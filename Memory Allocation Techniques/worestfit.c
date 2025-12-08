#include<stdio.h> 
#define max 25 

int main() 
{ 
    int frag[max],b[max],f[max],i,j,nb,nf,temp,highest; 
    static int bf[max],ff[max]; 

    printf("\n\tMemory Management Scheme - Worst Fit"); 
    printf("\nEnter the number of blocks:"); 
    scanf("%d",&nb); 
    printf("Enter the number of files:"); 
    scanf("%d",&nf); 

    printf("\nEnter the size of the blocks:-\n");
    for(i=0;i<nb;i++) // Changed loop to 0-indexed for consistency
    { 
        printf("Block %d:",i+1); // Displaying 1-indexed for user
        scanf("%d",&b[i]); 
    } 

    printf("Enter the size of the files :-\n"); 
    for(i=0;i<nf;i++) // Changed loop to 0-indexed for consistency
    { 
        printf("File %d:",i+1); // Displaying 1-indexed for user
        scanf("%d",&f[i]); 
    } 

    // Initialize bf and ff arrays
    for(i=0; i<nb; i++) bf[i] = 0;
    for(i=0; i<nf; i++) ff[i] = -1; // Initialize with -1 to indicate no block assigned

    for(i=0;i<nf;i++) // Loop through files (0-indexed)
    { 
        highest=-1; // Reset highest for each file
        int worst_fit_block_idx = -1; // To store the index of the worst fit block

        for(j=0;j<nb;j++) // Loop through blocks (0-indexed)
        { 
            if(bf[j]!=1) // If block is not allocated
            { 
                temp=b[j]-f[i]; 
                if(temp>=0) // If block is large enough
                {
                    if(temp > highest) // Find the block with the largest remaining space
                    {
                        highest=temp;
                        worst_fit_block_idx = j; // Store the index of this block
                    }
                } 
            } 
        } 

        if(worst_fit_block_idx != -1) // If a suitable block was found
        {
            ff[i]=worst_fit_block_idx; // Assign the block index to the file
            frag[i]=highest; // Store the fragmentation
            bf[worst_fit_block_idx]=1; // Mark the block as allocated
        } else {
            frag[i] = -1; // Indicate that the file could not be allocated
        }
    } 

    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:\tFragment"); 
    for(i=0;i<nf;i++) // Loop through files (0-indexed)
    { 
        if(ff[i] != -1) { // If the file was allocated
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i+1,f[i],ff[i]+1,b[ff[i]],frag[i]); 
        } else {
            printf("\n%d\t\t%d\t\tNot Allocated\t\t--\t\t--",i+1,f[i]);
        }
    } 
    printf("\n"); // Add a newline at the end for better formatting
    return 0; // Standard practice for int main()
}