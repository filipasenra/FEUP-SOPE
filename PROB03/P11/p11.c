// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_N_COM 20

/**
 * @param array de strings com os comandos separados
 * @param numero de comandos
 * @param string de c com os comandos
*/
void separate_arg(char *arg[MAX_N_COM], char command[MAX_LEN])
{
    char delim[] = " ";
    int n_arg = 0;

    //parte a string em arg em vários com o delim como delimitador
    char *command_token = strtok(command, delim);

    //quando chegar ao fim dos comandos
    while (command_token != NULL && n_arg != MAX_LEN)
    {
        arg[n_arg] = command_token;
        n_arg++;
        command_token = strtok(NULL, delim);
    }

    arg[n_arg] = NULL;
}

void eliminating_new_line(char command[MAX_LEN])
{
    int n = 0;

    while (command[n] != NULL && n <= MAX_LEN)
    {
        if (command[n] == '\n')
            command[n] = 0;
        n++;
    }
}

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc < 1)
    {
        printf("usage: %s\n", argv[0]);
        exit(1);
    }

    char a[MAX_LEN];

    while (strcmp(a, "quit") != 0)
    {

        printf("\nminix > ");
        fgets(a, sizeof(a), stdin);
        eliminating_new_line(a);

        char *arg[MAX_N_COM];
        separate_arg(arg, a);

        pid = fork();

        //filho executa o comando
        if (pid == 0)
        {
            execvp(arg[0], arg);

        }else if (pid > 0)
        //pai espera
        {
            wait(NULL);
        }
    }

    return 0;
}