#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAXLINE 15

int main(int argc, char* argv[])
{
    struct addrinfo hints, *listp, *p;
    struct sockaddr_in* sockp;
    char buf[MAXLINE];
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(argv[1], NULL, &hints, &listp) != 0) {
        printf("getaddrinfo error\n");
        exit(-1);
    }

    for (p = listp; p != NULL; p = p->ai_next) {
        sockp = (struct sockaddr_in*)p->ai_addr;
        inet_ntop(AF_INET, &(sockp->sin_addr), buf, MAXLINE);
        printf("%s\n", buf);
    }

    freeaddrinfo(listp);

    return 0;
}
