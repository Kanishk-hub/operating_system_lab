#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// LRU Page Replacement
int lruPageReplacement(int *pages, int numPages, int numFrames)
{
    int *frames = (int *)malloc(sizeof(int) * numFrames);
    int *lastUsed = (int *)malloc(sizeof(int) * numFrames);
    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
        lastUsed[i] = 0;
    }

    for (int i = 0; i < numPages; i++)
    {
        int page = pages[i];
        int pageFound = 0;

        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j] == page)
            {
                pageFound = 1;
                lastUsed[j] = i;
                break;
            }
        }

        if (!pageFound)
        {
            pageFaults++;
            int replaceIndex = -1;
            int oldestUsed = INT_MAX;

            for (int j = 0; j < numFrames; j++)
            {
                if (lastUsed[j] < oldestUsed)
                {
                    oldestUsed = lastUsed[j];
                    replaceIndex = j;
                }
            }
            frames[replaceIndex] = page;
            lastUsed[replaceIndex] = i;
        }
    }

    free(frames);
    free(lastUsed);
    return pageFaults;
}

int main()
{
    int numPages, numFrames;

    printf("Enter number of pages: ");
    scanf("%d", &numPages);

    int *pages = (int *)malloc(sizeof(int) * numPages);

    printf("Enter page reference string: ");
    for (int i = 0; i < numPages; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &numFrames);

    printf("\nLRU Page Replacement: Page Faults = %d\n", lruPageReplacement(pages, numPages, numFrames));

    free(pages);
    return 0;
}