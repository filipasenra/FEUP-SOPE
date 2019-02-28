// PROGRAMA p8b.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    clock_t start, end;
    struct tms a;
    long ticks;
    start = times(&a); /*begin of time*/
    ticks = sysconf(_SC_CLK_TCK);

    time_t t;
    srand((unsigned)time(&t));

    if (argc < 3)
    {
        printf("Error\n");
        exit(1);
    }

    if (atoi(argv[2]) >= atoi(argv[1]))
    {
        printf("Error\n");
        exit(2);
    }

    int n = 0;
    unsigned int i = 0;

    do
    {
        i++;
        n = rand() % atoi(argv[1]);
        printf("%d %d\n", i, n);
    } while (n != atoi(argv[2]));

    sleep(3);
    
    end = times(&a); /*end of time*/

    printf("Tempo Real: %f\n", (double) (end-start)/ticks);
    printf("Tempo de CPU %f\n", (double) a.tms_stime/ticks);

    exit(0);
}