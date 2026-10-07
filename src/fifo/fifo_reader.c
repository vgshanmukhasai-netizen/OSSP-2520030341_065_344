#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

int main()
{
    char buffer[100];

    printf("Waiting for message...\n");

    /* Open FIFO for reading */
    int fd = open(FIFO_NAME, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    /* Receive message */
    read(fd, buffer, sizeof(buffer));

    printf("Message received: %s\n", buffer);

    close(fd);

    return 0;
}
