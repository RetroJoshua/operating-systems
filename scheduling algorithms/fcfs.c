#include <stdio.h>
#include <stdlib.h>

// Define the process structure
struct process {
    int pid;
    int at;  // arrival time
    int bt;  // burst time
    int ct;  // completion time
    int wt;  // waiting time
    int tat; // turnaround time
};

// Comparator function for qsort: sort by arrival time
int cmp_at(const void *a, const void *b) {
    const struct process *p1 = (const struct process *)a;
    const struct process *p2 = (const struct process *)b;

    if (p1->at != p2->at)
        return (p1->at > p2->at) - (p1->at < p2->at); // Safe comparison
    if (p1->bt != p2->bt)
        return (p1->bt > p2->bt) - (p1->bt < p2->bt);
    return (p1->pid > p2->pid) - (p1->pid < p2->pid);
}

int main() {
    int n;

    printf("Enter Number of Processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of processes.\n");
        return 1;
    }

    // Dynamically allocate array of processes
    struct process *processes = malloc(n * sizeof(struct process));
    if (processes == NULL) {
        perror("malloc failed");
        return 1;
    }

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d:\n", i + 1);
        printf("  Arrival Time: ");
        if (scanf("%d", &processes[i].at) != 1) {
            fprintf(stderr, "Invalid input for arrival time.\n");
            free(processes);
            return 1;
        }
        printf("  Burst Time: ");
        if (scanf("%d", &processes[i].bt) != 1 || processes[i].bt <= 0) {
            fprintf(stderr, "Invalid burst time.\n");
            free(processes);
            return 1;
        }

        // Initialize remaining fields to zero
        processes[i].ct = 0;
        processes[i].wt = 0;
        processes[i].tat = 0;
    }

    // Sort processes by arrival time using qsort
    qsort(processes, n, sizeof(struct process), cmp_at);

    // FCFS Scheduling Logic
    int current_time = 0;
    for (int i = 0; i < n; ++i) {
        if (processes[i].at > current_time)
            current_time = processes[i].at; // CPU idle until process arrives

        int start = current_time;
        processes[i].ct = start + processes[i].bt;
        processes[i].wt = start - processes[i].at;
        processes[i].tat = processes[i].ct - processes[i].at;
        current_time = processes[i].ct; // advance time
    }

    // Calculate totals and averages
    int twt = 0, ttat = 0;
    for (int i = 0; i < n; i++) {
        twt += processes[i].wt;
        ttat += processes[i].tat;
    }

    float awt = (float)twt / n;
    float atat = (float)ttat / n;

    // Print results
    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid, processes[i].at, processes[i].bt,
               processes[i].ct, processes[i].wt, processes[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", awt);
    printf("Average Turnaround Time: %.2f\n", atat);

    // Free allocated memory
    free(processes);
    return 0;
}