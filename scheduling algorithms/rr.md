### Round Robin (RR) CPU Scheduling Algorithm

The provided C program implements the **Round Robin (RR)** CPU scheduling algorithm. RR is a preemptive scheduling algorithm where each process is assigned a fixed time slice (called a time quantum) for execution. If a process does not complete within its time quantum, it is preempted and moved to the end of the ready queue, allowing the next process to execute.

#### Algorithm Steps

1. **Input Collection**:
   - Prompt the user to enter the number of processes `n`.
   - For each process, collect:
     - Arrival Time (`AT`)
     - Burst Time (`BT`)
   - Assign a unique Process ID (`PID`) to each process (1-based index).

2. **Initialization**:
   - Sort all processes based on:
     - Arrival Time (ascending)
     - Burst Time (ascending, if arrival times are equal)
     - Process ID (ascending, if both arrival and burst times are equal)
   - Prompt the user to enter the time quantum `TQ`.

3. **Data Structures**:
   - Initialize a dynamic circular queue `Q` to hold indices of processes in the ready state.
   - Initialize variables:
     - `next`: Index of the next process in the sorted array not yet enqueued.
     - `completed`: Counter for the number of completed processes.
     - `current_time`: Current simulation time, initialized to the arrival time of the first process (or 0 if no processes).

4. **Main Scheduling Loop**:
   - Enqueue all processes that have arrived at or before `current_time` into `Q`.
   - While there are processes to be scheduled (`completed < n`):
     - If the ready queue `Q` is empty:
       - If there are still processes that haven't arrived:
         - Jump `current_time` to the arrival time of the next process.
         - Enqueue all processes that arrive at this new `current_time`.
       - Else, break the loop (no more processes).
     - Dequeue the next process index `idx` from `Q`.
     - Determine the execution time `exec` for this quantum:
       - `exec = min(remaining burst time of process[idx], TQ)`
     - Execute the process for `exec` time units:
       - Decrement the remaining burst time of the process: `process[idx].rem_bt -= exec`
       - Advance the simulation time: `current_time += exec`
     - Enqueue any processes that arrived while the current process was executing (between `current_time - exec` and `current_time`).
     - If the process has finished (`process[idx].rem_bt == 0`):
       - Record Completion Time (`CT`) as `current_time`.
       - Calculate Turnaround Time (`TAT = CT - AT`).
       - Calculate Waiting Time (`WT = TAT - BT`).
       - Mark the process as completed.
       - Increment the `completed` counter.
     - Else (process is not finished):
       - Re-enqueue the process index `idx` at the back of `Q`.

5. **Output Results**:
   - Print a table with the following details for each process:
     - PID
     - Arrival Time (`AT`)
     - Burst Time (`BT`)
     - Completion Time (`CT`)
     - Turnaround Time (`TAT`)
     - Waiting Time (`WT`)
   - Calculate and print:
     - Average Waiting Time (`AWT = Total WT / n`)
     - Average Turnaround Time (`ATAT = Total TAT / n`)

6. **Cleanup**:
   - Free the dynamically allocated memory for the queue and processes array.

#### Key Features of the Implementation

- **Dynamic Queue**: The ready queue dynamically resizes itself when full, ensuring efficient memory usage.
- **Preemption**: Processes are preempted after their time quantum expires.
- **Arrival Handling**: The algorithm correctly handles processes arriving at different times by enqueuing them as they arrive during the simulation.
- **Completion Tracking**: Each process's completion time, turnaround time, and waiting time are calculated upon completion.