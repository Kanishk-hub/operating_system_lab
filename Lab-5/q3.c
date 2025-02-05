#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubble_sort(char *arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(char *arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(arr[j], arr[min_index]) < 0)
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            char *temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

void quick_sort(char *arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}

int partition(char *arr[], int low, int high)
{
    char *pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (strcmp(arr[j], pivot) < 0)
        {
            i++;
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    char *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int main()
{
    int N;
    printf("Enter the number of strings: ");
    scanf("%d", &N);

    char *arr[N];
    for (int i = 0; i < N; i++)
    {
        arr[i] = (char *)malloc(100 * sizeof(char));
        printf("Enter string %d: ", i + 1);
        scanf("%s", arr[i]);
    }

    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid1 == 0)
    {
        printf("Child 1 (Bubble Sort):\n");
        bubble_sort(arr, N);
        for (int i = 0; i < N; i++)
        {
            printf("%s\n", arr[i]);
        }
        exit(0);
    }
    else
    {
        pid_t pid2 = fork();
        if (pid2 < 0)
        {
            perror("fork failed");
            return 1;
        }

        if (pid2 == 0)
        {
            printf("Child 2 (Quick Sort):\n");
            quick_sort(arr, 0, N - 1);
            for (int i = 0; i < N; i++)
            {
                printf("%s\n", arr[i]);
            }
            exit(0);
        }
        else
        {
            int status;
            waitpid(pid1, &status, 0);
            waitpid(pid2, &status, 0);
            printf("Parent process: One of the child processes has finished.\n");
        }
    }

    for (int i = 0; i < N; i++)
    {
        free(arr[i]);
    }

    return 0;
}
