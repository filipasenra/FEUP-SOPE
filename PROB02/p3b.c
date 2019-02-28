#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_LEN 20

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage of %s is %s <source> \n", argv[0], argv[0]);
        return 1;
    }

    //abre o ficheiro numero 1
    int file1 = open(argv[1], O_RDONLY);
    if (file1 == -1)
    {
        perror("ERROR OPENING SOURCE FILE!");
        return 2;
    }

    int file2;

    if (argc == 3)
    {
        //abre o ficheiro numero 1
        file2 = open(argv[2], O_WRONLY | O_TRUNC);
        if (file2 == -1)
        {
            perror("ERROR OPENING DESTINATION FILE!");
            return 2;
        }

        dup2(file2, STDOUT_FILENO);
    }

    char a[MAX_LEN];
    int nr;
    while ((nr = read(file1, a, MAX_LEN)) > 0)
    {
        if (write(file2, a, nr) != nr)
        {
            perror("ERROR WRITING IN DESTINATION FILE!");
        }
    }

    close(file1);
    close(file2);

    return 0;
}