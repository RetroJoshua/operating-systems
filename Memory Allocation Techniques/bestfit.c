#include <stdio.h>
#define max 25

int main()
{
    int frag[max], b[max], f[max], i, j, nb, nf, temp, lowest = 10000;
    static int bf[max], ff[max];
    
    printf("\nEnter the number of blocks:");
    scanf("%d", &nb);
    printf("Enter the number of files:");
    scanf("%d", &nf);
    
    printf("\nEnter the size of the blocks:-\n");
    for (i = 1; i <= nb; i++)
    {
        printf("Block %d:", i);
        scanf("%d", &b[i]);
    }
    
    printf("Enter the size of the files :-\n");
    for (i = 1; i <= nf; i++)
    {
        printf("File %d:", i);
        scanf("%d", &f[i]);
    }
    
    for (i = 1; i <= nf; i++)
    {
        lowest = 10000;
        ff[i] = 0;  // Initialize to 0 (no block allocated)
        
        for (j = 1; j <= nb; j++)
        {
            if (bf[j] != 1)  // If block is not allocated
            {
                temp = b[j] - f[i];
                if (temp >= 0)  // If file fits in block
                {
                    if (lowest > temp)  // If this is the best fit so far
                    {
                        ff[i] = j;
                        lowest = temp;
                    }
                }
            }
        }
        
        // Only allocate if a suitable block was found
        if (ff[i] != 0)
        {
            frag[i] = lowest;  // Store fragment
            bf[ff[i]] = 1;     // Mark block as allocated
        }
        else
        {
            frag[i] = -1;  // Indicate allocation failure
        }
    }
    
    printf("\nFile No\tFile Size \tBlock No\tBlock Size\tFragment");
    for (i = 1; i <= nf; i++)
    {
        if (ff[i] != 0)
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
        else
            printf("\n%d\t\t%d\t\tNot Allocated", i, f[i]);
    }
    
    printf("\n");
    return 0;
}