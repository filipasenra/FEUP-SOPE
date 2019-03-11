// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 2 && argc != 3)
    {
        printf("usage: %s <dirname> <destination>\n", argv[0]);
        exit(1);
    }
    pid = fork();

    if (pid > 0)
    {
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
        wait(NULL);
    }
    else if (pid == 0)
    {
        if (argc == 3) //user entered destination file
        {
            int file = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 00644);

            if (file == -1)
            {
                printf("Error creating the file %s (it may already exist)\n", argv[2]);
                exit(2);
            }

            // redirects STDOUT_FILENO to the file
            if (dup2(file, STDOUT_FILENO) == -1)
            {
                printf("Failed to redirects STDOUT_FILENO to the file.\n");
                exit(3);
            }
        }


        execlp("ls", "ls", "-laR", argv[1], NULL);

        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}