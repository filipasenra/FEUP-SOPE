#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    char *str;

    //Is the number of argumnts correct?
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s dir_name\n", argv[0]);
        exit(1);
    }

    //Tries to open the directory passed as argument
    //If it fails, displays the error
    if ((dirp = opendir(argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }

    //Until it has not reached the end of the directory (more files to display)
    while ((direntp = readdir(dirp)) != NULL)
    {
        //lstat returns information about the file in the stat_buf
        if (lstat(direntp->d_name, &stat_buf) == -1) // testar com stat()
        //if (stat(direntp->d_name, &stat_buf) == -1)
        {
            perror("lstat ERROR");
            exit(3);
        }

        //Analizes type and mode of file
        if (S_ISREG(stat_buf.st_mode))
            str = "regular";
        else if (S_ISDIR(stat_buf.st_mode))
            str = "directory";
        else
            str = "other";
        
        //name of the file, file type
        printf("%-25s - %s\n", direntp->d_name, str);
    }

    closedir(dirp);
    exit(0);
}
