#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t resource1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1Function(void *arg)
{
    (void)arg;

    printf("\nThread 1: Trying to lock Resource 1...\n");
    pthread_mutex_lock(&resource1);

    printf("Thread 1: Resource 1 locked.\n");

    sleep(1);

    printf("Thread 1: Trying to lock Resource 2...\n");

    if (pthread_mutex_trylock(&resource2) != 0)
    {
        printf("Thread 1: Resource 2 is already locked.\n");
        printf("Thread 1: Possible deadlock detected!\n");
    }
    else
    {
        printf("Thread 1: Resource 2 locked.\n");
        pthread_mutex_unlock(&resource2);
    }

    pthread_mutex_unlock(&resource1);

    return NULL;
}

void *thread2Function(void *arg)
{
    (void)arg;

    printf("\nThread 2: Trying to lock Resource 2...\n");
    pthread_mutex_lock(&resource2);

    printf("Thread 2: Resource 2 locked.\n");

    sleep(1);

    printf("Thread 2: Trying to lock Resource 1...\n");

    if (pthread_mutex_trylock(&resource1) != 0)
    {
        printf("Thread 2: Resource 1 is already locked.\n");
        printf("Thread 2: Possible deadlock detected!\n");
    }
    else
    {
        printf("Thread 2: Resource 1 locked.\n");
        pthread_mutex_unlock(&resource1);
    }

    pthread_mutex_unlock(&resource2);

    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    printf("\n========================================\n");
    printf("           DEADLOCK DETECTION\n");
    printf("========================================\n");

    printf("\nTwo threads will attempt to access two resources.\n");

    pthread_create(&thread1, NULL, thread1Function, NULL);
    pthread_create(&thread2, NULL, thread2Function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nDeadlock detection demonstration completed.\n");

    pthread_mutex_destroy(&resource1);
    pthread_mutex_destroy(&resource2);

    return 0;
}
