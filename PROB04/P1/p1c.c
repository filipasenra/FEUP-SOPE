// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
    printf("In SIGINT handler ...\n");
}

int main(void)
{
    struct sigaction action;

    //=====================================
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGINT, &action, NULL) < 0)
    {
        fprintf(stderr, "Unable to install SIGINT handler\n");
        exit(1);
    }

    //======================================
    action.sa_handler = SIG_IGN;
    //sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    
    if (sigaction(SIGUSR1, &action, NULL) < 0)
    {
        fprintf(stderr, "Unable to ignore SIGUSR1\n");
        exit(2);
    }

    printf("Sleeping for 30 seconds ...\n");

    //Acorda do sono com SIGINT vai para o handler
    //outros comportamento por omissao
    int remaining_seconds = sleep(30);

    while (remaining_seconds != 0)
    {
        remaining_seconds = sleep(remaining_seconds);
    }

    printf("Waking up ...\n");
    exit(0);
}