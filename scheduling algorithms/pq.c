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
    int priority;  // Priority of the process (lower number means higher priority)
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

/* Priority queue implementation using binary heap */
typedef struct {
    int *data;      // Array to store indices of processes
    int size;       // Current number of elements in the heap
    int capacity;   // Maximum capacity of the heap
    struct process *processes; // Pointer to the processes array for priority comparison
} PriorityQueue;

/* Initialize priority queue */
int pq_init(PriorityQueue *pq, int capacity, struct process *processes) {
    pq->data = malloc(capacity * sizeof(int));
    if (!pq->data) return -1;
    
    pq->capacity = capacity;
    pq->size = 0;
    pq->processes = processes;
    return 0;
}

/* Free priority queue resources */
void pq_free(PriorityQueue *pq) {
    free(pq->data);
    pq->data = NULL;
    pq->capacity = pq->size = 0;
}

/* Helper function to swap two integers */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Heapify up operation to maintain heap property after insertion */
void heapify_up(PriorityQueue *pq, int index) {
    if (index <= 0) return;
    
    int parent = (index - 1) / 2;
    
    // Compare priorities of processes (lower priority number means higher priority)
    // If child has higher priority than parent, swap them
    struct process *child_proc = &pq->processes[pq->data[index]];
    struct process *parent_proc = &pq->processes[pq->data[parent]];
    
    // Priority comparison: lower number means higher priority
    // Also consider arrival time and remaining burst time
    int should_swap = 0;
    if (child_proc->priority < parent_proc->priority) {
        should_swap = 1;
    } else if (child_proc->priority == parent_proc->priority) {
        // If priorities are equal, consider arrival time
        if (child_proc->at < parent_proc->at) {
            should_swap = 1;
        } else if (child_proc->at == parent_proc->at) {
            // If arrival times are equal, consider remaining burst time
            if (child_proc->rem_bt < parent_proc->rem_bt) {
                should_swap = 1;
            } else if (child_proc->rem_bt == parent_proc->rem_bt) {
                // If remaining burst times are equal, consider PID
                if (child_proc->pid < parent_proc->pid) {
                    should_swap = 1;
                }
            }
        }
    }
    
    if (should_swap) {
        swap(&pq->data[index], &pq->data[parent]);
        heapify_up(pq, parent);
    }
}

/* Heapify down operation to maintain heap property after deletion */
void heapify_down(PriorityQueue *pq, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    // Find the process with highest priority among parent and its children
    if (left < pq->size) {
        struct process *left_proc = &pq->processes[pq->data[left]];
        struct process *largest_proc = &pq->processes[pq->data[largest]];
        
        if (left_proc->priority < largest_proc->priority) {
            largest = left;
        } else if (left_proc->priority == largest_proc->priority) {
            if (left_proc->at < largest_proc->at) {
                largest = left;
            } else if (left_proc->at == largest_proc->at) {
                if (left_proc->rem_bt < largest_proc->rem_bt) {
                    largest = left;
                } else if (left_proc->rem_bt == largest_proc->rem_bt) {
                    if (left_proc->pid < largest_proc->pid) {
                        largest = left;
                    }
                }
            }
        }
    }
    
    if (right < pq->size) {
        struct process *right_proc = &pq->processes[pq->data[right]];
        struct process *largest_proc = &pq->processes[pq->data[largest]];
        
        if (right_proc->priority < largest_proc->priority) {
            largest = right;
        } else if (right_proc->priority == largest_proc->priority) {
            if (right_proc->at < largest_proc->at) {
                largest = right;
            } else if (right_proc->at == largest_proc->at) {
                if (right_proc->rem_bt < largest_proc->rem_bt) {
                    largest = right;
                } else if (right_proc->rem_bt == largest_proc->rem_bt) {
                    if (right_proc->pid < largest_proc->pid) {
                        largest = right;
                    }
                }
            }
        }
    }
    
    // If highest priority is not the parent, swap and continue heapifying
    if (largest != index) {
        swap(&pq->data[index], &pq->data[largest]);
        heapify_down(pq, largest);
    }
}

