// PROGRAMA p1.c
/*
* Primeiro acaba o pai
* A variavel global passada ao filho não é atualizada pelo processo pai!
* Em várias execuções o PID tanto do filho como do pai muda. (sleep ajuda
* a fazer com que o processo pai termine depois do filho)
*/
#include<stdio.h> 
#include<unistd.h> 
#include<sys/types.h>

int global = 1;
int main(void)
{
    int local = 2;
    if (fork() > 0)
    {
        sleep(1);
        //processo pai
        printf("PID = %d; PPID = %d\n", getpid(), getppid());
        global++;
        local--;
    }
    else
    {
        //processo filho
        printf("PID = %d; PPID = %d\n", getpid(), getppid());
        global--;
        local++;
    }
    printf("\nPID = %d - global = %d ; local = %d\n", getpid(), global, local);
    return 0;
}