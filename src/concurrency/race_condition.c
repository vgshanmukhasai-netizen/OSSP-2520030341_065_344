#include <stdio.h>
#include <pthread.h>

long counter = 0;

void *incrementCounter(void *arg)
{
    (void)arg;

    for (int i = 0; i < 1000000; i++)
    {
        counter++;
    }

    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    printf("\n========================================\n");
    printf("           RACE CONDITION DEMO\n");
    printf("========================================\n");

    printf("\nInitial Counter: %ld\n", counter);

    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Expected Counter: 2000000\n");
    printf("Actual Counter  : %ld\n", counter);

    if (counter != 2000000)
    {
        printf("\nRace condition occurred!\n");
        printf("Some updates were lost because both threads accessed the shared variable.\n");
    }
    else
    {
        printf("\nBoth threads completed.\n");
        printf("Run the program again to observe the race condition.\n");
    }

    return 0;
}
