#include <stdio.h>  // Standard input/output library
#include <stdlib.h> // Standard library for memory allocation

// Structure to represent a process
struct process{
    int pid;           // Process ID
    int at;            // Arrival time
    int bt;            // Burst time
    int ct;            // Completion time
    int wt;            // Waiting time
    int tat;           // Turnaround time
    int is_completed;  // Flag to track if process is completed (0 = not completed, 1 = completed)
};

// Comparison function for qsort - sorts by arrival time, then by burst time, then by PID
int cmp_at(const void *a, const void *b){
    const struct process *p1 = a;  // Cast void pointer to process pointer
    const struct process *p2 = b;  // Cast void pointer to process pointer
    
    // First compare by arrival time
    if(p1->at < p2->at) return -1;
    if(p1->at > p2->at) return 1;
    
    // If arrival times are equal, compare by burst time
    if(p1->bt < p2->bt) return -1;
    if(p1->bt > p2->bt) return 1;
    
    // If burst times are equal, compare by PID
    if(p1->pid < p2->pid) return -1;
    if(p1->pid > p2->pid) return 1;
    
    return 0;  // Processes are equal
}

// Main function
int main()
{
    int n;  // Number of processes
    
    // Prompt user for number of processes
    printf("Enter Number of Processes\n");
    scanf("%d",&n);  // Read number of processes
    
    // Allocate memory for processes dynamically
    struct process *processes = malloc(n * sizeof(struct process));
    
    // Check if memory allocation was successful
    if (processes == NULL){
        perror("malloc");  // Print error message
        return 1;          // Exit with error code
    }
    
    // Input process details
    for(int i=0; i<n; i++){
        processes[i].pid = i+1;              // Assign process ID
        printf("Process -%d",i+1);           // Display process number
        printf("\nArrival time ");           // Prompt for arrival time
        scanf("%d",&processes[i].at);        // Read arrival time
        printf("\nBurust time ");            // Prompt for burst time (typo in "Burust")
        scanf("%d",&processes[i].bt);        // Read burst time
        processes[i].wt = 0;                 // Initialize waiting time to 0
        processes[i].ct = 0;                 // Initialize completion time to 0
        processes[i].tat = 0;                // Initialize turnaround time to 0
        processes[i].is_completed = 0;       // Mark process as not completed
    }
    
    // Sort processes based on arrival time, burst time, and PID
    qsort(processes,n,sizeof(struct process),cmp_at);
   
    // Initialize variables for tracking completion
    int completed = 0;     // Number of processes completed
    int current_time = 0;  // Current time in the simulation
    int twt = 0, ttat = 0; // Total waiting time and total turnaround time
   
    // SJF implementation
    while(completed<n){  // Continue until all processes are completed
        int idx = -1;              // Index of selected process (-1 means no process selected)
        int min_bt = 1000000000;   // Initialize minimum burst time to a large value
        
        // Find process with minimum burst time among available processes
        for(int i=0; i<n; i++){
            // Check if process has arrived and is not yet completed
            if(processes[i].at <= current_time && !processes[i].is_completed){
                // If current process has smaller burst time, select it
                if(processes[i].bt < min_bt){
                    min_bt = processes[i].bt;  // Update minimum burst time
                    idx = i;                   // Update selected process index
                }
                
                // If burst times are equal, select process with earlier arrival time
                if(processes[i].bt == min_bt && processes[i].at < processes[idx].at){
                    idx = i;  // Update selected process index
                }
            }
        }
        
        // If no process is available, move to next process arrival time 
        if(idx == -1){
            current_time++;  // Increment current time
        }else{
            // Complete the selected process 
            current_time += processes[idx].bt;        // Update current time
            processes[idx].ct = current_time;         // Set completion time
            processes[idx].tat = processes[idx].ct - processes[idx].at;  // Calculate turnaround time
            processes[idx].wt = processes[idx].tat - processes[idx].bt;   // Calculate waiting time
           
            ttat += processes[idx].tat;  // Add to total turnaround time
            twt += processes[idx].wt;     // Add to total waiting time
            processes[idx].is_completed = 1;  // Mark process as completed
            completed++;                     // Increment completed processes count
        }
    }
    
    // Calculate average waiting time and average turnaround time
    float awt=0, atat=0;
    awt =(float)twt/n;    // Average waiting time
    atat = (float)ttat/n; // Average turnaround time
    
    // Display process details
    for(int i=0;i<n;i++){
        printf("Process \t %d\t arriaval time\t %d\t burust time\t %d\t waiting time\t %d\t tat\t %d\n",
               processes[i].pid, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat);
    }
    
    // Display average times
    printf("Average waiting time %.2f\n",awt);
    printf("Average Turnaround time %.2f",atat);
    
    // Free allocated memory
    free(processes);
    return 0;  // Exit successfully
}