#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_LEN 20

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage of %s is %s <source> <destination>\n", argv[0], argv[0]);
        return 1;
    }

    //abre o ficheiro numero 1
    int file1 = open(argv[1], O_RDONLY);
    if (file1 == -1)
    {
        perror("ERROR OPENING SOURCE FILE!");
        return 2;
    }

    //abre o ficheiro numero 2
    int file2 = open(argv[2], O_WRONLY);
    if (file2 == -1)
    {
        perror("ERROR OPENING DESTINATION FILE!");
        return 3;
    }

    char a[MAX_LEN];
    int nr;
    while ((nr = read(file1, a, MAX_LEN)) > 0)
    {
        if (write(file2, a, nr) != nr)
        {
            perror("ERROR OPENING DESTINATION FILE!");
        }
    }

    close(file1);
    close(file2);

    return 0;
}