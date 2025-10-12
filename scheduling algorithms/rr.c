// Include standard input/output functions (printf, scanf, etc.)
#include <stdio.h>   
// Include standard library functions (malloc, free, qsort, etc.)  
#include <stdlib.h>  

/* Define a structure to represent a process */
struct process {
    int pid;        // Process ID (assigned sequentially)
    int at;         // Arrival time of the process
    int bt;         // Original burst time (total CPU time needed)
    int rem_bt;     // Remaining burst time (decreases during execution)
    int ct;         // Completion time (when process finishes)
    int wt;         // Waiting time (time spent in ready queue)
    int tat;        // Turnaround time (total time from arrival to completion)
    int is_completed; // Flag to indicate if the process is completed (1 = yes, 0 = no)
};

/* Comparator function for qsort: sorts processes by arrival time, then burst time, then PID */
int cmp_at(const void *a, const void *b) {
    // Cast the generic pointers to process pointers
    const struct process *p1 = (const struct process *)a; 
    const struct process *p2 = (const struct process *)b; 

    // If arrival times differ, sort by arrival time (earlier first)
    if (p1->at != p2->at)                
        return p1->at - p2->at;         

    // If arrival times are same, sort by burst time (shorter first)
    if (p1->bt != p2->bt)               
        return p1->bt - p2->bt;         

    // If both arrival and burst times are same, sort by PID (lower first)
    return p1->pid - p2->pid;           
}

/* Simple dynamic circular queue to hold indices of processes */
typedef struct {
    int *data;   /* buffer to store process indices */
    int cap;     /* capacity of the buffer */
    int front;   /* index of the front element in the queue */
    int size;    /* number of elements currently in the queue */
} Queue;

/* Initialize queue with given capacity (must be > 0) */
int queue_init(Queue *q, int initial_cap) {
    // If initial capacity is not positive, set it to 4
    if (initial_cap <= 0) initial_cap = 4;
    // Allocate memory for the queue buffer
    q->data = malloc(initial_cap * sizeof(int));
    // Check if memory allocation was successful
    if (!q->data) return -1;
    // Set the capacity of the queue
    q->cap = initial_cap;
    // Initialize front index to 0
    q->front = 0;
    // Initialize size to 0
    q->size = 0;
    // Return 0 to indicate success
    return 0;
}

/* Free queue resources */
void queue_free(Queue *q) {
    // Free the memory allocated for the queue buffer
    free(q->data);
    // Set the buffer pointer to NULL to avoid dangling pointer
    q->data = NULL;
    // Reset capacity, front index, and size to 0
    q->cap = q->front = q->size = 0;
}

/* Ensure there's room for at least one more element; doubles capacity if full */
int queue_ensure_capacity(Queue *q) {
    // If the queue is not full, no need to resize
    if (q->size < q->cap) return 0;
    // Calculate the new capacity (double the current capacity)
    int newcap = q->cap * 2;
    // Allocate memory for the new buffer
    int *newdata = malloc(newcap * sizeof(int));
    // Check if memory allocation was successful
    if (!newdata) return -1;
    /* Copy elements in order from the old buffer to the new buffer */
    for (int i = 0; i < q->size; ++i) {
        // Copy each element to the new buffer
        newdata[i] = q->data[(q->front + i) % q->cap];
    }
    // Free the old buffer
    free(q->data);
    // Point the queue buffer to the new buffer
    q->data = newdata;
    // Update the capacity of the queue
    q->cap = newcap;
    // Reset the front index to 0
    q->front = 0;
    // Return 0 to indicate success
    return 0;
}

/* Enqueue an index at the back */
int queue_enqueue(Queue *q, int value) {
    // Ensure there is enough capacity in the queue
    if (queue_ensure_capacity(q) != 0) return -1;
    // Calculate the index of the back element
    int back = (q->front + q->size) % q->cap;
    // Store the value at the back of the queue
    q->data[back] = value;
    // Increment the size of the queue
    q->size++;
    // Return 0 to indicate success
    return 0;
}

