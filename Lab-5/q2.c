#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

void sort_strings(char *arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(arr[i], arr[j]) > 0)
            {
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please provide some strings as command-line arguments.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process (Sorted Strings):\n");
        sort_strings(argv + 1, argc - 1);
        for (int i = 1; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("Parent Process (Unsorted Strings):\n");
        for (int i = 1; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }
    }

    return 0;
}
