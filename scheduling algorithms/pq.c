#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, ct, wt, tat, priority;
};

int cmp_at(const void *a, const void *b) {
    const struct process *p1 = (const struct process *)a, *p2 = (const struct process *)b;
    if (p1->at != p2->at) return p1->at - p2->at;
    if (p1->priority != p2->priority) return p1->priority - p2->priority;
    return p1->pid - p2->pid;
}

int main(void) {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    
    struct process *p = malloc(n * sizeof(struct process));
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d:\n", i + 1);
        printf("  Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("  Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("  Priority: ");
        scanf("%d", &p[i].priority);
    }
    
    qsort(p, n, sizeof(struct process), cmp_at);
    
    int current_time = 0, completed = 0;
    int *is_completed = calloc(n, sizeof(int));
    
    while (completed < n) {
        int idx = -1, highest_priority = 999999;
        
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && p[i].at <= current_time) {
                if (p[i].priority < highest_priority || 
                    (p[i].priority == highest_priority && p[i].at < p[idx].at) ||
                    (p[i].priority == highest_priority && p[i].at == p[idx].at && p[i].pid < p[idx].pid)) {
                    highest_priority = p[i].priority;
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            current_time++;
            continue;
        }
        
        current_time += p[idx].bt;
        p[idx].ct = current_time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        is_completed[idx] = 1;
        completed++;
    }
    
    double total_wt = 0.0, total_tat = 0.0;
    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("Average WT = %.2f\nAverage TAT = %.2f\n", total_wt / n, total_tat / n);
    
    free(is_completed);
    free(p);
    return 0;
}
