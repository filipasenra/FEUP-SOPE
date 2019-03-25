// PROGRAMA p1a.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 256

int main(int argc, char *argv[], char *envp[])
{
    int fd[2];
    int num1, num2;
    char line[MAXLINE];

    int return_pipe = pipe(fd); /* opens pipe */

    if (return_pipe < 0) /* if opening pipe failed*/
    {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }

    int pid = fork(); /* creates child process */

    if (pid > 0) /* father */
    {
        close(fd[0]); /* fecha lado receptor do pipe */

        printf("Numeros (num1 num2): ");

        if (fgets(line, MAXLINE, stdin) < 0)
        {
            fprintf(stderr, "fgets error\n");
            exit(3);
        }

        write(fd[1], line, strlen(line)); /* writes to pipe */

        if (waitpid(pid, NULL, 0) < 0) /* espera pelo fim do filho */ 
        {
            fprintf(stderr, "waitpid error\n");
            exit(6);
        }
    }
    else if (pid == 0) /* child */
    {
        close(fd[1]); /* closes write side */

        if (read(fd[0], line, MAXLINE) == 0) /* reads from the pipe */
        {
            fprintf(stderr, "father closed pipe\n");
            exit(4);
        }

        if (sscanf(line, "%d %d", &num1, &num2) == 2) /* gets value of numbers */
        {
            printf("Sum: %d, Division: %d, Multiplication: %d, Diference: %d\n", num1 + num2, num1 / num2, num1 * num2, num1 - num2);
        }
    }
    else /* error creating fork */
    {
        fprintf(stderr, "fork error\n");
        exit(2);
    }

    return 0;
}