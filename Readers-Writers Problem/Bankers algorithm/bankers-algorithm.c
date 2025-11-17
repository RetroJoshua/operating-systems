#include<stdio.h> 
#include<conio.h> 
#include<string.h> 
void main() 
{ 
    int alloc[10][10],max[10][10]; 
    int avail[10],work[10],total[10]; 
    int i,j,k,n,need[10][10]; 
    int m; 
    int count=0,c=0; 
    char finish[10]; 
    printf("Enter the no. of processes and resources:"); 
    scanf("%d%d",&n,&m); 
    for(i=0;i<n;i++)  // Bug fix: was i<=n, should be i<n
        finish[i]='n'; 
    printf("Enter the claim matrix:\n"); 
    for(i=0;i<n;i++) 
        for(j=0;j<m;j++) 
            scanf("%d",&max[i][j]); 
    printf("Enter the allocation matrix:\n"); 
    for(i=0;i<n;i++) 
        for(j=0;j<m;j++) 
            scanf("%d",&alloc[i][j]); 
    printf("Resource vector:"); 
    for(i=0;i<m;i++) 
        scanf("%d",&total[i]); 
    for(i=0;i<m;i++) 
        avail[i]=0; 
    for(i=0;i<n;i++) 
        for(j=0;j<m;j++) 
            avail[j]+=alloc[i][j]; 
    for(i=0;i<m;i++) 
        work[i]=total[i]-avail[i];  // Bug fix: simplified logic
    for(i=0;i<n;i++) 
        for(j=0;j<m;j++) 
            need[i][j]=max[i][j]-alloc[i][j]; 
    A:for(i=0;i<n;i++) 
    { 
        c=0;
        for(j=0;j<m;j++) 
        {  // Bug fix: added missing braces
            if((need[i][j]<=work[j])&&(finish[i]=='n')) 
                c++; 
        }
        if(c==m) { 
            printf("All the resources can be allocated to Process %d", i+1); 
            printf("\n\nAvailable resources are:"); 
            for(k=0;k<m;k++) 
            { 
                work[k]+=alloc[i][k]; 
                printf("%4d",work[k]); 
            } 
            printf("\n"); 
            finish[i]='y'; 
            printf("\nProcess %d executed?:%c \n",i+1,finish[i]); 
            count++; 
            goto A;  // Bug fix: restart search after finding a process
        } 
    } 
    if(count==n) 
        printf("\n System is in safe state"); 
    else
        printf("\n System is NOT in safe state"); 
    
    getch();  // Bug fix: added to prevent console from closing
}