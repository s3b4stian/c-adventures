#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (errno=%d)\n",#x,errno)) exit(1)

int main (int argc, char *argv[])
{
    if (argc != 2) {
        fprintf (stderr, "usage: %s site_addr\n", argv[0]);
        return 0;
    }

    struct servent *sent;
    CALL((sent = getservbyname("http", "tcp")) != NULL);
    int port = sent->s_port;

    struct protoent *pent;
    //if (!pent) {exit(1);}
    CALL ((pent = getprotobyname("tcp")) != NULL);

    struct hostent *hent;
    CALL ((hent = gethostbyname(argv[1])) != NULL);
    printf ("%s -> %s\n", hent->h_name, inet_ntoa (*((struct in_addr *) hent->h_addr)));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr = *((struct in_addr *) hent->h_addr);
    memset (addr.sin_zero, 0, 8);

    int sock;
    CALL ((sock = socket (AF_INET, SOCK_STREAM, pent->p_proto)) > 0);
    CALL ((connect(sock, (struct sockaddr *) &addr, sizeof (struct sockaddr)))== 0);

    char buff[1024 + 1];
    sprintf(buff, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",argv[1]);

    CALL (write (sock, buff, strlen (buff)) == strlen (buff));

    int readin = read(sock, buff, sizeof(buff) - 1);
    while (readin > 0) {
        buff[readin] = '\0';
        printf ("%s", buff);
        readin = read(sock, buff, sizeof(buff) - 1);
    }

    close (sock);

    return 0;
}