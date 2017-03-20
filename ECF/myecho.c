#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    int i;
    printf("Command-line arguments:\n");
    for (i = 0; i < argc; i++) {
        printf("    argv[%2d]: %s\n", i, argv[i]);
    }

    printf("Environment variables:\n");

    for (i = 0; envp[i] != NULL; i++) {
        printf("    envp[%2d]: %s\n", i, envp[i]);
    }
    return 0;
}
