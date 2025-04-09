#include <stdio.h>
#include <stdlib.h>

// Structure to represent a real-time task
typedef struct
{
    int id;
    int arrival_time;
    int execution_time;
    int period;   // For Rate Monotonic
    int deadline; // For Earliest Deadline First
    int remaining_time;
    int priority; // For Rate Monotonic (lower period = higher priority)
} Task;

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b)
{
    while (b)
    {
        a %= b;
        int temp = a;
        a = b;
        b = temp;
    }
    return a;
}

// Function to calculate the least common multiple (LCM) of two numbers
int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

// Function to calculate the hyperperiod (LCM of all periods)
int calculate_hyperperiod(Task tasks[], int num_tasks)
{
    if (num_tasks == 0)
    {
        return 0;
    }
    int hp = tasks[0].period;
    for (int i = 1; i < num_tasks; i++)
    {
        hp = lcm(hp, tasks[i].period);
    }
    return hp;
}

// Function to perform Rate Monotonic Scheduling
void rate_monotonic_scheduling(Task tasks[], int num_tasks)
{
    printf("\n--- Rate Monotonic Scheduling ---\n");

    // Assign priorities based on the period (shorter period = higher priority)
    for (int i = 0; i < num_tasks; i++)
    {
        tasks[i].priority = tasks[i].period;
        tasks[i].remaining_time = tasks[i].execution_time;
    }

    int current_time = 0;
    int completed_tasks = 0;
    int hyperperiod = calculate_hyperperiod(tasks, num_tasks);

    printf("Time\tRunning Task\n");

    while (current_time < hyperperiod && completed_tasks < num_tasks)
    {
        int highest_priority_task = -1;

        // Find the highest priority ready task
        for (int i = 0; i < num_tasks; i++)
        {
            if (tasks[i].arrival_time <= current_time && tasks[i].remaining_time > 0)
            {
                if (highest_priority_task == -1 || tasks[i].priority < tasks[highest_priority_task].priority)
                {
                    highest_priority_task = i;
                }
            }
        }

        if (highest_priority_task != -1)
        {
            printf("%d\tTask %d\n", current_time, tasks[highest_priority_task].id);
            tasks[highest_priority_task].remaining_time--;
            if (tasks[highest_priority_task].remaining_time == 0)
            {
                completed_tasks++;
            }
        }
        else
        {
            printf("%d\tIdle\n", current_time);
        }

        current_time++;

        // Handle periodic arrivals
        for (int i = 0; i < num_tasks; i++)
        {
            if (current_time % tasks[i].period == 0)
            {
                tasks[i].remaining_time = tasks[i].execution_time;
            }
        }
    }

    if (completed_tasks == num_tasks)
    {
        printf("All tasks completed successfully within the hyperperiod.\n");
    }
    else
    {
        printf("Some tasks did not complete within the hyperperiod.\n");
    }
}

// Function to perform Earliest Deadline First Scheduling
void earliest_deadline_first_scheduling(Task tasks[], int num_tasks)
{
    printf("\n--- Earliest Deadline First Scheduling ---\n");

    // Initialize remaining times
    for (int i = 0; i < num_tasks; i++)
    {
        tasks[i].remaining_time = tasks[i].execution_time;
    }

    int current_time = 0;
    int completed_tasks = 0;
    int hyperperiod = calculate_hyperperiod(tasks, num_tasks);

    printf("Time\tRunning Task\n");

    while (current_time < hyperperiod && completed_tasks < num_tasks)
    {
        int earliest_deadline_task = -1;
        int min_deadline = -1;

        // Find the task with the earliest deadline among the ready tasks
        for (int i = 0; i < num_tasks; i++)
        {
            if (tasks[i].arrival_time <= current_time && tasks[i].remaining_time > 0)
            {
                int current_deadline = tasks[i].deadline + (current_time / tasks[i].period) * tasks[i].period; // Calculate current instance deadline
                if (earliest_deadline_task == -1 || current_deadline < min_deadline)
                {
                    earliest_deadline_task = i;
                    min_deadline = current_deadline;
                }
            }
        }

        if (earliest_deadline_task != -1)
        {
            printf("%d\tTask %d\n", current_time, tasks[earliest_deadline_task].id);
            tasks[earliest_deadline_task].remaining_time--;
            if (tasks[earliest_deadline_task].remaining_time == 0)
            {
                completed_tasks++;
            }
        }
        else
        {
            printf("%d\tIdle\n", current_time);
        }

        current_time++;

        // Handle periodic arrivals and update deadlines
        for (int i = 0; i < num_tasks; i++)
        {
            if (current_time % tasks[i].period == 0)
            {
                tasks[i].remaining_time = tasks[i].execution_time;
            }
        }
    }

    if (completed_tasks == num_tasks)
    {
        printf("All tasks completed successfully within the hyperperiod.\n");
    }
    else
    {
        printf("Some tasks did not complete within the hyperperiod.\n");
    }
}

int main()
{
    int num_tasks;

    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    Task tasks[num_tasks];

    printf("Enter task details (Arrival Time, Execution Time, Period, Deadline):\n");
    for (int i = 0; i < num_tasks; i++)
    {
        tasks[i].id = i + 1;
        printf("Task %d: ", i + 1);
        scanf("%d %d %d %d", &tasks[i].arrival_time, &tasks[i].execution_time, &tasks[i].period, &tasks[i].deadline);
    }

    // Create copies of the task array for each scheduling algorithm
    Task rm_tasks[num_tasks];
    Task edf_tasks[num_tasks];
    for (int i = 0; i < num_tasks; i++)
    {
        rm_tasks[i] = tasks[i];
        edf_tasks[i] = tasks[i];
    }

    rate_monotonic_scheduling(rm_tasks, num_tasks);
    earliest_deadline_first_scheduling(edf_tasks, num_tasks);

    return 0;
}