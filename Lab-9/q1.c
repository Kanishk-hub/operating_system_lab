#include <stdio.h>
#include <stdlib.h>

typedef struct Block
{
    int id;
    int size;
    int allocated;
    struct Block *next;
} Block;

typedef struct Process
{
    int id;
    int size;
    struct Process *next;
} Process;

// Function to add a block to the block list
void addBlock(Block **head, int id, int size)
{
    Block *newBlock = (Block *)malloc(sizeof(Block));
    newBlock->id = id;
    newBlock->size = size;
    newBlock->allocated = 0;
    newBlock->next = *head;
    *head = newBlock;
}

// Function to add a process to the process list
void addProcess(Process **head, int id, int size)
{
    Process *newProcess = (Process *)malloc(sizeof(Process));
    newProcess->id = id;
    newProcess->size = size;
    newProcess->next = *head;
    *head = newProcess;
}

// Function to allocate processes using first fit
void firstFit(Block *blockHead, Process *processHead)
{
    Process *currentProcess = processHead;
    while (currentProcess != NULL)
    {
        Block *currentBlock = blockHead;
        while (currentBlock != NULL)
        {
            if (currentBlock->allocated == 0 && currentBlock->size >= currentProcess->size)
            {
                currentBlock->allocated = currentProcess->id;
                printf("Process %d allocated to Block %d (First Fit)\n", currentProcess->id, currentBlock->id);
                break;
            }
            currentBlock = currentBlock->next;
        }
        if (currentBlock == NULL)
        {
            printf("Process %d could not be allocated (First Fit)\n", currentProcess->id);
        }
        currentProcess = currentProcess->next;
    }
}

// Function to allocate processes using best fit
void bestFit(Block *blockHead, Process *processHead)
{
    Process *currentProcess = processHead;
    while (currentProcess != NULL)
    {
        Block *currentBlock = blockHead;
        Block *bestBlock = NULL;
        int minSize = -1;

        while (currentBlock != NULL)
        {
            if (currentBlock->allocated == 0 && currentBlock->size >= currentProcess->size)
            {
                if (bestBlock == NULL || currentBlock->size < minSize)
                {
                    bestBlock = currentBlock;
                    minSize = currentBlock->size;
                }
            }
            currentBlock = currentBlock->next;
        }

        if (bestBlock != NULL)
        {
            bestBlock->allocated = currentProcess->id;
            printf("Process %d allocated to Block %d (Best Fit)\n", currentProcess->id, bestBlock->id);
        }
        else
        {
            printf("Process %d could not be allocated (Best Fit)\n", currentProcess->id);
        }
        currentProcess = currentProcess->next;
    }
}

// Function to free the block list
void freeBlocks(Block *head)
{
    while (head != NULL)
    {
        Block *temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to free the process list
void freeProcesses(Process *head)
{
    while (head != NULL)
    {
        Process *temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    Block *blockHead = NULL;
    Process *processHead = NULL;

    // Add blocks
    addBlock(&blockHead, 1, 100);
    addBlock(&blockHead, 2, 50);
    addBlock(&blockHead, 3, 300);
    addBlock(&blockHead, 4, 200);

    // Add processes
    addProcess(&processHead, 1, 80);
    addProcess(&processHead, 2, 70);
    addProcess(&processHead, 3, 120);
    addProcess(&processHead, 4, 90);

    // First Fit Allocation
    printf("\nFirst Fit Allocation:\n");
    firstFit(blockHead, processHead);

    // Reset block allocations
    Block *tempBlock = blockHead;
    while (tempBlock != NULL)
    {
        tempBlock->allocated = 0;
        tempBlock = tempBlock->next;
    }

    // Best Fit Allocation
    printf("\nBest Fit Allocation:\n");
    bestFit(blockHead, processHead);

    // Free the lists
    freeBlocks(blockHead);
    freeProcesses(processHead);

    return 0;
}