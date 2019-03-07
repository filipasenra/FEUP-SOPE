// PROGRAMA p7.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char prog[20];

    //Adiciona .c ao nome do programa passado por argumento
    sprintf(prog, "%s.c", argv[1]);

    //Executa o programa
    execlp("gcc", "gcc", prog, "-Wall", "-o", argv[1], NULL);

    //Nao passa por aqui porque:
    //quando um processo invoca exec, o processo é completamente 
    //substituído por um novo programa
    printf("This is not going to show!\n");
    
    exit(0);
}