#include <stdio.h>
#include <stdlib.h>

struct process{
    int pid, at, bt, ct, wt, tat, is_completed;
};

int cmp_at(const void *a, const void *b){
    const struct process *p1 = a, *p2 = b;
    if(p1->at != p2->at) return p1->at - p2->at;
    if(p1->bt != p2->bt) return p1->bt - p2->bt;
    return p1->pid - p2->pid;
}

int main()
{
    int n;
    printf("Enter Number of Processes\n");
    scanf("%d",&n);
    
    struct process *p = malloc(n * sizeof(struct process));
    
    for(int i=0; i<n; i++){
        p[i].pid = i+1;
        printf("Process -%d\nArrival time ",i+1);
        scanf("%d",&p[i].at);
        printf("Burst time ");
        scanf("%d",&p[i].bt);
        p[i].wt = p[i].ct = p[i].tat = p[i].is_completed = 0;
    }
    
    qsort(p, n, sizeof(struct process), cmp_at);
   
    int completed = 0, current_time = 0, twt = 0, ttat = 0;
   
    while(completed < n){
        int idx = -1, min_bt = 1000000000;
        
        for(int i=0; i<n; i++){
            if(p[i].at <= current_time && !p[i].is_completed){
                if(p[i].bt < min_bt){
                    min_bt = p[i].bt;
                    idx = i;
                }
                if(p[i].bt == min_bt && p[i].at < p[idx].at){
                    idx = i;
                }
            }
        }
        
        if(idx == -1){
            current_time++;
        }else{
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            ttat += p[idx].tat;
            twt += p[idx].wt;
            p[idx].is_completed = 1;
            completed++;
        }
    }
    
    for(int i=0; i<n; i++){
        printf("Process\t%d\tarrival time\t%d\tburst time\t%d\twaiting time\t%d\ttat\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
    
    printf("Average waiting time %.2f\n", (float)twt/n);
    printf("Average Turnaround time %.2f\n", (float)ttat/n);
    
    free(p);
    return 0;
}
