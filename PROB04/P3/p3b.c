// PROGRAMA p03a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>

int v = 0;

void handler(int signo)
{
    if (signo == SIGUSR1)
    {
        v++;
    }
    else
    {
        v--;
    }

    printf("V value: %d\n", v);
}

int main(void)
{
    int pid = fork();

    if (pid < 0)
    {
        printf("fork error");
        exit(1);
    }
    else if (pid == 0) /* filho */
    {
        struct sigaction action;
        action.sa_handler = handler;
        sigemptyset(&action.sa_mask);
        action.sa_flags = 0;

        if (sigaction(SIGUSR1, &action, NULL) < 0)
        {
            fprintf(stderr, "Unable to install SIGUSR1 handler\n");
            exit(1);
        }

        if (sigaction(SIGUSR2, &action, NULL) < 0)
        {
            fprintf(stderr, "Unable to install SIGUSR2 handler\n");
            exit(1);
        }

        //waits for next signal
        while (1)
        {
            pause();
        }
    }
    else /* pai */
    {
        srand(time(NULL)); // Initialization, should only be called once.
        
        //Why do I have to printf before calling child
        printf("... \n");

        for (int i = 0; i < 10; i++)
        {
            int r = rand() % 2; /* between 0 e 1 */

            //sending signal do child
            if (r == 0)
            {
                kill(pid, SIGUSR1);
            }
            else
            {
                kill(pid, SIGUSR2);
            }

            //Gives time to the child to finish its work
            sleep(1);
        }

        //terminates the child
        kill(pid, SIGTERM);
    }

    exit(0);
}