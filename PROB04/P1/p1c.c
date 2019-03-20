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
    sigaction(SIGINT , &action , NULL);

    //======================================
    action.sa_handler = SIG_IGN;
    //sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGUSR1 , &action , NULL);


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