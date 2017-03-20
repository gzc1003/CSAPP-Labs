#include <stdio.h>
#include <unistd.h>

unsigned int snooze(unsigned int secs)
{
    unsigned int res;
    res = sleep(secs);
    printf("Slept for %d of %d secs\n", secs-res, secs);
    return res;
}

int main(void)
{
    snooze(3);
    return 0;
}
