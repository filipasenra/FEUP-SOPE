// PROGRAMA p6b.c

/**
 * Prints in the console what other program write in the fifo
 * 
 * Read devolve -1 e errno fica com o valor apropriado
 * 
 * Com O_RDWR como fica um processo com o fifo aberto, 
 * o read nunca devolve erro
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int readline(int fd, char *str);

int main(void)
{
    int fd;
    char str[100];

    mkfifo("/tmp/myfifo", 0660);
    fd = open("/tmp/myfifo", O_RDWR);

    while (readline(fd, str))
        printf("%s", str);

    close(fd);
    return 0;
}
int readline(int fd, char *str)
{
    int n;
    do
    {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');

    return (n > 0);
}