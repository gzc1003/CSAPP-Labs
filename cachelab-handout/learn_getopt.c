#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    while (getopt(argc, argv, "abc") != -1)
        printf("optind: %d\n", optind);
    printf("optind: %d\n", optind);
    return 0;
}
