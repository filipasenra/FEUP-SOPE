// PROGRAMA p7a.c
#include <stdio.h>
#include <stdlib.h>

void handler01(void)
{
    printf("Executing exit handler 1\n");
}
void handler02(void)
{
    printf("Executing exit handler 2\n");
}

int main(void)
{
    atexit(handler01);
    atexit(handler02);
    
    printf("Main done!\n");
    exit(0); // zero é geralmente indicativo de "sucesso"
}