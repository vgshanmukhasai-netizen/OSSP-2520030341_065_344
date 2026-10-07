#include <stdio.h>

#define MAX 20

void fcfs()
{
    int n, bt[MAX], wt[MAX], tat[MAX];
    float avg_wt = 0, avg_tat = 0;

    printf("\n===== FCFS SCHEDULING =====\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++)
        printf("| P%d ", i + 1);

    printf("|\n");
}

void sjf()
{
    int n, bt[MAX], p[MAX], wt[MAX], tat[MAX];
    float avg_wt = 0, avg_tat = 0;

    printf("\n===== SJF SCHEDULING =====\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;

        printf("Enter burst time for P%d: ", p[i]);
        scanf("%d", &bt[i]);
    }

    /* Sort by burst time */
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j])
            {
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nExecution Order:\n");

    for (int i = 0; i < n; i++)
        printf("P%d ", p[i]);

    printf("\n\nProcess\tBurst\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n",
               p[i], bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++)
        printf("| P%d ", p[i]);

    printf("|\n");
}

void priorityScheduling()
{
    int n, bt[MAX], priority[MAX], p[MAX], wt[MAX], tat[MAX];
    float avg_wt = 0, avg_tat = 0;

    printf("\n===== PRIORITY SCHEDULING =====\n");
    printf("(Smaller priority number = higher priority)\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;

        printf("Enter burst time for P%d: ", p[i]);
        scanf("%d", &bt[i]);

        printf("Enter priority for P%d: ", p[i]);
        scanf("%d", &priority[i]);
    }

    /* Sort by priority */
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (priority[i] > priority[j])
            {
                int temp;

                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nExecution Order:\n");

    for (int i = 0; i < n; i++)
        printf("P%d ", p[i]);

    printf("\n\nProcess\tBurst\tPriority\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t\t%d\t%d\n",
               p[i], bt[i], priority[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++)
        printf("| P%d ", p[i]);

    printf("|\n");
}

void roundRobin()
{
    int n, bt[MAX], remaining[MAX];
    int quantum;
    int time = 0;
    int completed = 0;
    int wt[MAX] = {0};
    int tat[MAX];

    printf("\n===== ROUND ROBIN SCHEDULING =====\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);

        remaining[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    printf("\nExecution Order:\n");

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                printf("P%d ", i + 1);

                if (remaining[i] > quantum)
                {
                    time += quantum;
                    remaining[i] -= quantum;
                }
                else
                {
                    time += remaining[i];
                    remaining[i] = 0;

                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];

                    completed++;
                }
            }
        }
    }

    printf("\n\nProcess\tBurst\tWaiting\tTurnaround\n");

    float avg_wt = 0, avg_tat = 0;

    for (int i = 0; i < n; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];

        printf("P%d\t%d\t%d\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("       PROCESS SCHEDULING\n");
        printf("====================================\n");

        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. Priority Scheduling\n");
        printf("4. Round Robin\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                fcfs();
                break;

            case 2:
                sjf();
                break;

            case 3:
                priorityScheduling();
                break;

            case 4:
                roundRobin();
                break;

            case 5:
                printf("\nExiting scheduler...\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
