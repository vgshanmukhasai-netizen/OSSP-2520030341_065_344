#include <stdio.h>
#include <stdlib.h>

#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define RED     "\033[1;31m"

void pauseScreen()
{
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void showProjectInfo()
{
    printf("\n============================================\n");
    printf("             PROJECT INFORMATION\n");
    printf("============================================\n");

    printf("\nProject: Linux Inter-Process Communication\n");
    printf("Using Pipes and FIFOs\n");

    printf("\nImplemented Modules:\n");
    printf("--------------------------------------------\n");
    printf("CO-2 : Process Scheduling\n");
    printf("CO-3 : Pipes, FIFOs and IPC\n");
    printf("CO-4 : Memory Management\n");
    printf("CO-5 : File System Operations\n");
    printf("CO-6 : Concurrency and Synchronization\n");

    printf("\nIPC Features:\n");
    printf("- Anonymous Pipe Communication\n");
    printf("- Named Pipe / FIFO Communication\n");
    printf("- Bidirectional Pipe Communication\n");
    printf("- IPC Performance Analyzer\n");

    printf("\nProcess Features:\n");
    printf("- Linux Process Monitor\n");
    printf("- PID and PPID Information\n");
    printf("- Process State\n");
    printf("- Process Memory Information\n");

    printf("\nCO-5 Operations:\n");
    printf("- File I/O\n");
    printf("- File Metadata\n");
    printf("- Directory Operations\n");
    printf("- Buffered / Unbuffered I/O\n");
    printf("- Memory-Mapped Files\n");

    printf("\nCO-6 Operations:\n");
    printf("- POSIX Threads\n");
    printf("- Race Condition\n");
    printf("- Mutex Synchronization\n");
    printf("- Signal Handling\n");
    printf("- Deadlock Detection\n");
}

void co5Menu()
{
    int choice;

    while (1)
    {
        printf("\n============================================\n");
        printf("           CO-5 FILE SYSTEM OPERATIONS\n");
        printf("============================================\n");

        printf("\n1. File I/O\n");
        printf("2. File Metadata\n");
        printf("3. Directory Operations\n");
        printf("4. Buffered / Unbuffered I/O\n");
        printf("5. Memory-Mapped File\n");
        printf("6. Back to Main Menu\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf(RED "\nInvalid input.\n" RESET);
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                system("./bin/file_io_demo");
                pauseScreen();
                break;

            case 2:
                system("./bin/file_metadata");
                pauseScreen();
                break;

            case 3:
                system("./bin/directory_demo");
                pauseScreen();
                break;

            case 4:
                system("./bin/buffer_demo");
                pauseScreen();
                break;

            case 5:
                system("./bin/mmap_demo");
                pauseScreen();
                break;

            case 6:
                return;

            default:
                printf(RED "\nInvalid choice. Select 1-6.\n" RESET);
        }
    }
}

void co6Menu()
{
    int choice;

    while (1)
    {
        printf("\n============================================\n");
        printf("       CO-6 CONCURRENCY & SYNCHRONIZATION\n");
        printf("============================================\n");

        printf("\n1. POSIX Thread Demonstration\n");
        printf("2. Race Condition\n");
        printf("3. Mutex Synchronization\n");
        printf("4. Signal Handling\n");
        printf("5. Deadlock Detection\n");
        printf("6. Back to Main Menu\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf(RED "\nInvalid input.\n" RESET);
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                system("./bin/thread_demo");
                pauseScreen();
                break;

            case 2:
                system("./bin/race_condition");
                pauseScreen();
                break;

            case 3:
                system("./bin/mutex_demo");
                pauseScreen();
                break;

            case 4:
                printf("\nStarting signal demonstration...\n");
                printf("Press Ctrl+C to send SIGINT.\n");
                system("./bin/signal_demo");
                break;

            case 5:
                system("./bin/deadlock_demo");
                pauseScreen();
                break;

            case 6:
                return;

            default:
                printf(RED "\nInvalid choice. Select 1-6.\n" RESET);
        }
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf(CYAN "============================================\n" RESET);
        printf(CYAN "       LINUX IPC & OS SYSTEM PROJECT\n" RESET);
        printf(CYAN "============================================\n" RESET);

        printf("\n");

        printf(GREEN "[1] " RESET
               "Anonymous Pipe Demonstration\n");

        printf(GREEN "[2] " RESET
               "Named Pipe (FIFO) Demonstration\n");

        printf(GREEN "[3] " RESET
               "IPC Performance Analyzer\n");

        printf(GREEN "[4] " RESET
               "Bidirectional Pipe Communication\n");

        printf(GREEN "[5] " RESET
               "Process Monitor\n");

        printf(GREEN "[6] " RESET
               "Process Scheduling Simulator\n");

        printf(GREEN "[7] " RESET
               "Memory Management (CO-4)\n");

        printf(GREEN "[8] " RESET
               "File System Operations (CO-5)\n");

        printf(GREEN "[9] " RESET
               "Concurrency & Synchronization (CO-6)\n");

        printf(GREEN "[10] " RESET
               "Project Information\n");

        printf(RED "[11] " RESET
               "Exit\n");

        printf(YELLOW "\nEnter your choice: " RESET);

        if (scanf("%d", &choice) != 1)
        {
            printf(RED
                   "\nInvalid input! Enter a number from 1 to 11.\n"
                   RESET);

            while (getchar() != '\n');

            continue;
        }

        switch (choice)
        {
            case 1:
                printf("\nStarting Anonymous Pipe Demonstration...\n");
                system("./bin/pipe_demo");
                pauseScreen();
                break;

            case 2:
                printf("\n============================================\n");
                printf("          NAMED PIPE / FIFO DEMO\n");
                printf("============================================\n");

                printf("\nTerminal 1 - Reader:\n");
                printf("cd ~/linux_ipc_project\n");
                printf("./bin/fifo_reader\n");

                printf("\nTerminal 2 - Writer:\n");
                printf("cd ~/linux_ipc_project\n");
                printf("./bin/fifo_writer\n");

                pauseScreen();
                break;

            case 3:
                printf("\n============================================\n");
                printf("        IPC PERFORMANCE ANALYZER\n");
                printf("============================================\n");

                printf("\nComparing Anonymous Pipe and Named FIFO...\n");

                system("./bin/ipc_benchmark");

                pauseScreen();
                break;

            case 4:
                printf("\n============================================\n");
                printf("      BIDIRECTIONAL PIPE COMMUNICATION\n");
                printf("============================================\n");

                printf("\nParent -> Child -> Parent communication\n");
                printf("Starting demonstration...\n\n");

                system("./bin/bidirectional_pipe");

                pauseScreen();
                break;

            case 5:
                printf("\nStarting Linux Process Monitor...\n");

                system("./bin/process_monitor");

                break;

            case 6:
                printf("\nStarting Process Scheduling Simulator...\n");

                system("./bin/scheduler");

                break;

            case 7:
                printf("\nStarting CO-4 Memory Management...\n");

                system("./bin/memory_manager");

                break;

            case 8:
                co5Menu();
                break;

            case 9:
                co6Menu();
                break;

            case 10:
                showProjectInfo();
                pauseScreen();
                break;

            case 11:
                printf(GREEN
                       "\nProject closed successfully.\n"
                       RESET);

                return 0;

            default:
                printf(RED
                       "\nInvalid choice. Select 1-11.\n"
                       RESET);
        }
    }

    return 0;
}
