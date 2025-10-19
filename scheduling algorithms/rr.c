#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, rem_bt, ct, wt, tat, is_completed;
};

int cmp_at(const void *a, const void *b) {
    const struct process *p1 = a, *p2 = b;
    if (p1->at != p2->at) return p1->at - p2->at;
    if (p1->bt != p2->bt) return p1->bt - p2->bt;
    return p1->pid - p2->pid;
}

typedef struct {
    int *data, cap, front, size;
} Queue;

int queue_init(Queue *q, int initial_cap) {
    if (initial_cap <= 0) initial_cap = 4;
    q->data = malloc(initial_cap * sizeof(int));
    if (!q->data) return -1;
    q->cap = initial_cap;
    q->front = q->size = 0;
    return 0;
}

void queue_free(Queue *q) {
    free(q->data);
    q->data = NULL;
    q->cap = q->front = q->size = 0;
}

int queue_ensure_capacity(Queue *q) {
    if (q->size < q->cap) return 0;
    int newcap = q->cap * 2;
    int *newdata = malloc(newcap * sizeof(int));
    if (!newdata) return -1;
    for (int i = 0; i < q->size; ++i) {
        newdata[i] = q->data[(q->front + i) % q->cap];
    }
    free(q->data);
    q->data = newdata;
    q->cap = newcap;
    q->front = 0;
    return 0;
}

int queue_enqueue(Queue *q, int value) {
    if (queue_ensure_capacity(q) != 0) return -1;
    int back = (q->front + q->size) % q->cap;
    q->data[back] = value;
    q->size++;
    return 0;
}

int queue_dequeue(Queue *q) {
    if (q->size == 0) return -1;
    int val = q->data[q->front];
    q->front = (q->front + 1) % q->cap;
    q->size--;
    return val;
}

int queue_empty(Queue *q) {
    return q->size == 0;
}

int main(void) {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    struct process *p = malloc(n * sizeof(struct process));

    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        printf("Process %d:\n  Arrival Time: ", i + 1);
        scanf("%d", &p[i].at);
        printf("  Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].rem_bt = p[i].bt;
        p[i].ct = p[i].wt = p[i].tat = p[i].is_completed = 0;
    }

    qsort(p, n, sizeof(struct process), cmp_at);

    int time_quantum;
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    Queue q;
    queue_init(&q, n + 4);

    int next = 0, completed = 0;
    int current_time = (n > 0) ? p[0].at : 0;

    while (next < n && p[next].at <= current_time) {
        queue_enqueue(&q, next);
        next++;
    }

    while (completed < n) {
        if (queue_empty(&q)) {
            if (next < n) {
                current_time = p[next].at;
                while (next < n && p[next].at <= current_time) {
                    queue_enqueue(&q, next);
                    next++;
                }
                continue;
            } else {
                break;
            }
        }

        int idx = queue_dequeue(&q);
        if (idx < 0) continue;

        int exec = (p[idx].rem_bt < time_quantum) ? p[idx].rem_bt : time_quantum;
        p[idx].rem_bt -= exec;
        current_time += exec;

        while (next < n && p[next].at <= current_time) {
            queue_enqueue(&q, next);
            next++;
        }

        if (p[idx].rem_bt == 0) {
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].is_completed = 1;
            completed++;
        } else {
            queue_enqueue(&q, idx);
        }
    }

    double total_wt = 0.0, total_tat = 0.0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("Average WT = %.2f\n", total_wt / n);
    printf("Average TAT = %.2f\n", total_tat / n);

    queue_free(&q);
    free(p);
    return 0;
}
