#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>

#define CALL(x) if (counter++ && !(x)) error(#x, __LINE__, counter)

#define h_addr h_addr_list[0] /* for backward compatibility */

int counter = 2;

void error(char * action, int line, int retc) {
    fprintf(stderr, "'%s' in line #%d failed - client terminated\n", action,
        line);
    exit(retc);
}

int main(int argc, char * argv[]) {
    
    //check for all arguments
    if (argc != 4) {
        fprintf(stderr, "usage %s server_addr service_no number_no\n", argv[0]);
        return 1;
    }

    //scanf for port and check port range
    //check id do uscing the CALL macro
    int port = 0;
    CALL(sscanf(argv[2], "%d", & port) == 1 && port >= 1 && port <= 65535);

    //scanf for the number of client iterations with the server
    int numno = 0;
    CALL(sscanf(argv[3], "%d", & numno) == 1 && numno >= 0 && numno <= 10);

    //create the structure hosthent
    struct hostent * hent = NULL;
    CALL((hent = gethostbyname(argv[1])) != NULL);

    //create the strcuture protoent
    struct protoent * pent;
    CALL((pent = getprotobyname("tcp")) != NULL);

    //creat sockaddr_in struct for the connection
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = * ((struct in_addr * ) hent->h_addr); //basckward compatibility applied
    memset(addr.sin_zero, 0, 8);

    //create the socket
    int sock;
    CALL((sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

    //make connection
    CALL((connect(sock, (struct sockaddr * ) &addr, sizeof(struct sockaddr))) == 0);

    char * draw_cmd = "DRAW\r\n", * quit_cmd = "QUIT\r\n";

    if (numno == 0) {
        char* exitcmd = "EXIT\r\n";
        CALL(write(sock, exitcmd, strlen(exitcmd)) == strlen(exitcmd));
        close(sock);
        return 0;
    }

    while (numno--) {
        CALL(write(sock, draw_cmd, strlen(draw_cmd)) == strlen(draw_cmd));
        char buff[16];
        int readin = 0;
        CALL((readin = read(sock, buff, sizeof(buff))) > 0);
        buff[readin] = '\0';
        printf("%s\n", buff);
        if (numno) {
            sleep(1);
        }
    }

    CALL(write(sock, quit_cmd, strlen(quit_cmd)) == strlen(quit_cmd));

    close(sock);

    return 0;
}