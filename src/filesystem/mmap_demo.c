#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
    const char *filename = "src/filesystem/mmap_file.txt";
    const int size = 4096;

    printf("\n========================================\n");
    printf("        MEMORY-MAPPED FILE DEMO\n");
    printf("========================================\n");

    int fd = open(filename, O_CREAT | O_RDWR, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    if (ftruncate(fd, size) == -1)
    {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    char *mapped = mmap(NULL,
                        size,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED,
                        fd,
                        0);

    if (mapped == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    strcpy(mapped, "Hello from Memory-Mapped File!");

    printf("\nData written through memory mapping:\n");
    printf("%s\n", mapped);

    if (munmap(mapped, size) == -1)
    {
        perror("munmap");
        close(fd);
        return 1;
    }

    close(fd);

    printf("\nMemory mapping released successfully.\n");
    printf("File closed successfully.\n");

    return 0;
}
