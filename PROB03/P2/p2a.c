#include<stdio.h> 
#include<unistd.h> 
#include<sys/types.h>
/*
* Primeiro executa o pai, depois o filho.
*/

int main(void)
{
    write(STDOUT_FILENO, "1\n", 3);
    if (fork() > 0)
    {
        //Papai
        write(STDOUT_FILENO, "2", 1);
        write(STDOUT_FILENO, "3", 1);
    }
    else
    {
        //Filho
        write(STDOUT_FILENO, "4", 1);
        write(STDOUT_FILENO, "5", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
    return 0;
}