### Algorithm — First-Come-First-Serve (FCFS) Scheduling

#### Overview
This program implements FCFS CPU scheduling for a set of processes. It:
- reads process arrival time (AT) and burst time (BT),
- sorts processes by arrival time,
- simulates FCFS execution computing completion time (CT), waiting time (WT) and turnaround time (TAT),
- computes average waiting and turnaround times and prints the results.

#### Inputs
- n: number of processes
- For each process i:
  - AT[i]: arrival time (integer)
  - BT[i]: burst time (positive integer)

#### Outputs
- For each process: PID, AT, BT, CT, WT, TAT
- Average Waiting Time (AWT)
- Average Turnaround Time (ATAT)

#### Step-by-step algorithm
1. Read integer n. If n <= 0, report error and stop.
2. Allocate an array processes of size n. Each entry stores pid, at, bt, ct, wt, tat.
3. For i = 0 to n-1:
   1. Set processes[i].pid = i + 1.
   2. Read processes[i].at (arrival time). On invalid input, free memory and stop.
   3. Read processes[i].bt (burst time). If <= 0 or invalid input, free memory and stop.
   4. Initialize processes[i].ct = processes[i].wt = processes[i].tat = 0.
4. Sort the processes array by arrival time. (The provided comparator also breaks ties by burst time, then pid.)
5. Set current_time = 0.
6. For each process p in order (i from 0 to n-1):
   1. If p.at > current_time, set current_time = p.at (CPU remains idle until arrival).
   2. Let start = current_time.
   3. p.ct = start + p.bt.
   4. p.wt = start - p.at.
   5. p.tat = p.ct - p.at.
   6. Set current_time = p.ct.
7. Compute totals:
   1. twt = sum of all p.wt.
   2. ttat = sum of all p.tat.
8. Compute averages:
   1. AWT = twt / n.
   2. ATAT = ttat / n.
9. Print the table of PID, AT, BT, CT, WT, TAT and the average times.
10. Free the allocated memory and exit.

#### Pseudocode
```text
read n
if n <= 0: error and exit
allocate processes[n]

for i = 0 to n-1:
    processes[i].pid = i + 1
    read processes[i].at
    read processes[i].bt
    if invalid: free and exit
    processes[i].ct = processes[i].wt = processes[i].tat = 0

sort processes by (at, bt, pid)

current_time = 0
for i = 0 to n-1:
    p = processes[i]
    if p.at > current_time:
        current_time = p.at
    start = current_time
    p.ct = start + p.bt
    p.wt = start - p.at
    p.tat = p.ct - p.at
    current_time = p.ct

twt = sum(p.wt)
ttat = sum(p.tat)
AWT = twt / n
ATAT = ttat / n

print table and averages
free processes
```

#### Complexity
- Time complexity: O(n log n) due to sorting; O(n) for the scheduling loop. Overall O(n log n).
- Space complexity: O(n) for the processes array.

#### Notes / Edge cases
- The comparator sorts by arrival time, then by burst time, then by pid. This gives deterministic tie-breaking but FCFS strictly by arrival time would typically preserve original input order for equal arrival times.
- The program handles CPU idle periods by advancing current_time to the next arrival.
- The code validates n and burst times and handles malloc failure.