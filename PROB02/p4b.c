#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MAX_LEN_NAME 100
#define MAX_LEN_GRADE 15
#define MAX_N_STUDENTS 4

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage of %s is %s <destination>\n", argv[0], argv[0]);
        return 1;
    }

    //abre o ficheiro numero 1
    int file1 = open(argv[1], O_WRONLY | O_TRUNC);
    if (file1 == -1)
    {
        perror("ERROR OPENING Destination FILE!");
        return 2;
    }

    typedef struct Student
    {
        char name[MAX_LEN_NAME];
        int grade;
    } Student;

    Student struStudents[MAX_N_STUDENTS];

    printf("Enter %d student names and their respective grades.\n", MAX_N_STUDENTS);

    //let's get the name of the students and their respectives grades
    int i; //note why I declare i here

    for (i = 0; i < MAX_N_STUDENTS; i++)
    {
        printf("\nName: ");
        fgets(struStudents[i].name, MAX_LEN_NAME, stdin);
        printf("Grade: ");
        scanf("%d", &struStudents[i].grade);
        getchar();
    }

    while (i > 0)
    {
        i--;

        write(file1, &struStudents[i], sizeof(Student));
    }

    close(file1);

    return 0;
}