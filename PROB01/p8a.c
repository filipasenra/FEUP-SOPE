// PROGRAMA p8a.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t t;
    srand((unsigned) time(&t));

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

    exit(0);
}