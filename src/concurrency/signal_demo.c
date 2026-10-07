#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handleSignal(int signalNumber)
{
    if (signalNumber == SIGINT)
    {
        printf("\nSIGINT received!\n");
        printf("Interrupt signal handled successfully.\n");
    }
    else if (signalNumber == SIGTERM)
    {
        printf("\nSIGTERM received!\n");
        printf("Termination signal handled successfully.\n");
    }
}

int main()
{
    printf("\n========================================\n");
    printf("           SIGNAL HANDLING DEMO\n");
    printf("========================================\n");

    printf("\nProcess PID: %d\n", getpid());

    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    printf("\nWaiting for signals...\n");
    printf("Press Ctrl+C to send SIGINT.\n");
    printf("Press Ctrl+Z only if you want to stop the program.\n");

    while (1)
    {
        pause();
    }

    return 0;
}
