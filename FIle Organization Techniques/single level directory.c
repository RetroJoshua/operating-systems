#include<stdio.h>

// Structure to represent a directory
struct Directory {
    char name[20];
    int fileCount;
    char files[20][20];
};

int main() 
{ 
    struct Directory directories[20];
    int master;
    int i, j;
    
    printf("Enter number of directories: ");
    scanf("%d", &master);
    
    // Input directory information
    for(i = 0; i < master; i++) {
        printf("\nDirectory %d:\n", i + 1);
        
        printf("  Enter directory name: ");
        scanf("%s", directories[i].name);
        
        printf("  Enter number of files: ");
        scanf("%d", &directories[i].fileCount);
        
        printf("  Enter file names:\n");
        for(j = 0; j < directories[i].fileCount; j++) {
            printf("    File %d: ", j + 1);
            scanf("%s", directories[i].files[j]);
        }
    }
    
    // Display directory structure
    printf("\n\n");
    printf("=================================================\n");
    printf(" Directory\t\tSize\tFilenames\n");
    printf("=================================================\n");
    
    for(i = 0; i < master; i++) 
    { 
        printf("%-20s\t%2d\t", directories[i].name, directories[i].fileCount);
        
        for(j = 0; j < directories[i].fileCount; j++) {
            if(j == 0)
                printf("%s\n", directories[i].files[j]);
            else
                printf("\t\t\t\t%s\n", directories[i].files[j]);
        }
        printf("\n");
    }
    printf("=================================================\n");
    
    return 0;
}