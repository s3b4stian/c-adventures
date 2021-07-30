#include <stdio.h>

#ifdef _MSC_VER
#include <Winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

#ifdef _MSC_VER
#define CALL(x)                                                                     \
    if (!(x) && fprintf(stderr, "'%s' failed (error=%d)\n", #x, WSAGetLastError())) \
    Exit(1)
#else
#define CALL(x)                                                         \
    if (!(x) && fprintf(stderr, "'%s' failed (errno=%d)\n", #x, errno)) \
    Exit(1)
#endif


void Exit(int retc)
{
#ifdef _MSC_VER
    WSACleanup();
#endif
    exit(retc);
}

int Write(int h, char *buf, int siz)
{
#ifdef _MSC_VER
    return send(h, buf, siz, 0);
#else
    return write(h, buf, siz);
#endif
}

int Read(int h, char *buf, int siz)
{
#ifdef _MSC_VER
    return recv(h, buf, siz, 0);
#else
    return read(h, buf, siz);
#endif
}

int Close(int h)
{
#ifdef _MSC_VER
    return closesocket(h);
#else
    return close(h);
#endif
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s site_addr\n", argv[0]);
        return 0;
    }

#ifdef _MSC_VER
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

    struct addrinfo hints;
    struct addrinfo *info;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    CALL(getaddrinfo(argv[1], "http", &hints, &info) == 0);

    char str[32];
    inet_ntop(info->ai_family, &((struct sockaddr_in *)info->ai_addr)->sin_addr, str, sizeof(str) - 1);
    printf("%s -> %s\n", info->ai_canonname, str);

    struct sockaddr_in addr = *((struct sockaddr_in *)info->ai_addr);

    int sock;
    CALL((sock = socket(AF_INET, SOCK_STREAM, info->ai_protocol)) > 0);

    CALL((connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr))) == 0);

    char buff[1024 + 1];
    sprintf(buff, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
            argv[1]);

    CALL(Write(sock, buff, strlen(buff)) == strlen(buff));

    int readin = Read(sock, buff, sizeof(buff) - 1);
    while (readin > 0)
    {
        buff[readin] = '\0';
        printf("%s", buff);
        readin = Read(sock, buff, sizeof(buff) - 1);
    }

    Close(sock);
    freeaddrinfo(info);
#ifdef _MSC_VER
    WSACleanup();
#endif
    return 0;
}