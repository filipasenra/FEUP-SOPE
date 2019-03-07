#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    switch (pid)
    {
    case -1:
        perror("fork");
        break;
    case 0: //filho
        printf("Hello");
        break;
    default: //pai
        //espera que o filho termine;
        wait(NULL);
        printf(" World!\n");
    }

    return 0;
}