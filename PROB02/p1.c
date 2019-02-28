#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 20

int main(void)
{
    write(STDIN_FILENO, "Password: ", strlen("Password: "));

    struct termios old, new;

    //vai buscar a estrutura termios atual do standard output
    tcgetattr(STDOUT_FILENO, &old);

    new = old;

    //vamos alterar a estrutura para que nao escreva no ecra
    //desativar os campos: ECHO, ECHOE, ECHOK e o Modo Canonico
    new.c_lflag &= ~(ECHO | ECHOE | ECHOK | ICANON);

    //queremos que a alteracao ocorra apos fazer o print para a consola
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    int i = 0;
    char tmp;

    //reading each caracter at a time
    do
    {
        read(STDIN_FILENO, &tmp, 1);

        if (tmp == '\n')
            break;

        write(STDOUT_FILENO, "*", 1);

        i++;

    } while (i < MAX_LEN);

    write(STDOUT_FILENO, "\n", 2);

    tcsetattr(STDOUT_FILENO, TCSANOW, &old);

    return 0;
}