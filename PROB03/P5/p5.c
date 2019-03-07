#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * Assumi que o fork não deu erro!
*/

int main(void)
{
    pid_t pid;

    pid = fork();

    //filho1
    if (pid == 0)
        write(STDOUT_FILENO, "Hello ", strlen("Hello "));
    else
    {
        //espera pelo filho1 e termina
        wait(NULL);
        return 0;
    }

    pid = fork();

    //filho2
    if (pid == 0)
        write(STDOUT_FILENO, "my ", strlen("my "));
    else
    {
        //o filho1 espera pelo filho2 e termina
        wait(NULL);
        return 0;
    }

    pid = fork();

    //filho3
    if (pid == 0)
        write(STDOUT_FILENO, "friends!\n", strlen("friends!\n"));
    else
    {
        //o filho2 espera pelo filho3 e termina
        wait(NULL);
        return 0;
    }
    
    return 0;
}