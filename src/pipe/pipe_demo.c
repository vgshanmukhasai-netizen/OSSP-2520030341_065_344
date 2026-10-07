#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    char message[] = "Hello from Parent Process";
    char buffer[100];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        /* Parent process */
        close(fd[0]);

        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID : %d\n", pid);

        printf("Parent: Sending message...\n");

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);

        wait(NULL);

        printf("Parent: Child process completed.\n");
    }
    else
    {
        /* Child process */
        close(fd[1]);

        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());

        read(fd[0], buffer, sizeof(buffer));

        printf("Child: Received message: %s\n", buffer);

        close(fd[0]);
    }

    return 0;
}
