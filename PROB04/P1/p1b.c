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
    //ORIGEM DE SIGINT: teclado (^C)
    if (signal(SIGINT, sigint_handler) < 0)
    {
        fprintf(stderr, "Unable to install SIGINT handler\n");
        exit(1);
    }

    if (signal (SIGUSR1, SIG_IGN) < 0)
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