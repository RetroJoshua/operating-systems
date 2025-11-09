#include<stdio.h> 
#include<string.h> 

void main() 
{ 
    int alloc[10][10], max[10][10]; 
    int avail[10], work[10], total[10]; 
    int i, j, k, n, need[10][10]; 
    int m; 
    int count = 0, c = 0; 
    char finish[10]; 
    int safe_sequence[10];
    int iteration = 0;
    
    printf("Enter the no. of processes and resources: "); 
    scanf("%d%d", &n, &m); 
    
    // Initialize finish array - FIXED: changed i<=n to i<n
    for(i = 0; i < n; i++) 
        finish[i] = 'n'; 
    
    printf("Enter the claim matrix:\n"); 
    for(i = 0; i < n; i++) 
        for(j = 0; j < m; j++) 
            scanf("%d", &max[i][j]); 
    
    printf("Enter the allocation matrix:\n"); 
    for(i = 0; i < n; i++) 
        for(j = 0; j < m; j++) 
            scanf("%d", &alloc[i][j]); 
    
    printf("Resource vector: "); 
    for(i = 0; i < m; i++) 
        scanf("%d", &total[i]); 
    
    // Calculate available resources
    for(i = 0; i < m; i++) 
        avail[i] = 0; 
    
    for(i = 0; i < n; i++) 
        for(j = 0; j < m; j++) 
            avail[j] += alloc[i][j]; 
    
    for(i = 0; i < m; i++) 
        work[i] = total[i] - avail[i]; 
    
    // Calculate need matrix
    for(i = 0; i < n; i++) 
        for(j = 0; j < m; j++) 
            need[i][j] = max[i][j] - alloc[i][j]; 
    
    // Display Need Matrix
    printf("\nNeed Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) 
            printf("%4d", need[i][j]);
        printf("\n");
    }
    
    printf("\nInitial Available Resources: ");
    for(i = 0; i < m; i++)
        printf("%4d", work[i]);
    printf("\n\n");
    
    // FIXED: Replaced goto with while loop
    while(count < n) {
        int found = 0;
        
        for(i = 0; i < n; i++) {
            if(finish[i] == 'n') {
                c = 0;
                
                // Check if process can be allocated resources
                for(j = 0; j < m; j++) {
                    if(need[i][j] <= work[j]) 
                        c++; 
                }
                
                if(c == m) {
                    printf("All the resources can be allocated to Process %d", i + 1); 
                    printf("\n\nAvailable resources are: "); 
                    
                    // Release resources
                    for(k = 0; k < m; k++) {
                        work[k] += alloc[i][k]; 
                        printf("%4d", work[k]); 
                    } 
                    printf("\n"); 
                    
                    finish[i] = 'y'; 
                    printf("Process %d executed?: %c\n\n", i + 1, finish[i]); 
                    
                    safe_sequence[count] = i + 1;
                    count++; 
                    found = 1;
                } 
            }
        }
        
        // FIXED: Added check for unsafe state
        if(found == 0) {
            printf("\nSystem is in UNSAFE state!\n");
            printf("Deadlock may occur.\n");
            return;
        }
        
        // FIXED: Added iteration limit to prevent infinite loop
        iteration++;
        if(iteration > n * n) {
            printf("\nError: Too many iterations. System may be in unsafe state.\n");
            return;
        }
    } 
    
    // All processes completed successfully
    printf("\nSystem is in SAFE state\n"); 
    printf("The given state is safe state\n");
    printf("\nSafe Sequence: ");
    for(i = 0; i < count; i++) {
        printf("P%d", safe_sequence[i]);
        if(i < count - 1)
            printf(" -> ");
    }
    printf("\n");
}