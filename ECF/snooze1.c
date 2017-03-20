#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signum) { return; }

int main(int argc, char* argv[])
{
    unsigned int t, i;
    signal(SIGINT, sigint_handler);
    i = atoi(argv[1]);
    t = sleep(i);
    printf("Slept for %u of %u secs.\n", t, i);
    return 0;
}
