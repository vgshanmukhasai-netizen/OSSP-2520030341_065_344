#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

int globalVariable = 100;

void virtualMemoryDemo()
{
    int n;

    printf("\n========================================\n");
    printf("          VIRTUAL MEMORY DEMO\n");
    printf("========================================\n");

    printf("\nEnter number of integers to allocate: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("\nInvalid size.\n");
        return;
    }

    int *memory = malloc(n * sizeof(int));

    if (memory == NULL)
    {
        perror("malloc");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        memory[i] = (i + 1) * 10;
    }

    printf("\nMemory allocated successfully.\n");
    printf("Process PID       : %d\n", getpid());
    printf("Virtual address   : %p\n", (void *)memory);
    printf("Allocated bytes   : %zu\n", n * sizeof(int));

    printf("\nStored values:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Address %p -> %d\n",
               (void *)&memory[i],
               memory[i]);
    }

    free(memory);

    printf("\nMemory released successfully using free().\n");
}

void addressTranslationDemo()
{
    int virtualAddress;
    int pageSize = 100;

    int pageTable[4] = {2, 0, 3, 1};

    printf("\n========================================\n");
    printf("          ADDRESS TRANSLATION\n");
    printf("========================================\n");

    printf("\nPage Size: %d bytes\n", pageSize);

    printf("\nPage Table:\n");

    for (int i = 0; i < 4; i++)
    {
        printf("Page %d -> Frame %d\n", i, pageTable[i]);
    }

    printf("\nEnter virtual address (0 - 399): ");
    scanf("%d", &virtualAddress);

    if (virtualAddress < 0 || virtualAddress >= 400)
    {
        printf("\nInvalid virtual address.\n");
        return;
    }

    int pageNumber = virtualAddress / pageSize;
    int offset = virtualAddress % pageSize;

    int frameNumber = pageTable[pageNumber];

    int physicalAddress =
        frameNumber * pageSize + offset;

    printf("\nTranslation Result\n");
    printf("----------------------------\n");
    printf("Virtual Address : %d\n", virtualAddress);
    printf("Page Number     : %d\n", pageNumber);
    printf("Offset          : %d\n", offset);
    printf("Frame Number    : %d\n", frameNumber);
    printf("Physical Address: %d\n", physicalAddress);
}

void pageFaultDemo()
{
    int pages[4] = {1, 0, 1, 0};
    int page;
    int found = 0;

    printf("\n========================================\n");
    printf("            PAGE FAULT DEMO\n");
    printf("========================================\n");

    printf("\nCurrent resident pages: 0 1\n");

    printf("Enter page number to access (0 - 3): ");
    scanf("%d", &page);

    if (page < 0 || page > 3)
    {
        printf("\nInvalid page number.\n");
        return;
    }

    for (int i = 0; i < 2; i++)
    {
        if (pages[i] == page)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\nPage %d is already in memory.\n", page);
        printf("Result: PAGE HIT\n");
    }
    else
    {
        printf("\nPage %d is not in memory.\n", page);
        printf("Result: PAGE FAULT\n");

        printf("Loading page %d into memory...\n", page);

        pages[0] = pages[1];
        pages[1] = page;

        printf("Page loaded successfully.\n");
        printf("Current resident pages: %d %d\n",
               pages[0], pages[1]);
    }
}

void fifoPageReplacement()
{
    int pages[50];
    int frames[3] = {-1, -1, -1};

    int n;
    int pointer = 0;
    int faults = 0;

    printf("\n========================================\n");
    printf("        FIFO PAGE REPLACEMENT\n");
    printf("========================================\n");

    printf("\nNumber of page references: ");
    scanf("%d", &n);

    if (n <= 0 || n > 50)
    {
        printf("\nInvalid number of references.\n");
        return;
    }

    printf("Enter page reference string:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("\nProcessing pages...\n\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < 3; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("Page %d -> PAGE FAULT\n", page);

            frames[pointer] = page;
            pointer = (pointer + 1) % 3;

            faults++;
        }
        else
        {
            printf("Page %d -> HIT\n", page);
        }

        printf("Frames: ");

        for (int j = 0; j < 3; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        printf("\n");
    }

    printf("\n========================================\n");
    printf("Total References : %d\n", n);
    printf("Total Page Faults: %d\n", faults);
    printf("Total Hits       : %d\n", n - faults);
    printf("========================================\n");
}

