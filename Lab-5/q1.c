#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("This is the child process.\n");
    }
    else
    {
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("This is the parent process.\n");
    }

    return 0;
}
