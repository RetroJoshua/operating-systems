#include<stdio.h> 
int fr[3]; 
void main() 
{ 
    void display(); 
    int i,j,n,page[50]; 
    int flag1=0,flag2=0,pf=0,frsize=3,top=0; 
    printf("Enter number of pages (max 50): "); scanf("%d",&n);
    printf("Enter %d page numbers: ",n);
    for(i=0;i<n;i++) scanf("%d",&page[i]);
    for(i=0;i<3;i++) 
    { 
        fr[i]=-1; 
    } 
    for(j=0;j<n;j++) 
    { 
        flag1=0; 
        flag2=0; 
        for(i=0;i<3;i++) 
        { 
            if(fr[i]==page[j]) 
            { 
                flag1=1; 
                flag2=1; 
                break; 
            } 
        } 
    if(flag1==0) 
    { 
        for(i=0;i<frsize;i++)   
        { 
            if(fr[i]==-1) 
            { 
                fr[i]=page[j]; 
                flag2=1; 
                break; 
            } 
        } 
    } 
if(flag2==0) 
{ 
    fr[top]=page[j]; 
    top++; 
    pf++; 
    if(top>=frsize) 
        top=0; 
} 
    display(); 
} 
    printf("\nNumber of page faults  : %d ",pf); 
} 
void display() 
{ 
    int i; 
    printf("\n"); 
    for(i=0;i<3;i++) 
        printf("%d\t",fr[i]); 
}