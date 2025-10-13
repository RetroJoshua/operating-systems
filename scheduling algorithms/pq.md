### Algorithm for Priority-Based Round Robin Scheduling

This algorithm implements a hybrid CPU scheduling approach that combines **priority-based selection** with **Round Robin (RR) execution**. Processes are selected based on their priority, but within the same priority level, they are executed using Round Robin with a fixed time quantum.

#### Data Structures

1. **Process Structure**:
   - `pid`: Process ID
   - `at`: Arrival time
   - `bt`: Burst time (total CPU time needed)
   - `rem_bt`: Remaining burst time
   - `ct`: Completion time
   - `wt`: Waiting time
   - `tat`: Turnaround time
   - `priority`: Priority of the process (lower number means higher priority)
   - `is_completed`: Flag indicating completion status

2. **Priority Queue**:
   - Implemented as a binary heap
   - Stores indices of processes
   - Maintains processes in order of priority

#### Algorithm Steps

1. **Initialization**:
   - Read the number of processes `n`
   - For each process:
     - Read arrival time, burst time, and priority
     - Initialize remaining burst time to burst time
     - Set completion, waiting, and turnaround times to 0
     - Mark as not completed

2. **Sorting**:
   - Sort processes by arrival time, then by burst time, then by PID using `qsort`

3. **Priority Queue Setup**:
   - Initialize a priority queue with capacity `n + 4`
   - Read time quantum for Round Robin scheduling

4. **Main Scheduling Loop**:
   - Initialize `current_time` to the arrival time of the first process
   - Initialize `completed` counter to 0
   - Initialize `next` pointer to 0 (points to next process to be enqueued)

5. **Enqueue Initial Processes**:
   - Enqueue all processes that have arrived at or before `current_time`

6. **Scheduling Execution**:
   - While there are processes to be completed:
     - If the priority queue is empty:
       - If there are processes that haven't arrived yet:
         - Jump `current_time` to the arrival time of the next process
         - Enqueue all processes that arrive at this new time
       - Else:
         - Exit (no more processes)
     - Dequeue the highest priority process from the queue
     - Determine execution time as `min(rem_bt, time_quantum)`
     - Execute the process for this time:
       - Decrement `rem_bt` by execution time
       - Increment `current_time` by execution time
     - Enqueue any processes that arrived during execution
     - If the process is completed (`rem_bt == 0`):
       - Record completion time
       - Calculate turnaround time (`ct - at`)
       - Calculate waiting time (`tat - bt`)
       - Mark as completed
       - Increment `completed` counter
     - Else:
       - Re-enqueue the process in the priority queue

7. **Result Calculation**:
   - For each process:
     - Print PID, arrival time, burst time, priority, completion time, turnaround time, and waiting time
   - Calculate and print average waiting time
   - Calculate and print average turnaround time

8. **Cleanup**:
   - Free allocated memory for processes and priority queue

#### Priority Comparison Logic

When comparing two processes for priority queue ordering:
1. Lower priority number means higher priority
2. If priorities are equal:
   - Earlier arrival time has higher priority
   - If arrival times are equal:
     - Shorter remaining burst time has higher priority
     - If remaining burst times are equal:
       - Lower PID has higher priority

This algorithm ensures that:
- Higher priority processes are executed first
- Within the same priority level, processes are handled fairly using Round Robin
- Processes are executed in the order they arrive when priorities and other factors are equal
- Efficient scheduling with O(n log n) time complexity due to sorting and heap operations