// PROGRAMA p3a.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>

#define MAXLINE 256

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Use of program %s <output_file>\n", argv[0]);
        return 1;
    }

    int pid = fork();

    if (pid == 0)
    {
        char command[256] = "sort ";
        strcat(command, argv[1]);
        strcat(command, " | cat");

        system(command);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }

    return 0;
}