/* Dequeue an index from the front; returns -1 if empty, else value >= 0 */
int queue_dequeue(Queue *q) {
    // If the queue is empty, return -1
    if (q->size == 0) return -1;
    // Get the value at the front of the queue
    int val = q->data[q->front];
    // Move the front index to the next element (circular)
    q->front = (q->front + 1) % q->cap;
    // Decrement the size of the queue
    q->size--;
    // Return the dequeued value
    return val;
}

/* Check if queue is empty */
int queue_empty(Queue *q) {
    // Return 1 if the queue is empty, 0 otherwise
    return q->size == 0;
}

/* Main function: entry point of the program */
int main(void) {
    // Variable to store the number of processes
    int n;                            

    /* Prompt the user to enter the number of processes */
    printf("Enter Number of Processes: ");
    // Read the number of processes and validate input
    if (scanf("%d", &n) != 1 || n <= 0) { 
        // If input is invalid or non-positive, print error and exit
        fprintf(stderr, "Invalid number of processes.\n");
        return 1;
    }

    /* Allocate memory for 'n' process structures */
    struct process *processes = malloc(n * sizeof(struct process));
    // Check if memory allocation was successful
    if (!processes) {
        // If not, print error message and exit
        perror("malloc failed");
        return 1;
    }

    /* Loop to read arrival time and burst time for each process */
    for (int i = 0; i < n; ++i) {
        // Assign a process ID (1-based index)
        processes[i].pid = i + 1;      
        // Print prompt for current process
        printf("Process %d:\n", i + 1);

        // Prompt for arrival time
        printf("  Arrival Time: ");
        // Read arrival time and validate input
        if (scanf("%d", &processes[i].at) != 1) {
            // If invalid, print error, free memory, and exit
            fprintf(stderr, "Invalid input for arrival time.\n");
            free(processes);
            return 1;
        }

        // Prompt for burst time
        printf("  Burst Time: ");
        // Read burst time and validate input (must be positive)
        if (scanf("%d", &processes[i].bt) != 1 || processes[i].bt <= 0) {
            // If invalid, print error, free memory, and exit
            fprintf(stderr, "Invalid burst time.\n");
            free(processes);
            return 1;
        }

        // Initialize remaining burst time to original burst time
        processes[i].rem_bt = processes[i].bt;
        // Initialize completion, waiting, and turnaround times to 0
        processes[i].ct = processes[i].wt = processes[i].tat = 0;
        // Mark the process as not completed
        processes[i].is_completed = 0;
    }

    /* Print the processes before sorting (for debugging/clarity) */
    printf("\n--- Before Sorting ---\n");
    for (int i = 0; i < n; ++i) {
        // Print PID, arrival time, and burst time
        printf("P%d\tAT=%d\tBT=%d\n", processes[i].pid, processes[i].at, processes[i].bt);
    }

    /* Sort the processes array using qsort and the cmp_at comparator */
    qsort(processes, n, sizeof(struct process), cmp_at);

    // Variable to store the time quantum for Round Robin scheduling
    int time_quantum;
    // Prompt the user to enter the time quantum
    printf("Enter time quantum: ");
    // Read the time quantum and validate input (must be positive)
    if (scanf("%d", &time_quantum) != 1 || time_quantum <= 0) {
        // If invalid, print error, free memory, and exit
        fprintf(stderr, "Time quantum must be a positive integer.\n");
        free(processes);
        return 1;
    }

    /* Prepare queue */
    Queue q;
    // Initialize the queue with a capacity slightly larger than n
    if (queue_init(&q, n + 4) != 0) {
        // If initialization fails, print error, free memory, and exit
        perror("queue init failed");
        free(processes);
        return 1;
    }

    // Index of the next process (in sorted array) not yet enqueued
    int next = 0;        
    // Number of completed processes
    int completed = 0;   
    // Current simulation time, initialized to the arrival time of the first process (or 0 if none)
    int current_time = (n > 0) ? processes[0].at : 0;

    /* Enqueue all processes that have arrived at or before current_time */
    while (next < n && processes[next].at <= current_time) {
        // Enqueue the index of the process
        if (queue_enqueue(&q, next) != 0) { 
            // If enqueue fails, print error, free memory, and exit
            perror("enqueue"); 
            free(processes); 
            queue_free(&q); 
            return 1; 
        }
        // Move to the next process in the sorted array
        next++;
    }

    /* Main RR scheduling loop: run until all processes are completed */
    while (completed < n) {
        // If the ready queue is empty
        if (queue_empty(&q)) {
            // If there are processes that haven't arrived yet
            if (next < n) {
                // Jump to the arrival time of the next process
                current_time = processes[next].at;
                // Enqueue all processes that arrive at this new current time
                while (next < n && processes[next].at <= current_time) {
                    // Enqueue the index of the process
                    if (queue_enqueue(&q, next) != 0) { 
                        // If enqueue fails, print error, free memory, and exit
                        perror("enqueue"); 
                        free(processes); 
                        queue_free(&q); 
                        return 1; 
                    }
                    // Move to the next process in the sorted array
                    next++;
                }
                // Continue to the next iteration of the loop
                continue;
            } else {
                /* No processes left to arrive and queue is empty => done */
                break;
            }
        }

        // Dequeue the next ready process index
        int idx = queue_dequeue(&q);
        // If dequeue fails (shouldn't happen), continue to the next iteration
        if (idx < 0) continue; 

        // Determine the execution time for this quantum (minimum of remaining burst and time quantum)
        int exec = (processes[idx].rem_bt < time_quantum) ? processes[idx].rem_bt : time_quantum;
        // Execute the process for 'exec' time units and decrement remaining burst
        processes[idx].rem_bt -= exec;
        // Advance the simulation time
        current_time += exec;

        /* Enqueue any processes that arrived while this process was executing */
        while (next < n && processes[next].at <= current_time) {
            // Enqueue the index of the process
            if (queue_enqueue(&q, next) != 0) { 
                // If enqueue fails, print error, free memory, and exit
                perror("enqueue"); 
                free(processes); 
                queue_free(&q); 
                return 1; 
            }
            // Move to the next process in the sorted array
            next++;
        }

        // If the process has finished
        if (processes[idx].rem_bt == 0) {
            // Record the completion time
            processes[idx].ct = current_time;                      
            // Calculate turnaround time
            processes[idx].tat = processes[idx].ct - processes[idx].at; 
            // Calculate waiting time
            processes[idx].wt = processes[idx].tat - processes[idx].bt; 
            // Mark the process as completed
            processes[idx].is_completed = 1;                      
            // Increment the completed process count
            completed++;                                          
        } else {
            // If not finished, re-enqueue the process at the back of the queue
            if (queue_enqueue(&q, idx) != 0) { 
                // If enqueue fails, print error, free memory, and exit
                perror("enqueue"); 
                free(processes); 
                queue_free(&q); 
                return 1; 
            }
        }
    }

    /* Compute and print results */
    // Variables to accumulate total waiting and turnaround times for averaging
    double total_wt = 0.0, total_tat = 0.0;
    // Print the results header
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    // Loop through all processes to print results
    for (int i = 0; i < n; ++i) {
        // Print PID, arrival time, burst time, completion time, turnaround time, and waiting time
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid, processes[i].at, processes[i].bt,
               processes[i].ct, processes[i].tat, processes[i].wt);
        // Accumulate waiting time
        total_wt += processes[i].wt;
        // Accumulate turnaround time
        total_tat += processes[i].tat;
    }
    // Print average waiting time
    printf("Average WT = %.2f\n", total_wt / n);
    // Print average turnaround time
    printf("Average TAT = %.2f\n", total_tat / n);

    /* Clean up memory */
    // Free the memory allocated for the queue
    queue_free(&q);
    // Free the memory allocated for the processes array
    free(processes);
    // Return 0 to indicate successful execution
    return 0;
}