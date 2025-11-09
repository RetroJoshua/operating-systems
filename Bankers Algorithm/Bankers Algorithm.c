#include<stdio.h> 

void main() 
{ 
    int alloc[10][10], max[10][10], avail[10], work[10], total[10];
    int i, j, n, m, count = 0, c, safe[10];
    char finish[10];
    
    printf("Enter the no. of processes and resources: "); 
    scanf("%d%d", &n, &m); 
    
    for(i = 0; i < n; i++) finish[i] = 'n'; 
    
    printf("Enter the claim matrix:\n"); 
    for(i = 0; i < n; i++) 
        for(j = 0; j < m; j++) scanf("%d", &max[i][j]); 
    
    printf("Enter the allocation matrix:\n"); 
    for(i = 0; i < n; i++) 
        for(j = 0; j < m; j++) scanf("%d", &alloc[i][j]); 
    
    printf("Resource vector: "); 
    for(i = 0; i < m; i++) scanf("%d", &total[i]); 
    
    // Calculate available resources
    for(i = 0; i < m; i++) {
        work[i] = total[i];
        for(j = 0; j < n; j++) work[i] -= alloc[j][i];
    }
    
    printf("\nInitial Available: ");
    for(i = 0; i < m; i++) printf("%4d", work[i]);
    printf("\n\n");
    
    // Find safe sequence
    while(count < n) {
        int found = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 'n') {
                for(c = 0, j = 0; j < m; j++) 
                    if(max[i][j] - alloc[i][j] <= work[j]) c++;
                
                if(c == m) {
                    printf("Process P%d allocated. Available: ", i + 1);
                    for(j = 0; j < m; j++) printf("%4d", work[j] += alloc[i][j]);
                    printf("\n");
                    finish[i] = 'y';
                    safe[count++] = i + 1;
                    found = 1;
                }
            }
        }
        if(!found) {
            printf("\nSystem is UNSAFE!\n");
            return;
        }
    }
    
    printf("\nSystem is SAFE\nSafe Sequence: ");
    for(i = 0; i < count; i++) printf("%sP%d", i ? " -> " : "", safe[i]);
    printf("\n");
}