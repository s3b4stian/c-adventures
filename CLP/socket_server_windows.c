#include <stdio.h>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define CALL(x) if (counter++ && !(x)) error(#x, __LINE__, counter)

int counter = 2;

void error(char* action, int line, int retc) {
    fprintf(stderr, "'%s' in line #%d failed - server terminated (%d)\n", action, line, WSAGetLastError());
    exit(retc);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage %s service_no\n", argv[0]);
        return 1;
    }

    WSADATA wsa;
    CALL(WSAStartup(MAKEWORD(2, 2), & wsa) == 0);

    int port = 0;
    CALL(sscanf(argv[1], "%d", & port) == 1 && port >= 1 && port <= 65535);

    struct protoent * pent;
    CALL((pent = getprotobyname("tcp")) != NULL);

    int listen_sock;
    CALL((listen_sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(servaddr.sin_zero, 0, 8);

    int opt_on = 1;
    CALL(setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, (char*) & opt_on, sizeof(opt_on)) == 0);

    CALL(bind(listen_sock, (struct sockaddr * ) & servaddr, sizeof(servaddr)) == 0);

    CALL(listen(listen_sock, 5) == 0);

    for (;;) {
        struct sockaddr_in cliaddr;
        int conn_sock = 0;
        int cliaddrlen = sizeof(cliaddr);
        
        CALL((conn_sock = accept(listen_sock, (struct sockaddr*) &cliaddr, &cliaddrlen)) > 0);
        
        printf("client: %s:%d\n", inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
        
        srand(time(NULL));
        
        for (;;) {

            char buff[16];
            char* quit_cmd = "QUIT\r\n";
            char* exit_cmd = "EXIT\r\n";
            char* draw_cmd = "DRAW\r\n";
            char* ok_ans = "OK\r\n";
            char* err_ans = "ERR\r\n";

            int readin = recv(conn_sock, buff, sizeof(buff) - 1, 0);
            buff[readin] = '\0';

            if (!strcmp(buff, draw_cmd)) {
                char answer[100];
                sprintf(answer, "OK %d\r\n", rand() % 10000);
                send(conn_sock, answer, strlen(answer), 0); 
                printf("drawn\n");
            }
            else if (!strcmp(buff, quit_cmd)) {
                send(conn_sock, ok_ans, strlen(ok_ans), 0);
                closesocket(conn_sock);
                printf("quitted\n");
                break;
            }
            else if (!strcmp(buff, exit_cmd)) {
                send(conn_sock, ok_ans, strlen(ok_ans), 0);
                closesocket(conn_sock);
                closesocket(listen_sock);
                WSACleanup();
                printf("exited\n");
                return 0;
            }
            else {
                send(conn_sock, err_ans, strlen(err_ans), 0);
                printf("bad command: %s\n", buff);
            }
        }
    }
}