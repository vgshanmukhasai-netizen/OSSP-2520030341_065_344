#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "myfifo"

int main()
{
    char message[100];

    /* Create the FIFO */
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo");
    }

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    /* Open FIFO for writing */
    int fd = open(FIFO_NAME, O_WRONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    /* Send message */
    write(fd, message, strlen(message) + 1);

    printf("Message sent successfully.\n");

    close(fd);

    return 0;
}
