/* FOLHA DE PROBLEMAS No 4 - Sinais
 *  Prob. 3.b)
 * jmcruz@fe.up.pt, 22.mar.2019
 */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int v = 0;
#define NTIMES 10

void handler(int n)
{
    if (n == SIGUSR1)
        v++;
    if (n == SIGUSR2)
        v--;
    printf("\nv: %d", v);
    if (v >= NTIMES)
        exit(0);
} // handler()

int main(void)
{
    int f = fork();
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    // NOTE: it is not good idea to install here the signal handlers, as signals might arrive before and kill child!
    if (sigaction(SIGUSR1, &act, NULL) < 0)
    {
        perror("sigaction1");
        exit(1);
    }
    if (sigaction(SIGUSR2, &act, NULL) < 0)
    {
        perror("sigaction2");
        exit(1);
    }
    if (f < 0)
    {
        perror("fork");
        exit(1);
    }
    if (f == 0)
    {
        printf("Child waiting for %d signals...\n", NTIMES);
        while (1)
            pause();
    }
    else if (f > 0)
    {
        int count = 0;
        //sleep(1); // (try to) make sure child has time to install handlers...
        srandom((unsigned int)time(NULL));
        for (count = 0; count < NTIMES; count++)
        {
            if ((random() % 2) == 1)
                kill(f, SIGUSR1);
            else
                kill(f, SIGUSR2);
            printf("\ncount: %d", count);
        }
    }
    return (0);
} // main()
