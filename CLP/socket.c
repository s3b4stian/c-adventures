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

//check if returned pointer is null
//print the message exploiting short circuit
#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (errno=%d)\n",#x,errno)) exit(1)

int main (int argc, char *argv[])
{
    if (argc != 2) {
        fprintf (stderr, "usage: %s site_addr\n", argv[0]);
        return 0;
    }

    //struct servent {
    //  char  *s_name;      // official service name
    //  char **s_aliases;   // alias list
    //  int    s_port;      // port number
    //  char  *s_proto;     // protocol to use
    //}
    struct servent *sent;
    CALL((sent = getservbyname("http", "tcp")) != NULL);
    int port = sent->s_port;

    //struct protoent {
    //  char  *p_name;      // official protocol name
    //  char **p_aliases;   // alias list
    //  int    p_proto;     // protocol number
    //}
    struct protoent *pent;
    //returns a protoent structure for
    //the entry from the database that matches the protocol name name.
    CALL((pent = getprotobyname("tcp")) != NULL);


    //struct hostent {
    //  char  *h_name;      // official name of host
    //  char **h_aliases;   // alias list
    //  int    h_addrtype;  // host address type
    //  int    h_length;    // length of address
    //  char **h_addr_list; // list of addresses
    //}
    //#define h_addr h_addr_list[0] //for backward compatibility
    struct hostent *hent;
    //returns a structure of type hostent for the given host name.
    CALL((hent = gethostbyname(argv[1])) != NULL);
    printf("%s -> %s\n", hent->h_name, inet_ntoa(*((struct in_addr *) hent->h_addr)));


    //struct sockaddr_in {
    //  a_family_t     sin_family; // address family: AF_INET
    //  in_port_t      sin_port;   // port in network byte order
    //  struct in_addr sin_addr;   // internet address
    //};
    //Internet address
    //struct in_addr {
    //  uint32_t       s_addr;     // address in network byte order
    //};
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr = *((struct in_addr *) hent->h_addr);
    memset(addr.sin_zero, 0, 8);

    //tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    //udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    //raw_socket = socket(AF_INET, SOCK_RAW, protocol);
    int sock;
    CALL((sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0);
    
    CALL((connect(sock, (struct sockaddr *) &addr, sizeof(struct sockaddr))) == 0);

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