#include <stdio.h>
#include <pthread.h>

long counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *incrementCounter(void *arg)
{
    (void)arg;

    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    printf("\n========================================\n");
    printf("          MUTEX SYNCHRONIZATION\n");
    printf("========================================\n");

    printf("\nInitial Counter: %ld\n", counter);

    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Expected Counter: 2000000\n");
    printf("Actual Counter  : %ld\n", counter);

    if (counter == 2000000)
    {
        printf("\nSynchronization successful!\n");
        printf("No updates were lost.\n");
    }
    else
    {
        printf("\nUnexpected result.\n");
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
