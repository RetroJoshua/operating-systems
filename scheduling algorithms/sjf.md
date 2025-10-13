### Algorithm — Non‑preemptive SJF with arrival times

#### Problem
Schedule n processes using non-preemptive Shortest Job First (SJF) with arrival times. For each process compute completion time (CT), turnaround time (TAT), waiting time (WT) and the average WT/TAT.

#### Inputs
- n: number of processes
- For each process i:
  - pid (process id)
  - at (arrival time)
  - bt (burst time)

#### Outputs
- For each process: ct, tat, wt
- Average waiting time (AWT) and average turnaround time (ATAT)

#### Key idea
1. Sort processes by arrival time (tie-break: burst time, then pid).
2. Maintain a current time and repeatedly pick, among arrived and not-yet-completed processes, the one with the smallest burst time.
3. If none has arrived yet, advance current time by 1.
4. When a process is selected, run it to completion (non-preemptive), update its CT, TAT and WT, mark it completed, and update totals.
5. Repeat until all processes are completed.

#### Detailed step-by-step algorithm
1. Read n.
2. For i = 1..n:
   - Read arrival time at[i] and burst time bt[i].
   - Initialize ct[i] = tat[i] = wt[i] = 0, is_completed[i] = false.
   - Set pid[i] = i.
3. Sort processes by (at, bt, pid).
4. completed = 0, current_time = 0, total_wt = 0, total_tat = 0.
5. While completed < n:
   1. idx = -1, min_bt = +infinity.
   2. For each process i from 0..n-1:
      - If at[i] <= current_time and not is_completed[i]:
        - If bt[i] < min_bt:
          - min_bt = bt[i], idx = i.
        - Else if bt[i] == min_bt and at[i] < at[idx]:
          - idx = i.   (tie-breaker: earlier arrival)
   3. If idx == -1:
      - current_time = current_time + 1 (no process available yet).
   4. Else:
      - current_time = current_time + bt[idx].
      - ct[idx] = current_time.
      - tat[idx] = ct[idx] - at[idx].
      - wt[idx] = tat[idx] - bt[idx].
      - total_tat += tat[idx], total_wt += wt[idx].
      - is_completed[idx] = true.
      - completed = completed + 1.
6. Compute averages:
   - AWT = total_wt / n
   - ATAT = total_tat / n
7. Print per-process details and AWT, ATAT.

#### Pseudocode
```text
INPUT n
for i = 0 to n-1:
    pid[i] = i+1
    read at[i], bt[i]
    ct[i] = tat[i] = wt[i] = 0
    is_completed[i] = false

sort processes by (at asc, bt asc, pid asc)

completed = 0
current_time = 0
total_wt = total_tat = 0

while completed < n:
    idx = -1
    min_bt = INF
    for i = 0 to n-1:
        if at[i] <= current_time and not is_completed[i]:
            if bt[i] < min_bt:
                min_bt = bt[i]
                idx = i
            else if bt[i] == min_bt and at[i] < at[idx]:
                idx = i

    if idx == -1:
        current_time = current_time + 1
    else:
        current_time = current_time + bt[idx]
        ct[idx] = current_time
        tat[idx] = ct[idx] - at[idx]
        wt[idx] = tat[idx] - bt[idx]
        total_tat += tat[idx]
        total_wt += wt[idx]
        is_completed[idx] = true
        completed += 1

AWT = total_wt / n
ATAT = total_tat / n

PRINT details and averages
```

#### Time and space complexity
- Sorting: O(n log n)
- Main scheduling loop: in worst case you scan all processes for each completion → O(n^2)
- Overall: O(n^2) time, O(n) extra space.

#### Notes / Assumptions / Improvements
- This is non-preemptive SJF (once a process starts, it runs to completion).
- Tie-breaking:
  - Initial sort: by arrival time, then burst time, then pid.
  - Selection: chooses smallest bt among arrived processes; if bt equal, the one with earlier arrival is chosen.
- If you want better performance for large n, use a min-heap (priority queue) keyed by burst time for arrived processes; that gives O(n log n) scheduling after sorting arrivals.
- Edge case: if there are gaps with no arrived process, current_time is incremented by 1 each loop; you can instead jump to the next earliest arrival time to reduce unnecessary iterations.

