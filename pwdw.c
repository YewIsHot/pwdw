#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <linux/limits.h>

int addDistroToPath(char *path)
{
    // Loading distro info
    FILE *release = popen("cat /etc/os-release", "r");

    if (release == NULL)
    {
        fprintf(stderr, "Could not get WSL distro name!\n");
        return 0;
    }

    char line[1024];
    char lineStart[] = "NAME=";
    while(fgets(line, sizeof(line), release) != NULL)
    {
        if (strncmp(lineStart, line, strlen(lineStart)) != 0) continue;

        // Cutting the excessive part of the string
        int lineLen = strlen(line);
        line[lineLen - 2] = '\0';

        strcat(path, &line[strlen(lineStart) + 1]);
    }

    pclose(release);
    return 1;
}

int getWslPath(char *path, char *dir, char * del)
{
    // Adding common path beggining
    strcat(path, "\\\\wsl.localhost\\");

    if (!addDistroToPath(path)) return 0;

    // Append the rest of the path with new delimiter
    do
    {
        strcat(path, "\\");
        strcat(path, dir);
    }
    while (dir = strtok(NULL, del), dir != NULL);    

    return 1;
}

void getWindowsPath(char *path, char *dir, char *del)
{
     // Changing disk name and adding ":"
    char *disk = strtok(NULL, del);
    for (int i = 0; i < strlen(disk); i++)
    {
        disk[i] = toupper(disk[i]);
    }
    
    strcat(path, disk);
    strcat(path, ":");
    
    // Adding the rest of the path, separated by [backslash]
    while (dir = strtok(NULL, del), dir != NULL)
    {
        strcat(path, "\\");
        strcat(path, dir);
    }
}

int main()
{
    char path[PATH_MAX];
    if (getcwd(path, PATH_MAX) == NULL)
    {
        fprintf(stderr, "Could not get the directory path!\n");
    }
    char *del = "/";
    char winPath[PATH_MAX] = {'\0'};
    
    // Checking if current directory is from Windows or WSL
    char *dir = strtok(path, del);
    if (strcmp(dir, "mnt"))
    {
        if (!getWslPath(winPath, dir, del)) return EXIT_FAILURE;
    }
    else
    {
        getWindowsPath(winPath, dir, del);
    }

    // Copiyng to Windows clipboard
    FILE *clipboard = popen("clip.exe", "w");
    if (clipboard == NULL)
    {
        fprintf(stderr, "Copy to clipboard failed!\n");
        return EXIT_FAILURE;
    }

    fwrite(winPath, sizeof(char), strlen(winPath), clipboard);
    pclose(clipboard);
    
    // Printing the result
    printf("%s\n", winPath);
    printf("[*] Copied to clipboard.\n");

    return EXIT_SUCCESS;
}