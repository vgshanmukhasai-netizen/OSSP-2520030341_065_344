#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    printf("\n========================================\n");
    printf("      BUFFERED AND UNBUFFERED I/O\n");
    printf("========================================\n");

    /* Buffered I/O using standard C library */
    FILE *file = fopen("src/filesystem/buffered.txt", "w");

    if (file == NULL)
    {
        perror("fopen");
        return 1;
    }

    fprintf(file, "This is Buffered I/O.\n");
    fclose(file);

    printf("\nBuffered I/O completed using fopen() and fprintf().\n");

    /* Unbuffered I/O using system calls */
    int fd = open("src/filesystem/unbuffered.txt",
                  O_CREAT | O_WRONLY | O_TRUNC,
                  0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    char message[] = "This is Unbuffered I/O.\n";

    write(fd, message, strlen(message));

    close(fd);

    printf("Unbuffered I/O completed using open() and write().\n");

    printf("\nBoth files were created successfully.\n");

    return 0;
}
