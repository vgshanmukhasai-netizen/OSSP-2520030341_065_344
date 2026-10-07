#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int parentToChild[2];
    int childToParent[2];

    char parentMessage[] = "Hello Child! This is Parent.";
    char childMessage[] = "Hello Parent! Message received successfully.";

    char buffer[200];

    printf("\n============================================\n");
    printf("        BIDIRECTIONAL PIPE COMMUNICATION\n");
    printf("============================================\n");

    if (pipe(parentToChild) == -1)
    {
        perror("pipe");
        return 1;
    }

    if (pipe(childToParent) == -1)
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
        /* Parent */

        close(parentToChild[0]);
        close(childToParent[1]);

        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID : %d\n", pid);

        printf("\nParent -> Child\n");
        printf("Sending: %s\n", parentMessage);

        write(parentToChild[1],
              parentMessage,
              strlen(parentMessage) + 1);

        close(parentToChild[1]);

        memset(buffer, 0, sizeof(buffer));

        read(childToParent[0],
             buffer,
             sizeof(buffer));

        printf("\nChild -> Parent\n");
        printf("Received: %s\n", buffer);

        close(childToParent[0]);

        wait(NULL);

        printf("\nTwo-way communication completed successfully.\n");
    }
    else
    {
        /* Child */

        close(parentToChild[1]);
        close(childToParent[0]);

        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());

        read(parentToChild[0],
             buffer,
             sizeof(buffer));

        printf("\nParent -> Child\n");
        printf("Received: %s\n", buffer);

        close(parentToChild[0]);

        printf("\nChild -> Parent\n");
        printf("Sending: %s\n", childMessage);

        write(childToParent[1],
              childMessage,
              strlen(childMessage) + 1);

        close(childToParent[1]);
    }

    return 0;
}
