#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// FIFO Page Replacement
int fifoPageReplacement(int *pages, int numPages, int numFrames)
{
    int *frames = (int *)malloc(sizeof(int) * numFrames);
    int *frameUsage = (int *)malloc(sizeof(int) * numFrames);
    int frameIndex = 0;
    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
        frameUsage[i] = 0;
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
                break;
            }
        }

        if (!pageFound)
        {
            pageFaults++;
            frames[frameIndex] = page;
            frameUsage[frameIndex] = i;
            frameIndex = (frameIndex + 1) % numFrames;
        }
    }

    free(frames);
    free(frameUsage);
    return pageFaults;
}

// Optimal Page Replacement
int optimalPageReplacement(int *pages, int numPages, int numFrames)
{
    int *frames = (int *)malloc(sizeof(int) * numFrames);
    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
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
                break;
            }
        }

        if (!pageFound)
        {
            pageFaults++;
            int replaceIndex = -1;
            int farthest = -1;

            for (int j = 0; j < numFrames; j++)
            {
                int futureIndex = -1;
                for (int k = i + 1; k < numPages; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        futureIndex = k;
                        break;
                    }
                }
                if (futureIndex == -1)
                {
                    replaceIndex = j;
                    break;
                }
                if (futureIndex > farthest)
                {
                    farthest = futureIndex;
                    replaceIndex = j;
                }
            }
            frames[replaceIndex] = page;
        }
    }

    free(frames);
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

    printf("\nFIFO Page Replacement: Page Faults = %d\n", fifoPageReplacement(pages, numPages, numFrames));
    printf("Optimal Page Replacement: Page Faults = %d\n", optimalPageReplacement(pages, numPages, numFrames));

    free(pages);
    return 0;
}