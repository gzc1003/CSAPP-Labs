#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    struct in_addr inaddr;
    uint32_t saddr;
    if (inet_pton(AF_INET, argv[1], &inaddr) == -1) {
        printf("inet_pton error\n");
        exit(-1);
    }
    saddr = ntohl(inaddr.s_addr);
    printf("0x%x\n", saddr);
    return 0;
}
