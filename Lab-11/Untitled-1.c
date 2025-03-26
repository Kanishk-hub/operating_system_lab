#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

// Function to calculate absolute difference
int abs_diff(int a, int b)
{
    return abs(a - b);
}

// Function to sort the request array
void sort_requests(int requests[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (requests[i] > requests[j])
            {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
}

// SSTF Scheduling
void SSTF(int disk[], int n, int initial_position)
{
    int seek_count = 0, distance, cur_track, min_distance, min_index;
    int visited[MAX] = {0};
    int current_position = initial_position;

    for (int i = 0; i < n; i++)
    {
        min_distance = 10000;
        min_index = -1;

        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                distance = abs_diff(current_position, disk[j]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }

        visited[min_index] = 1;
        cur_track = disk[min_index];
        seek_count += min_distance;

        printf("Move from %d to %d with seek distance %d\n", current_position, cur_track, min_distance);
        current_position = cur_track; // Update current position
    }

    printf("Total Seek Count: %d\n", seek_count);
}

// SCAN Scheduling
void SCAN(int disk[], int n, int initial_position, int total_tracks)
{
    sort_requests(disk, n);
    int seek_count = 0, left[MAX], right[MAX];
    int total_left = 0, total_right = 0;

    // Divide the requests into left and right of the initial position
    for (int i = 0; i < n; i++)
    {
        if (disk[i] < initial_position)
        {
            left[total_left++] = disk[i];
        }
        else
        {
            right[total_right++] = disk[i];
        }
    }

    // Move towards left first
    for (int i = total_left - 1; i >= 0; i--)
    {
        seek_count += abs_diff(initial_position, left[i]);
        printf("Move from %d to %d with seek distance %d\n", initial_position, left[i], abs_diff(initial_position, left[i]));
        initial_position = left[i];
    }

    // Move towards right
    for (int i = 0; i < total_right; i++)
    {
        seek_count += abs_diff(initial_position, right[i]);
        printf("Move from %d to %d with seek distance %d\n", initial_position, right[i], abs_diff(initial_position, right[i]));
        initial_position = right[i];
    }

    printf("Total Seek Count: %d\n", seek_count);
}

// C-SCAN Scheduling
void CSCAN(int disk[], int n, int initial_position, int total_tracks)
{
    sort_requests(disk, n);
    int seek_count = 0;
    int left[MAX], right[MAX];
    int total_left = 0, total_right = 0;

    // Divide the requests into left and right of the initial position
    for (int i = 0; i < n; i++)
    {
        if (disk[i] < initial_position)
        {
            left[total_left++] = disk[i];
        }
        else
        {
            right[total_right++] = disk[i];
        }
    }

    // Move towards right first
    for (int i = 0; i < total_right; i++)
    {
        seek_count += abs_diff(initial_position, right[i]);
        printf("Move from %d to %d with seek distance %d\n", initial_position, right[i], abs_diff(initial_position, right[i]));
        initial_position = right[i];
    }

    // After reaching the right end, go to the leftmost position
    seek_count += abs_diff(initial_position, total_tracks - 1);
    printf("Move from %d to %d with seek distance %d\n", initial_position, total_tracks - 1, abs_diff(initial_position, total_tracks - 1));

    initial_position = 0; // Go back to the leftmost end

    // Then, move towards the right again
    for (int i = 0; i < total_left; i++)
    {
        seek_count += abs_diff(initial_position, left[i]);
        printf("Move from %d to %d with seek distance %d\n", initial_position, left[i], abs_diff(initial_position, left[i]));
        initial_position = left[i];
    }

    printf("Total Seek Count: %d\n", seek_count);
}

// C-LOOK Scheduling
void CLOOK(int disk[], int n, int initial_position)
{
    sort_requests(disk, n);
    int seek_count = 0;
    int left[MAX], right[MAX];
    int total_left = 0, total_right = 0;

    // Divide the requests into left and right of the initial position
    for (int i = 0; i < n; i++)
    {
        if (disk[i] < initial_position)
        {
            left[total_left++] = disk[i];
        }
        else
        {
            right[total_right++] = disk[i];
        }
    }

    // Move towards right first
    for (int i = 0; i < total_right; i++)
    {
        seek_count += abs_diff(initial_position, right[i]);
        printf("Move from %d to %d with seek distance %d\n", initial_position, right[i], abs_diff(initial_position, right[i]));
        initial_position = right[i];
    }

    // Then, move to the leftmost position and continue
    if (total_left > 0)
    {
        seek_count += abs_diff(initial_position, left[total_left - 1]);
        printf("Move from %d to %d with seek distance %d\n", initial_position, left[total_left - 1], abs_diff(initial_position, left[total_left - 1]));
        initial_position = left[total_left - 1];

        // Move towards left
        for (int i = total_left - 2; i >= 0; i--)
        {
            seek_count += abs_diff(initial_position, left[i]);
            printf("Move from %d to %d with seek distance %d\n", initial_position, left[i], abs_diff(initial_position, left[i]));
            initial_position = left[i];
        }
    }

    printf("Total Seek Count: %d\n", seek_count);
}

// Main function to display the menu and call scheduling algorithms
int main()
{
    int disk[MAX], n, initial_position, total_tracks, choice;
    while (1)
    {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. SSTF\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. C-LOOK\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5)
        {
            break;
        }

        printf("Enter the number of disk requests: ");
        scanf("%d", &n);

        printf("Enter the disk requests: ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &disk[i]);
        }

        printf("Enter the initial head position: ");
        scanf("%d", &initial_position);

        printf("Enter the total number of tracks: ");
        scanf("%d", &total_tracks);

        switch (choice)
        {
        case 1:
            SSTF(disk, n, initial_position);
            break;
        case 2:
            SCAN(disk, n, initial_position, total_tracks);
            break;
        case 3:
            CSCAN(disk, n, initial_position, total_tracks);
            break;
        case 4:
            CLOOK(disk, n, initial_position);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return 0;
}
