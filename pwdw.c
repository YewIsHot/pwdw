#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <linux/limits.h>

int main()
{
    char path[PATH_MAX];
    getcwd(path, PATH_MAX);
    char *del = "/";

    // Checking if current directory is from Windows
    char *dir = strtok(path, del);
    if (strcmp(dir, "mnt"))
    {
        fprintf(stderr, "This untility can be used only in Windows native directiories (mounted to /mnt).\n");
        return EXIT_FAILURE;
    }

    char winPath[PATH_MAX];
    winPath[0] = '\0';

    
    // Changing disk name and adding ":"
    char *disk = strtok(NULL, del);
    for (int i = 0; i < strlen(disk); i++)
    {
        disk[i] = toupper(disk[i]);
    }
    
    strcat(winPath, disk);
    strcat(winPath, ":");
    
    // Adding the rest of the path, separated by [backslash]
    while (dir = strtok(NULL, del), dir != NULL)
    {
        strcat(winPath, "\\");
        strcat(winPath, dir);
    }
    
    // Printing the result
    printf("%s\n", winPath);

    return EXIT_SUCCESS;
}