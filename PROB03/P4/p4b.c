#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    //antes de haver o fork, é o processo pai a esrecver
    write(STDOUT_FILENO, "Hello !", strlen("Hello !"));

    pid = fork();

    if (pid == 0)
    {
        write(STDOUT_FILENO, "World!\n", strlen("World!\n"));
    }
    else if (pid == -1)
    {
        perror("fork");
        return 2;
    }

    return 0;
}