#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MAX_LEN_NAME 100

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage of %s is %s <source>\n", argv[0], argv[0]);
        return 1;
    }

    //abre o ficheiro numero 1
    int file1 = open(argv[1], O_RDONLY);
    if (file1 == -1)
    {
        perror("ERROR OPENING Source FILE!");
        return 2;
    }

    typedef struct Student
    {
        char name[MAX_LEN_NAME];
        int grade;
    } Student;

    // Read student names and grades and print them to the screen
	Student s1;
	
	while( read(file1 , &s1 , sizeof(Student)) > 0){
	    printf("Name: %s          Grade: %d\n" , s1.name , s1.grade);
	}

	// Close the file
	close(file1);


	return 0;
}