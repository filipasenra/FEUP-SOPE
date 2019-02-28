#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
int main(void)
{
    char a[MAX + 1];
    char s[] = " > ";

    printf("Linha de comando: ");
    fgets(a, MAX, stdin);

    char *token = strtok(a, s);

    while (token != NULL)
    {
        printf("%s ", token);

        token = strtok(NULL, s);
    }

    return 0;
}