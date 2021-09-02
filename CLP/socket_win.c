#include <stdio.h>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

//uint32_t htonl (uint32_t hostlong);   host to network long
//uint16_t htons (uint16_t hostshort);  host to network short
//uint32_t ntohl (uint32_t netlong);    network to host long
//uint16_t ntohs (uint16_t netshort);   network to host short

#define CALL(x) if (!(x) && fprintf(stderr, "'%s' failed (error=%d)\n", #x, WSAGetLastError())) exit(1)

int main(int argc, char * argv[]) {

    if (argc != 2) {
        fprintf(stderr, "usage: %s site_addr\n", argv[0]);
        return 0;
    }

    WSADATA wsa;
    CALL(WSAStartup(MAKEWORD(2, 2), & wsa) == 0);

    struct servent * sent;
    CALL((sent = getservbyname("http", "tcp")) != NULL);
    int port = sent -> s_port;

    struct protoent * pent;
    CALL((pent = getprotobyname("tcp")) != NULL);

    struct hostent * hent;
    CALL((hent = gethostbyname(argv[1])) != NULL);
    printf("%s -> %s\n", hent -> h_name, inet_ntoa( * ((struct in_addr * ) hent -> h_addr)));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr = * ((struct in_addr * ) hent -> h_addr);
    memset(addr.sin_zero, 0, 8);

    int sock;
    CALL((sock = socket(AF_INET, SOCK_STREAM, pent -> p_proto)) > 0);
    CALL((connect(sock, (struct sockaddr * ) & addr, sizeof(struct sockaddr))) == 0);

    char buff[1024 + 1];
    sprintf(buff, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[1]);
    CALL(send(sock, buff, strlen(buff), 0) == strlen(buff));

    int readin = recv(sock, buff, sizeof(buff) - 1, 0);
    while (readin > 0) {
        buff[readin] = '\0';
        printf("%s", buff);
        readin = recv(sock, buff, sizeof(buff) - 1, 0);
    }

    closesocket(sock);
    
    WSACleanup();

    return 0;
}