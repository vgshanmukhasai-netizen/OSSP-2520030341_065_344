#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

void showProcessDetails(int pid)
{
    char path[256];
    char line[256];

    snprintf(path, sizeof(path), "/proc/%d/status", pid);

    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("\nProcess %d no longer exists.\n", pid);
        return;
    }

    printf("\n============================================\n");
    printf("          PROCESS DETAILS\n");
    printf("============================================\n");

    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "Name:", 5) == 0 ||
            strncmp(line, "State:", 6) == 0 ||
            strncmp(line, "Pid:", 4) == 0 ||
            strncmp(line, "PPid:", 5) == 0 ||
            strncmp(line, "Threads:", 8) == 0 ||
            strncmp(line, "VmSize:", 7) == 0 ||
            strncmp(line, "VmRSS:", 6) == 0 ||
            strncmp(line, "VmData:", 7) == 0 ||
            strncmp(line, "VmStk:", 6) == 0)
        {
            printf("%s", line);
        }
    }

    fclose(file);

    printf("============================================\n");
}

void listProcesses()
{
    DIR *directory;
    struct dirent *entry;

    directory = opendir("/proc");

    if (directory == NULL)
    {
        perror("opendir");
        return;
    }

    printf("\n========================================================\n");
    printf("              LIVE PROCESS MONITOR\n");
    printf("========================================================\n");

    printf("%-8s %-8s %-5s %-25s %-12s\n",
           "PID", "PPID", "STATE", "PROCESS", "MEMORY");

    printf("--------------------------------------------------------\n");

    while ((entry = readdir(directory)) != NULL)
    {
        if (!isdigit((unsigned char)entry->d_name[0]))
            continue;

        int pid = atoi(entry->d_name);

        char path[256];
        char line[256];

        snprintf(path, sizeof(path),
                 "/proc/%d/status", pid);

        FILE *file = fopen(path, "r");

        if (file == NULL)
            continue;

        char name[100] = "unknown";
        char state = '?';
        int ppid = 0;
        char memory[50] = "unknown";

        while (fgets(line, sizeof(line), file))
        {
            if (strncmp(line, "Name:", 5) == 0)
            {
                sscanf(line, "Name:\t%99[^\n]", name);
            }
            else if (strncmp(line, "State:", 6) == 0)
            {
                sscanf(line, "State:\t%c", &state);
            }
            else if (strncmp(line, "PPid:", 5) == 0)
            {
                sscanf(line, "PPid:\t%d", &ppid);
            }
            else if (strncmp(line, "VmRSS:", 6) == 0)
            {
                sscanf(line, "VmRSS:\t%49[^\n]", memory);
            }
        }

        fclose(file);

        printf("%-8d %-8d %-5c %-25s %-12s\n",
               pid,
               ppid,
               state,
               name,
               memory);
    }

    closedir(directory);

    printf("========================================================\n");
}

void searchProcess()
{
    int pid;

    printf("\nEnter PID to inspect: ");
    scanf("%d", &pid);

    if (pid <= 0)
    {
        printf("\nInvalid PID.\n");
        return;
    }

    showProcessDetails(pid);
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n============================================\n");
        printf("             PROCESS MONITOR\n");
        printf("============================================\n");

        printf("\n1. Show Running Processes\n");
        printf("2. Inspect Process by PID\n");
        printf("3. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input.\n");

            while (getchar() != '\n');

            continue;
        }

        switch (choice)
        {
            case 1:
                listProcesses();
                break;

            case 2:
                searchProcess();
                break;

            case 3:
                printf("\nExiting Process Monitor...\n");
                return 0;

            default:
                printf("\nInvalid choice. Select 1-3.\n");
        }
    }

    return 0;
}
