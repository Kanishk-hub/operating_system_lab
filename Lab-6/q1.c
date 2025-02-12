#include <stdio.h>
#include <stdlib.h>

#define MAX 20

// Structure to represent a process
struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int priority;
};

// Function to sort processes based on arrival time
void sortByArrival(struct Process processes[], int n)
{
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].arrivalTime > processes[j].arrivalTime)
            {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Preemptive SJF scheduling
void preemptiveSJF(struct Process processes[], int n)
{
    sortByArrival(processes, n);

    int completed = 0, currentTime = 0, shortestBurstTime, shortestProcessIndex;
    int isProcessCompleted[MAX] = {0};

    printf("\nPreemptive SJF Scheduling:\n");
    while (completed < n)
    {
        shortestBurstTime = 9999; // Arbitrarily large number
        shortestProcessIndex = -1;

        // Find the process with the shortest remaining burst time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !isProcessCompleted[i] && processes[i].remainingTime < shortestBurstTime)
            {
                shortestBurstTime = processes[i].remainingTime;
                shortestProcessIndex = i;
            }
        }

        if (shortestProcessIndex == -1)
        {
            currentTime++;
        }
        else
        {
            processes[shortestProcessIndex].remainingTime--;
            currentTime++;

            if (processes[shortestProcessIndex].remainingTime == 0)
            {
                processes[shortestProcessIndex].completionTime = currentTime;
                processes[shortestProcessIndex].turnAroundTime = processes[shortestProcessIndex].completionTime - processes[shortestProcessIndex].arrivalTime;
                processes[shortestProcessIndex].waitingTime = processes[shortestProcessIndex].turnAroundTime - processes[shortestProcessIndex].burstTime;
                isProcessCompleted[shortestProcessIndex] = 1;
                completed++;
            }
        }
    }

    // Display results
    printf("ID  Arrival  Burst  Completion  Turnaround  Waiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d   %d       %d      %d          %d         %d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, processes[i].turnAroundTime,
               processes[i].waitingTime);
    }
}

// Round Robin scheduling
void roundRobin(struct Process processes[], int n, int quantum)
{
    sortByArrival(processes, n);

    int completed = 0, currentTime = 0;
    int remainingProcesses = n;
    int isProcessCompleted[MAX] = {0};

    printf("\nRound Robin Scheduling:\n");
    while (remainingProcesses > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !isProcessCompleted[i])
            {
                int timeSlice = (processes[i].remainingTime > quantum) ? quantum : processes[i].remainingTime;
                processes[i].remainingTime -= timeSlice;
                currentTime += timeSlice;
                printf("Process %d executed for %d units of time at time %d\n", processes[i].id, timeSlice, currentTime);

                if (processes[i].remainingTime == 0)
                {
                    processes[i].completionTime = currentTime;
                    processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                    isProcessCompleted[i] = 1;
                    remainingProcesses--;
                }
            }
        }
    }

    // Display results
    printf("ID  Arrival  Burst  Completion  Turnaround  Waiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d   %d       %d      %d          %d         %d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, processes[i].turnAroundTime,
               processes[i].waitingTime);
    }
}

// Non-preemptive Priority Scheduling
void priorityScheduling(struct Process processes[], int n)
{
    sortByArrival(processes, n);

    int completed = 0, currentTime = 0;
    int isProcessCompleted[MAX] = {0};

    printf("\nNon-preemptive Priority Scheduling:\n");
    while (completed < n)
    {
        int highestPriority = -1;
        int processIndex = -1;

        // Find the process with the highest priority
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !isProcessCompleted[i])
            {
                if (processes[i].priority > highestPriority)
                {
                    highestPriority = processes[i].priority;
                    processIndex = i;
                }
            }
        }

        if (processIndex != -1)
        {
            currentTime += processes[processIndex].burstTime;
            processes[processIndex].completionTime = currentTime;
            processes[processIndex].turnAroundTime = processes[processIndex].completionTime - processes[processIndex].arrivalTime;
            processes[processIndex].waitingTime = processes[processIndex].turnAroundTime - processes[processIndex].burstTime;
            isProcessCompleted[processIndex] = 1;
            completed++;
        }
    }

    // Display results
    printf("ID  Arrival  Burst  Priority  Completion  Turnaround  Waiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d   %d       %d       %d        %d          %d         %d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].priority, processes[i].completionTime,
               processes[i].turnAroundTime, processes[i].waitingTime);
    }
}

int main()
{
    struct Process processes[MAX];
    int n, quantum, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter details for Process %d\n", i + 1);
        processes[i].id = i + 1;
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // For preemptive SJF and RR
        printf("Priority (higher number means higher priority): ");
        scanf("%d", &processes[i].priority);
    }

    do
    {
        printf("\nMenu:\n");
        printf("1. Preemptive SJF\n");
        printf("2. Round Robin\n");
        printf("3. Non-preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            preemptiveSJF(processes, n);
            break;
        case 2:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &quantum);
            roundRobin(processes, n, quantum);
            break;
        case 3:
            priorityScheduling(processes, n);
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
