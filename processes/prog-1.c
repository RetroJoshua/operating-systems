#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>  // Added for wait()

int main(int argc, char **argv) 
{ 
    pid_t pid; 
    pid = fork(); 
    
    if(pid == 0) 
    { 
        printf("It is the child process and pid is %d\n", getpid()); 
        exit(0); 
    } 
    else if(pid > 0) 
    { 
        printf("It is the parent process and pid is %d\n", getpid()); 
        wait(NULL);  // Wait for child to prevent zombie process
    } 
    else 
    { 
        printf("Error while forking\n"); 
        exit(EXIT_FAILURE); 
    } 
    
    return 0; 
}