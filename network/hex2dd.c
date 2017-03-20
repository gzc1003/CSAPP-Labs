#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 15

int main(int argc, char* argv[])
{
    char dst[MAXLINE];
    const char* dd;
    uint32_t addr;
    struct in_addr inaddr;
    sscanf(argv[1], "%x", &addr);
    inaddr.s_addr = htonl(addr);
    if ((dd = inet_ntop(AF_INET, &inaddr, dst, MAXLINE)) == NULL) {
        printf("inet_ntop error\n");
        exit(-1);
    }
    printf("%s\n", dd);
    return 0;
}
