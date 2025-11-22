// C implementation of First-Fit algorithm
#include <stdio.h>

// Function to allocate memory to blocks as per First fit algorithm
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int i, j;
    // Stores block id of the block allocated to a process
    int allocation[n];
    
    // Create a copy of blockSize to preserve original values
    int availableBlock[m];
    for (i = 0; i < m; i++)
    {
        availableBlock[i] = blockSize[i];
    }

    // Initially no block is assigned to any process
    for (i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    // Pick each process and find suitable blocks
    // according to its size and assign to it
    for (i = 0; i < n; i++) // n -> number of processes
    {
        for (j = 0; j < m; j++) // m -> number of blocks
        {
            if (availableBlock[j] >= processSize[i])
            {
                // Allocating block j to the ith process
                allocation[i] = j;

                // Reduce available memory in this block
                availableBlock[j] -= processSize[i];

                break; // Go to the next process in the queue
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++)
    {
        printf(" %d\t\t%d KB\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Driver code
int main()
{
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    printf("Memory Blocks: ");
    for (int i = 0; i < m; i++)
        printf("%d KB ", blockSize[i]);
    printf("\n");

    firstFit(blockSize, m, processSize, n);

    return 0;
}