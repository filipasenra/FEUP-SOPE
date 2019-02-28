#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define N_TOKENS 2

int main(void)
{
    char a[MAX + 1];
    char s[] = " > ";
    char * save[N_TOKENS];

    printf("Linha de comando: ");
    fgets(a, MAX, stdin);

    char *token = strtok(a, s);
    unsigned int i =0;

    while (token != NULL && i < N_TOKENS)
    {
        save[i] = token;
        token = strtok(NULL, s);
        i++;
    }

    unsigned int tmp = i;
    i = 0;

    while(i < tmp && i < N_TOKENS)
    {
        printf("%s ", save[i]);
        i++;
    }

    return 0;
}