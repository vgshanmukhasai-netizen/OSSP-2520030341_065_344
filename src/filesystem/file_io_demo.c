#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char buffer[100];

    printf("\n========================================\n");
    printf("          FILE I/O DEMONSTRATION\n");
    printf("========================================\n");

    fd = open("src/filesystem/demo.txt",
              O_CREAT | O_RDWR,
              0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    char message[] = "Hello from Linux File I/O";

    write(fd, message, strlen(message));

    printf("\nData written successfully.\n");

    lseek(fd, 0, SEEK_SET);

    int bytes = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes] = '\0';

    printf("Data read from file: %s\n", buffer);

    close(fd);

    printf("File closed successfully.\n");

    return 0;
}