void dynamicMemoryDemo()
{
    int n;

    printf("\n========================================\n");
    printf("       DYNAMIC MEMORY ALLOCATION\n");
    printf("========================================\n");

    printf("\nEnter number of integers: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("\nInvalid size.\n");
        return;
    }

    int *arr = malloc(n * sizeof(int));

    if (arr == NULL)
    {
        perror("malloc");
        return;
    }

    printf("\nMemory allocated using malloc().\n");
    printf("Address: %p\n", (void *)arr);

    for (int i = 0; i < n; i++)
    {
        arr[i] = (i + 1) * 10;
    }

    printf("\nValues stored:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    int newSize;

    printf("\nEnter new size for realloc(): ");
    scanf("%d", &newSize);

    if (newSize <= 0)
    {
        free(arr);
        printf("\nMemory released.\n");
        return;
    }

    int *temp = realloc(arr, newSize * sizeof(int));

    if (temp == NULL)
    {
        printf("\nReallocation failed.\n");
        free(arr);
        return;
    }

    arr = temp;

    printf("\nMemory resized successfully using realloc().\n");
    printf("New address: %p\n", (void *)arr);

    for (int i = n; i < newSize; i++)
    {
        arr[i] = (i + 1) * 10;
    }

    printf("Updated values:\n");

    for (int i = 0; i < newSize; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    free(arr);

    printf("\nMemory released using free().\n");
}

void processMemoryDemo()
{
    int localVariable = 10;

    static int staticVariable = 20;

    int *heapVariable = malloc(sizeof(int));

    if (heapVariable == NULL)
    {
        perror("malloc");
        return;
    }

    *heapVariable = 30;

    printf("\n========================================\n");
    printf("        PROCESS ADDRESS SPACE\n");
    printf("========================================\n");

    printf("\nProcess PID: %d\n", getpid());

    printf("\nMemory Regions\n");
    printf("----------------------------------------\n");

    printf("Text / Code address : %p\n",
           (void *)(uintptr_t)processMemoryDemo);

    printf("Global variable     : %p\n",
           (void *)&globalVariable);

    printf("Static variable     : %p\n",
           (void *)&staticVariable);

    printf("Heap variable       : %p\n",
           (void *)heapVariable);

    printf("Stack variable      : %p\n",
           (void *)&localVariable);

    printf("\nValues\n");
    printf("----------------------------------------\n");

    printf("Global : %d\n", globalVariable);
    printf("Static : %d\n", staticVariable);
    printf("Heap   : %d\n", *heapVariable);
    printf("Stack  : %d\n", localVariable);

    free(heapVariable);

    printf("\nHeap memory released.\n");
}

void procMemoryDemo()
{
    FILE *file;
    char line[256];

    printf("\n========================================\n");
    printf("       LINUX /PROC MEMORY INFORMATION\n");
    printf("========================================\n");

    printf("\nProcess PID: %d\n", getpid());

    file = fopen("/proc/self/status", "r");

    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    printf("\nReal Linux memory information:\n");
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "VmPeak:", 7) == 0 ||
            strncmp(line, "VmSize:", 7) == 0 ||
            strncmp(line, "VmRSS:", 6) == 0 ||
            strncmp(line, "VmData:", 7) == 0 ||
            strncmp(line, "VmStk:", 6) == 6 ||
            strncmp(line, "VmExe:", 6) == 6 ||
            strncmp(line, "VmLib:", 6) == 6)
        {
            printf("%s", line);
        }
    }

    fclose(file);

    printf("\nInformation obtained directly from /proc.\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n========================================\n");
        printf("          CO-4 MEMORY MANAGEMENT\n");
        printf("========================================\n");

        printf("1. Virtual Memory\n");
        printf("2. Address Translation\n");
        printf("3. Page Fault\n");
        printf("4. FIFO Page Replacement\n");
        printf("5. Dynamic Memory Allocation\n");
        printf("6. Process Address Space\n");
        printf("7. Linux /proc Memory Information\n");
        printf("8. Exit\n");

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
                virtualMemoryDemo();
                break;

            case 2:
                addressTranslationDemo();
                break;

            case 3:
                pageFaultDemo();
                break;

            case 4:
                fifoPageReplacement();
                break;

            case 5:
                dynamicMemoryDemo();
                break;

            case 6:
                processMemoryDemo();
                break;

            case 7:
                procMemoryDemo();
                break;

            case 8:
                printf("\nExiting CO-4 module...\n");
                return 0;

            default:
                printf("\nInvalid choice. Select 1-8.\n");
        }
    }

    return 0;
}
