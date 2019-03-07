#include<stdio.h> 
#include<unistd.h> 
#include<sys/types.h>
/*
* printf não escreve diretamente na consola, mas num buffer
* esse buffer é passado pelo pai ao filho, por isso, vemos a repetição do 1 
* tanto no prcesso filho como no processo pai
*/

int main(void)
{
    //write(STDOUT_FILENO, "1\n", 3);
    printf("1");
    if (fork() > 0)
    {
        //Papai
        /*write(STDOUT_FILENO, "2", 1);
        write(STDOUT_FILENO, "3", 1);*/
        printf("2");
        printf("3");
    }
    else
    {
        //Filho
        /* write(STDOUT_FILENO, "4", 1);
        write(STDOUT_FILENO, "5", 1); */
        printf("4");
        printf("5");
    }
    /* write(STDOUT_FILENO, "\n", 1); */
    printf("\n");
    return 0;
}