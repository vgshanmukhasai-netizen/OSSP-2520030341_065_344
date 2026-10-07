#include <stdio.h>
#include <sys/stat.h>

int main()
{
    struct stat fileInfo;

    printf("\n========================================\n");
    printf("          FILE METADATA\n");
    printf("========================================\n");

    if (stat("src/filesystem/demo.txt", &fileInfo) == -1)
    {
        perror("stat");
        return 1;
    }

    printf("\nFile: src/filesystem/demo.txt\n");

    printf("File Size       : %ld bytes\n", fileInfo.st_size);
    printf("Inode Number    : %ld\n", fileInfo.st_ino);
    printf("Link Count      : %ld\n", fileInfo.st_nlink);
    printf("File Permissions: %o\n",
           fileInfo.st_mode & 0777);

    printf("\nMetadata retrieved successfully.\n");

    return 0;
}
