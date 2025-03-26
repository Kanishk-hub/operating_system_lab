#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to check if the system is in a safe state
bool isSafe(int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int numProcesses, int numResources, int safeSequence[])
{
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int tempSafeSequence[MAX_PROCESSES];
    int safeCount = 0;

    // Initialize work array with available resources
    for (int i = 0; i < numResources; i++)
    {
        work[i] = available[i];
    }

    int count = 0;
    while (count < numProcesses)
    {
        bool found = false;
        for (int p = 0; p < numProcesses; p++)
        {
            if (!finish[p])
            {
                bool canAllocate = true;
                for (int r = 0; r < numResources; r++)
                {
                    if (need[p][r] > work[r])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int r = 0; r < numResources; r++)
                    {
                        work[r] += allocation[p][r];
                    }
                    finish[p] = true;
                    tempSafeSequence[safeCount++] = p;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
        {
            return false; // Unsafe state
        }
    }

    // Copy the safe sequence to the output array
    for (int i = 0; i < numProcesses; i++)
    {
        safeSequence[i] = tempSafeSequence[i];
    }

    return true; // Safe state
}

// Function to handle resource request
bool resourceRequest(int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int processId, int request[], int numProcesses, int numResources)
{
    // Check if the request is within the need
    for (int i = 0; i < numResources; i++)
    {
        if (request[i] > need[processId][i])
        {
            printf("Error: Request exceeds need.\n");
            return false;
        }
    }

    // Check if the request is within the available resources
    for (int i = 0; i < numResources; i++)
    {
        if (request[i] > available[i])
        {
            printf("Error: Request exceeds available resources.\n");
            return false;
        }
    }

    // Simulate resource allocation
    int tempAvailable[MAX_RESOURCES];
    int tempAllocation[MAX_PROCESSES][MAX_RESOURCES];
    int tempNeed[MAX_PROCESSES][MAX_RESOURCES];

    for (int i = 0; i < numResources; i++)
    {
        tempAvailable[i] = available[i] - request[i];
    }

    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            tempAllocation[i][j] = allocation[i][j];
            tempNeed[i][j] = need[i][j];
        }
    }

    for (int i = 0; i < numResources; i++)
    {
        tempAllocation[processId][i] += request[i];
        tempNeed[processId][i] -= request[i];
    }

    // Check if the resulting state is safe
    int safeSequence[MAX_PROCESSES];
    if (isSafe(tempAvailable, tempAllocation, tempNeed, numProcesses, numResources, safeSequence))
    {
        // Grant the request
        for (int i = 0; i < numResources; i++)
        {
            available[i] -= request[i];
            allocation[processId][i] += request[i];
            need[processId][i] -= request[i];
        }
        printf("Request granted.\n");
        return true;
    }
    else
    {
        printf("Request denied. System would be in an unsafe state.\n");
        return false;
    }
}

int main()
{
    int available[MAX_RESOURCES] = {3, 3, 2};
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int maxResources[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int numProcesses = MAX_PROCESSES;
    int numResources = MAX_RESOURCES;

    // Calculate need matrix
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            need[i][j] = maxResources[i][j] - allocation[i][j];
        }
    }

    printf("Available: ");
    for (int i = 0; i < numResources; i++)
        printf("%d ", available[i]);
    printf("\nAllocation:\n");
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    int safeSequence[MAX_PROCESSES];
    if (isSafe(available, allocation, need, numProcesses, numResources, safeSequence))
    {
        printf("System is in a safe state. Safe sequence: ");
        for (int i = 0; i < numProcesses; i++)
        {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("System is in an unsafe state.\n");
    }

    // Resource request example
    int processId = 1;
    int request[MAX_RESOURCES] = {1, 0, 2};
    resourceRequest(available, allocation, need, processId, request, numProcesses, numResources);
    if (isSafe(available, allocation, need, numProcesses, numResources, safeSequence))
    {
        printf("System is in a safe state. Safe sequence: ");
        for (int i = 0; i < numProcesses; i++)
        {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("System is in an unsafe state.\n");
    }

    processId = 0;
    int request2[MAX_RESOURCES] = {0, 2, 0};
    resourceRequest(available, allocation, need, processId, request2, numProcesses, numResources);

    if (isSafe(available, allocation, need, numProcesses, numResources, safeSequence))
    {
        printf("System is in a safe state. Safe sequence: ");
        for (int i = 0; i < numProcesses; i++)
        {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("System is in an unsafe state.\n");
    }

    return 0;
}