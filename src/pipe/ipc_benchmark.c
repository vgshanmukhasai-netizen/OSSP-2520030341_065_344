#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define FIFO_NAME "ipc_benchmark_fifo"

double getTime()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

int writeAll(int fd, char *buffer, size_t size)
{
    size_t total = 0;

    while (total < size)
    {
        ssize_t written = write(fd, buffer + total, size - total);

        if (written < 0)
        {
            if (errno == EINTR)
                continue;

            return -1;
        }

        total += written;
    }

    return 0;
}

int readAll(int fd, char *buffer, size_t size)
{
    size_t total = 0;

    while (total < size)
    {
        ssize_t bytes = read(fd, buffer + total, size - total);

        if (bytes < 0)
        {
            if (errno == EINTR)
                continue;

            return -1;
        }

        if (bytes == 0)
            break;

        total += bytes;
    }

    return total == size ? 0 : -1;
}

double benchmarkPipe(size_t messageSize, int messageCount)
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return -1;
    }

    char *buffer = malloc(messageSize);

    if (buffer == NULL)
    {
        perror("malloc");
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }

    memset(buffer, 'A', messageSize);

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        free(buffer);
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }

    if (pid == 0)
    {
        close(pipefd[1]);

        char *receiveBuffer = malloc(messageSize);

        if (receiveBuffer == NULL)
            exit(1);

        for (int i = 0; i < messageCount; i++)
        {
            if (readAll(pipefd[0], receiveBuffer, messageSize) == -1)
            {
                free(receiveBuffer);
                close(pipefd[0]);
                exit(1);
            }
        }

        free(receiveBuffer);
        close(pipefd[0]);

        exit(0);
    }

    close(pipefd[0]);

    double start = getTime();

    for (int i = 0; i < messageCount; i++)
    {
        if (writeAll(pipefd[1], buffer, messageSize) == -1)
        {
            perror("pipe write");
            break;
        }
    }

    close(pipefd[1]);

    waitpid(pid, NULL, 0);

    double end = getTime();

    free(buffer);

    return end - start;
}

double benchmarkFIFO(size_t messageSize, int messageCount)
{
    unlink(FIFO_NAME);

    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo");

        return -1;
    }

    char *buffer = malloc(messageSize);

    if (buffer == NULL)
    {
        perror("malloc");
        unlink(FIFO_NAME);
        return -1;
    }

    memset(buffer, 'B', messageSize);

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        free(buffer);
        unlink(FIFO_NAME);
        return -1;
    }

    if (pid == 0)
    {
        int fd = open(FIFO_NAME, O_RDONLY);

        if (fd == -1)
            exit(1);

        char *receiveBuffer = malloc(messageSize);

        if (receiveBuffer == NULL)
        {
            close(fd);
            exit(1);
        }

        for (int i = 0; i < messageCount; i++)
        {
            if (readAll(fd, receiveBuffer, messageSize) == -1)
            {
                free(receiveBuffer);
                close(fd);
                exit(1);
            }
        }

        free(receiveBuffer);
        close(fd);

        exit(0);
    }

    int fd = open(FIFO_NAME, O_WRONLY);

    if (fd == -1)
    {
        perror("FIFO open");

        free(buffer);
        unlink(FIFO_NAME);

        waitpid(pid, NULL, 0);

        return -1;
    }

    double start = getTime();

    for (int i = 0; i < messageCount; i++)
    {
        if (writeAll(fd, buffer, messageSize) == -1)
        {
            perror("FIFO write");
            break;
        }
    }

    close(fd);

    waitpid(pid, NULL, 0);

    double end = getTime();

    free(buffer);

    unlink(FIFO_NAME);

    return end - start;
}

int main()
{
    int messageSizeKB;
    int messageCount;

    printf("\n============================================\n");
    printf("           IPC PERFORMANCE ANALYZER\n");
    printf("============================================\n");

    printf("\nThis test compares Anonymous Pipe and Named FIFO.\n");
    printf("Both mechanisms will transfer the same amount of data.\n");

    printf("\nEnter message size in KB: ");
    scanf("%d", &messageSizeKB);

    printf("Enter number of messages: ");
    scanf("%d", &messageCount);

    if (messageSizeKB <= 0 || messageCount <= 0)
    {
        printf("\nInvalid input.\n");
        return 1;
    }

    size_t messageSize = (size_t)messageSizeKB * 1024;

    double totalMB =
        ((double)messageSize * messageCount) /
        (1024.0 * 1024.0);

    printf("\n============================================\n");
    printf("              TEST CONFIGURATION\n");
    printf("============================================\n");

    printf("Message Size       : %d KB\n", messageSizeKB);
    printf("Number of Messages : %d\n", messageCount);
    printf("Total Data         : %.2f MB\n", totalMB);

    printf("\nRunning Anonymous Pipe test...\n");

    double pipeTime =
        benchmarkPipe(messageSize, messageCount);

    if (pipeTime < 0)
    {
        printf("Pipe benchmark failed.\n");
        return 1;
    }

    printf("Pipe test completed.\n");

    printf("\nRunning Named FIFO test...\n");

    double fifoTime =
        benchmarkFIFO(messageSize, messageCount);

    if (fifoTime < 0)
    {
        printf("FIFO benchmark failed.\n");
        return 1;
    }

    printf("FIFO test completed.\n");

    double pipeThroughput =
        totalMB / pipeTime;

    double fifoThroughput =
        totalMB / fifoTime;

    printf("\n============================================\n");
    printf("             PERFORMANCE RESULTS\n");
    printf("============================================\n");

    printf("\nAnonymous Pipe\n");
    printf("--------------------------------------------\n");
    printf("Time       : %.6f seconds\n", pipeTime);
    printf("Throughput : %.2f MB/s\n", pipeThroughput);

    printf("\nNamed FIFO\n");
    printf("--------------------------------------------\n");
    printf("Time       : %.6f seconds\n", fifoTime);
    printf("Throughput : %.2f MB/s\n", fifoThroughput);

    printf("\n============================================\n");
    printf("                 COMPARISON\n");
    printf("============================================\n");

    if (pipeTime < fifoTime)
    {
        double improvement =
            ((fifoTime - pipeTime) / fifoTime) * 100.0;

        printf("\nFaster Method : Anonymous Pipe\n");
        printf("Time Difference: %.6f seconds\n",
               fifoTime - pipeTime);
        printf("Relative Advantage: %.2f%%\n",
               improvement);
    }
    else if (fifoTime < pipeTime)
    {
        double improvement =
            ((pipeTime - fifoTime) / pipeTime) * 100.0;

        printf("\nFaster Method : Named FIFO\n");
        printf("Time Difference: %.6f seconds\n",
               pipeTime - fifoTime);
        printf("Relative Advantage: %.2f%%\n",
               improvement);
    }
    else
    {
        printf("\nBoth methods completed in approximately the same time.\n");
    }

    printf("\n============================================\n");
    printf("          BENCHMARK COMPLETED\n");
    printf("============================================\n");

    return 0;
}
