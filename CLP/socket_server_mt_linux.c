#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>

#define CALL(x) if (counter++ && !(x)) error(#x, __LINE__, counter)

int counter = 2;

char *quit_cmd = "QUIT\r\n";
char *exit_cmd = "EXIT\r\n";
char *draw_cmd = "DRAW\r\n";
char *ok_ans = "OK\r\n";
char *err_ans = "ERR\r\n";

int listen_sock = 0;

void error(char *action, int line, int retc)
{
    fprintf(stderr, "'%s' in line #%d failed - server terminated (%d)\n", action, line, errno);
    exit(retc);
}

void *serve_client(void *data)
{

    int conn_sock = *((int *)data);
    char buff[16];
    pthread_t self = pthread_self();
    srand(self);

    for (;;) {

        int readin = read(conn_sock, buff, sizeof(buff) - 1);
        buff[readin] = '\0';

        if (!strcmp(buff, draw_cmd)) {
            char answer[100];
            sprintf(answer, "OK %d\r\n", rand() % 10000);
            write(conn_sock, answer, strlen(answer));
            printf("thread %lxd: drawn\n", self);
        }
        else if (!strcmp(buff, quit_cmd)) {
            write(conn_sock, ok_ans, strlen(ok_ans));
            close(conn_sock);
            printf("thread %lxd: quitted\n", self);
            break;
        }
        else if (!strcmp(buff, exit_cmd)) {
            write(conn_sock, ok_ans, strlen(ok_ans));
            close(conn_sock);
            close(listen_sock);
            printf("thread %lxd: exited\n", self);
            exit(0);
        }
        else {
            write(conn_sock, err_ans, strlen(err_ans));
            printf("thread %lxd: bad command: %s\n", self, buff);
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage %s service_no\n", argv[0]);
        return 1;
    }

    int port = 0;
    
    CALL(sscanf(argv[1], "%d", &port) == 1 && port >= 1 && port <= 65535);
    
    struct protoent *pent;
    CALL((pent = getprotobyname("tcp")) != NULL);
    
    CALL((listen_sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0);
    
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(servaddr.sin_zero, 0, 8);
    
    int opt_on = 1;
    CALL(setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt_on, sizeof(opt_on)) == 0);
    CALL(bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) == 0);
    CALL(listen(listen_sock, 5) == 0);

    for (;;) {
        struct sockaddr_in cliaddr;
        int conn_sock = 0;
        socklen_t cliaddrlen = sizeof(cliaddr);
        
        for (;;) {
            CALL((conn_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &cliaddrlen)) > 0);
            
            printf("client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
            
            int *newsock = malloc(sizeof(int));
            pthread_t newthrd;
            *newsock = conn_sock;
            
            pthread_create(&newthrd, NULL, serve_client, newsock);
        }
    }
}