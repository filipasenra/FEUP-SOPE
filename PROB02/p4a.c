#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MAX_LEN_NAME 20
#define MAX_LEN_GRADE 3
#define MAX_N_STUDENTS 20

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage of %s is %s <source> <destination>\n", argv[0], argv[0]);
        return 1;
    }

    //abre o ficheiro numero 1
    int file1 = open(argv[1], O_WRONLY);
    if (file1 == -1)
    {
        perror("ERROR OPENING SOURCE FILE!");
        return 2;
    }

    char grades[MAX_N_STUDENTS][MAX_LEN_GRADE];
    char students[MAX_N_STUDENTS][MAX_LEN_NAME];
    
    printf("Enter %d student names and their respective grades.\n", MAX_N_STUDENTS);

    //let's get the name of the students and their respectives grades
    int i; //note why I declare i here

    for (i = 0; i < MAX_N_STUDENTS; i++)
    {
        printf("\nName: ");
        fgets(students[i], MAX_LEN_NAME, stdin);
        printf("Grade: ");
        fgets(grades[i], MAX_LEN_GRADE, stdin);
    }

    while (i > 0)
    {
        i--;

        //think why i don't use MAX_LEN_NAME & MAX_LEN_GRADE here
        write(file1, students[i], strlen(students[i])-1);
        write(file1, ": ", 2);
        write(file1, grades[i], strlen(grades[i])-1);
        write(file1, "\n", 2);
    }

    close(file1);

    return 0;
}