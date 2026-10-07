#include <stdio.h>
#include <dirent.h>

int main()
{
    DIR *dir;
    struct dirent *entry;

    printf("\n========================================\n");
    printf("          DIRECTORY OPERATIONS\n");
    printf("========================================\n");

    dir = opendir("src/filesystem");

    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }

    printf("\nFiles and directories inside src/filesystem:\n\n");

    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    printf("\nDirectory closed successfully.\n");

    return 0;
}
