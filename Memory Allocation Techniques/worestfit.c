#include <stdio.h>
#define MAX 25

int main(void)
{
    int frag[MAX], b[MAX], f[MAX];
    int i, j, nb, nf, temp, highest;
    static int bf[MAX], ff[MAX];

    printf("\n\tMemory Management Scheme - Worst Fit");
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    // Optional: basic bounds check
    if (nb > MAX || nf > MAX) {
        printf("Error: nb and nf must each be <= %d\n", MAX);
        return 1;
    }

    printf("\nEnter the size of the blocks:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    printf("Enter the size of the files:\n");
    for (i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &f[i]);
    }

    // Initialize bf and ff arrays
    for (i = 0; i < nb; i++)
        bf[i] = 0;      // 0 = free, 1 = allocated

    for (i = 0; i < nf; i++)
        ff[i] = -1;     // -1 = no block assigned

    // Worst Fit allocation
    for (i = 0; i < nf; i++) {
        int worst_fit_block_idx;   // ✅ Declare at start of block

        highest = -1;              // Reset highest for each file
        worst_fit_block_idx = -1;  // No block chosen yet

        for (j = 0; j < nb; j++) {
            if (bf[j] != 1) {     // Block is free
                temp = b[j] - f[i];
                if (temp >= 0) {  // Block can accommodate file
                    if (temp > highest) {
                        highest = temp;
                        worst_fit_block_idx = j;
                    }
                }
            }
        }

        if (worst_fit_block_idx != -1) {  // A suitable block was found
            ff[i] = worst_fit_block_idx;  // Assign block index to file
            frag[i] = highest;            // Fragmentation
            bf[worst_fit_block_idx] = 1;  // Mark block as allocated
        } else {
            frag[i] = -1;                 // File could not be allocated
        }
    }

    printf("\nFile_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment");
    for (i = 0; i < nf; i++) {
        if (ff[i] != -1) {
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",
                   i + 1,
                   f[i],
                   ff[i] + 1,
                   b[ff[i]],
                   frag[i]);
        } else {
            printf("\n%d\t\t%d\t\tNot Allocated\t--\t\t--",
                   i + 1,
                   f[i]);
        }
    }

    printf("\n");
    return 0;
}