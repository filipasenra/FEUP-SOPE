#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{

    if (argc > 1)
    {

        int n = atoi(argv[argc - 1]);

        if (n <= 0)
            return 1;

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
    }
    else
    {
        char user[] = "USER=";

        while (*envp)
        {
            if (strncmp(*envp, user, 5) == 0)
            {
                printf("Hello %s\n", *envp + 5);
            }
            envp++;
        }
    }

    return 0;
}