// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>

#define BUF_LENGTH 256
#define MAX 50

int main(void)
{
    FILE *src, *dst;
    char buf[BUF_LENGTH];

    if ((src = fopen("infile.txt", "r")) == NULL)
    {
        perror("Error in infile.txt");
        exit(1);
    }

    if ((dst = fopen("outfile.txt", "w")) == NULL)
    {
        perror("Error in outfile.txt");
        exit(2);
    }

    while ((fgets(buf, MAX, src)) != NULL)
    {
        fputs(buf, dst);
    }

    fclose(src);
    fclose(dst);
    exit(0); // zero é geralmente indicativo de "sucesso"
}