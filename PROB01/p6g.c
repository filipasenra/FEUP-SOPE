// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_LENGTH 256
#define MAX 50

int main(int argc, char *argv[])
{
    FILE *src, *dst;
    char buf[BUF_LENGTH];

    if (argc < 3)
        {
            printf("usage: nome_do_executável file1 file2\n");
            exit(3);
        }

    if ((src = fopen(argv[1], "r")) == NULL)
    {
        printf("Error %d\n", errno);
        exit(1);
    }

    if ((dst = fopen(argv[2], "w")) == NULL)
    {
        printf("Error %d\n", errno);
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