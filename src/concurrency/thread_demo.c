#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *threadFunction(void *arg)
{
    int threadNumber = *(int *)arg;

    for (int i = 1; i <= 5; i++)
    {
        printf("Thread %d: Count = %d\n",
               threadNumber, i);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    int num1 = 1;
    int num2 = 2;

    printf("\n========================================\n");
    printf("          POSIX THREAD DEMO\n");
    printf("========================================\n");

    pthread_create(&thread1, NULL,
                   threadFunction, &num1);

    pthread_create(&thread2, NULL,
                   threadFunction, &num2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nBoth threads completed successfully.\n");

    return 0;
}
