#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    unsigned int n = atoi(argv[argc - 1]);

    while (n > 0)
    {
        printf("Hello!");

        unsigned int i = 0;
        while (i < (argc - 2))
        {
            i++;
            printf(" %s", argv[i]);
        }

        printf("\n");
        n--;
    }

    return 0;
}
