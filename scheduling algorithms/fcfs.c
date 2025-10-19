#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, ct, wt, tat;
};

int cmp_at(const void *a, const void *b) {
    const struct process *p1 = a, *p2 = b;
    if (p1->at != p2->at) return p1->at - p2->at;
    if (p1->bt != p2->bt) return p1->bt - p2->bt;
    return p1->pid - p2->pid;
}

int main() {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    struct process *p = malloc(n * sizeof(struct process));

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d:\n  Arrival Time: ", i + 1);
        scanf("%d", &p[i].at);
        printf("  Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].ct = p[i].wt = p[i].tat = 0;
    }

    qsort(p, n, sizeof(struct process), cmp_at);

    int current_time = 0, twt = 0, ttat = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].at > current_time) current_time = p[i].at;
        p[i].ct = current_time + p[i].bt;
        p[i].wt = current_time - p[i].at;
        p[i].tat = p[i].ct - p[i].at;
        current_time = p[i].ct;
        twt += p[i].wt;
        ttat += p[i].tat;
    }

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);

    printf("\nAverage Waiting Time: %.2f\n", (float)twt / n);
    printf("Average Turnaround Time: %.2f\n", (float)ttat / n);

    free(p);
    return 0;
}
