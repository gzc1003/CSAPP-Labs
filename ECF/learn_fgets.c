#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char str[50];
    while (1) {
        fgets(str, 49, stdin);
        if (feof(stdin))
            exit(0);
        printf("%s", str);
    }
}
