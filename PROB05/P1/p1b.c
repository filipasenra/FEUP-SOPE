// PROGRAMA p1b.c
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
    typedef struct
    {
        int num1;
        int num2;
    } Numbers;

    int fd[2];
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
        Numbers numbers;

        close(fd[0]); /* fecha lado receptor do pipe */

        printf("Numeros (num1 num2): ");

        if (fgets(line, MAXLINE, stdin) < 0)
        {
            fprintf(stderr, "fgets error\n");
            exit(3);
        }

        if (sscanf(line, "%d %d", &numbers.num1, &numbers.num2) != 2)
        {
            fprintf(stderr, "sscanf error\n");
            exit(4);
        }

        write(fd[1], &numbers, sizeof(Numbers)); /* writes to pipe */

        if (waitpid(pid, NULL, 0) < 0) /* espera pelo fim do filho */
        {
            fprintf(stderr, "waitpid error\n");
            exit(6);
        }
    }
    else if (pid == 0) /* child */
    {
        Numbers numbers;

        close(fd[1]); /* closes write side */

        if (read(fd[0], &numbers, sizeof(Numbers)) == 0) /* reads from the pipe */
        {
            fprintf(stderr, "father closed pipe\n");
            exit(4);
        }

        printf("Sum: %d, Division: %d, Multiplication: %d, Diference: %d\n", numbers.num1 + numbers.num2, numbers.num1 / numbers.num2, numbers.num1 * numbers.num2, numbers.num1 - numbers.num2);
    }
    else /* error creating fork */
    {
        fprintf(stderr, "fork error\n");
        exit(2);
    }

    return 0;
}