// PROGRAMA p1c.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 256

/**
 * Is missing the protocol: how should I do it?
 * Missing some verification for errors!
*/

int main(int argc, char *argv[], char *envp[])
{

    int fd1[2], fd2[2], numbers[2];
    char line[MAXLINE];
    int sum = 0, division, multipli, diference;

    int return_pipe = pipe(fd1); /* opens pipe */

    if (return_pipe < 0) /* if opening pipe failed*/
    {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }

    return_pipe = pipe(fd2);

    if (return_pipe < 0) /* if opening pipe failed*/
    {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }

    int pid = fork(); /* creates child process */

    if (pid > 0) /* father */
    {
        close(fd1[0]); /* fecha lado receptor do pipe */
        close(fd2[1]); /* closes write side*/

        printf("Numeros (num1 num2): ");

        if (fgets(line, MAXLINE, stdin) < 0)
        {
            fprintf(stderr, "fgets error\n");
            exit(3);
        }

        if (sscanf(line, "%d %d", &numbers[0], &numbers[1]) != 2)
        {
            fprintf(stderr, "sscanf error\n");
            exit(4);
        }

        write(fd1[1], numbers, sizeof(numbers)); /* writes to pipe */

        if (waitpid(pid, NULL, 0) < 0) /* espera pelo fim do filho */
        {
            fprintf(stderr, "waitpid error\n");
            exit(6);
        }

        read(fd2[0], &sum, sizeof(sum));
        printf("Sum: %d, ", sum);

        read(fd2[0], &division, sizeof(int));
        printf("Division: %d, ", division);

        read(fd2[0], &multipli, sizeof(int));
        printf("Multiplication: %d, ", multipli);

        read(fd2[0], &diference, sizeof(int));
        printf("Diference: %d\n", diference);
    }
    else if (pid == 0) /* child */
    {
        close(fd1[1]); /* closes write side */
        close(fd2[0]); /* closes read side */

        if (read(fd1[0], numbers, sizeof(numbers)) == 0) /* reads from the pipe */
        {
            fprintf(stderr, "father closed pipe\n");
            exit(4);
        }

        sum = numbers[0] + numbers[1];
        division = numbers[0] / numbers[1];
        multipli = numbers[0] * numbers[1];
        diference = numbers[0] - numbers[1];

        write(fd2[1], &sum, sizeof(sum));
        write(fd2[1], &division, sizeof(int));
        write(fd2[1], &multipli, sizeof(int));
        write(fd2[1], &diference, sizeof(int));

    }
    else /* error creating fork */
    {
        fprintf(stderr, "fork error\n");
        exit(2);
    }

    return 0;
}