// PROGRAMA p6a1.c

/**
 * Prints in the console what other program write in the fifo
 * 
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
    fd = open("/tmp/myfifo", O_RDONLY);

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