/* Insert an element into the priority queue */
int pq_enqueue(PriorityQueue *pq, int process_index) {
    if (pq->size >= pq->capacity) {
        // Resize if needed
        int new_capacity = pq->capacity * 2;
        int *new_data = realloc(pq->data, new_capacity * sizeof(int));
        if (!new_data) return -1;
        pq->data = new_data;
        pq->capacity = new_capacity;
    }
    
    pq->data[pq->size] = process_index;
    heapify_up(pq, pq->size);
    pq->size++;
    return 0;
}

/* Remove and return the highest priority element */
int pq_dequeue(PriorityQueue *pq) {
    if (pq->size <= 0) return -1;
    
    int result = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    heapify_down(pq, 0);
    
    return result;
}

/* Check if priority queue is empty */
int pq_empty(PriorityQueue *pq) {
    return pq->size == 0;
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

    /* Loop to read arrival time, burst time, and priority for each process */
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

        // Prompt for priority
        printf("  Priority: ");
        // Read priority and validate input (must be non-negative)
        if (scanf("%d", &processes[i].priority) != 1 || processes[i].priority < 0) {
            // If invalid, print error, free memory, and exit
            fprintf(stderr, "Invalid priority.\n");
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
        // Print PID, arrival time, burst time, and priority
        printf("P%d\tAT=%d\tBT=%d\tPriority=%d\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].priority);
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

    /* Prepare priority queue */
    PriorityQueue pq;
    // Initialize the priority queue with a capacity slightly larger than n
    if (pq_init(&pq, n + 4, processes) != 0) {
        // If initialization fails, print error, free memory, and exit
        perror("priority queue init failed");
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
        if (pq_enqueue(&pq, next) != 0) { 
            // If enqueue fails, print error, free memory, and exit
            perror("enqueue"); 
            free(processes); 
            pq_free(&pq); 
            return 1; 
        }
        // Move to the next process in the sorted array
        next++;
    }

    /* Main RR scheduling loop with priority queue: run until all processes are completed */
    while (completed < n) {
        // If the ready queue is empty
        if (pq_empty(&pq)) {
            // If there are processes that haven't arrived yet
            if (next < n) {
                // Jump to the arrival time of the next process
                current_time = processes[next].at;
                // Enqueue all processes that arrive at this new current time
                while (next < n && processes[next].at <= current_time) {
                    // Enqueue the index of the process
                    if (pq_enqueue(&pq, next) != 0) { 
                        // If enqueue fails, print error, free memory, and exit
                        perror("enqueue"); 
                        free(processes); 
                        pq_free(&pq); 
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

        // Dequeue the next ready process index (highest priority)
        int idx = pq_dequeue(&pq);
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
            if (pq_enqueue(&pq, next) != 0) { 
                // If enqueue fails, print error, free memory, and exit
                perror("enqueue"); 
                free(processes); 
                pq_free(&pq); 
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
            // If not finished, re-enqueue the process at the priority queue
            if (pq_enqueue(&pq, idx) != 0) { 
                // If enqueue fails, print error, free memory, and exit
                perror("enqueue"); 
                free(processes); 
                pq_free(&pq); 
                return 1; 
            }
        }
    }

    /* Compute and print results */
    // Variables to accumulate total waiting and turnaround times for averaging
    double total_wt = 0.0, total_tat = 0.0;
    // Print the results header
    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    // Loop through all processes to print results
    for (int i = 0; i < n; ++i) {
        // Print PID, arrival time, burst time, priority, completion time, turnaround time, and waiting time
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               processes[i].pid, processes[i].at, processes[i].bt, processes[i].priority,
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
    // Free the memory allocated for the priority queue
    pq_free(&pq);
    // Free the memory allocated for the processes array
    free(processes);
    // Return 0 to indicate successful execution
    return 0;
}