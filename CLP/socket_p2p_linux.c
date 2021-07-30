#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#define h_addr h_addr_list[0]
#define CALL(x) if (counter++ && !(x)) error(#x, __LINE__, counter)
#define MAX_SIZE 4

int counter = 2;

void error(char * action, int line, int retc) {
    fprintf(stderr, "'%s' in line #%d failed - terminated (%d)\n", action, line, errno);
    exit(retc);
}

char* times2(char * val)
{
    int len = strlen(val);
    char * newval = malloc(len + 2);
    newval[len + 1] = '\0';
    int i, cy = 0;
    
    for (i = len - 1; i >= 0; i--) {
        char c = 2 * (val[i] - '0') + cy;
        cy = c >= 10;
        c %= 10;
        newval[i + 1] = '0' + c;
    }
    
    if (cy)
        newval[0] = '1';
    else
        memmove(newval, newval + 1, len + 1);
    
    return newval;
}

int main(int argc, char * argv[])
{
    
    if (argc != 4 && argc != 5) {
        fprintf(stderr, "usage: %s my_port peer_addr peer_port [value]\n", argv[0]);
        
        return 1;
    }
    
    int myport = 0;
    CALL(sscanf(argv[1], "%d", & myport) == 1 && myport >= 1 && myport <= 65535);
    
    int peerport = 0;
    CALL(sscanf(argv[3], "%d", & peerport) == 1 && peerport >= 1 && peerport <= 65535);
    
    unsigned first = 0;
    if (argc == 5) {
        CALL(sscanf(argv[4], "%u", & first) == 1 && first >= 1 && first <= (1 << 16));
    }

    struct hostent * hent = NULL;
    CALL((hent = gethostbyname(argv[2])) != NULL);
    
    struct protoent * pent;
    CALL((pent = getprotobyname("udp")) != NULL);
    
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(myport);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(myaddr.sin_zero, 0, 8);
    
    struct sockaddr_in peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_port = htons(peerport);
    peeraddr.sin_addr = * ((struct in_addr*) hent->h_addr);
    memset(peeraddr.sin_zero, 0, 8);
    
    int mysock;
    //create socket
    CALL((mysock = socket(AF_INET, SOCK_DGRAM, pent->p_proto)) > 0);
    //bind socket
    CALL(bind(mysock, (struct sockaddr*) &myaddr, sizeof(myaddr)) == 0);
    
    char * buf = NULL, * resp = NULL;
    
    for (;;) {
        
        if (first) {
            resp = malloc(16);
            sprintf(resp, "%u", first);
            first = 0;
        } 
        else {
            buf = malloc(MAX_SIZE + 1);
            int recvd = 0;
            //receive from, accept from any peer
            CALL(recvd = recvfrom(mysock, buf, MAX_SIZE, 0, NULL, NULL));
            buf[recvd] = '\0';
            printf("rcvd: %s\n", buf);
            
            if (recvd >= MAX_SIZE) {
                break;
            }

            sleep(1);
            
            resp = times2(buf);
            free(buf);
        }
        
        int tosend = strlen(resp);
        //send to specific peer
        CALL(sendto(mysock, resp, tosend, 0, (struct sockaddr*) &peeraddr, sizeof(peeraddr)));
        
        printf("sent: %s\n", resp);
        
        free(resp);
        
        if (tosend >= MAX_SIZE) {
            break;
        }
    }

    close(mysock);
    return 0;
}