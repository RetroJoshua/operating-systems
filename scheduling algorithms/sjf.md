## Algorithm for Shortest Job First (SJF) Non-Preemptive CPU Scheduling

### Data Structure
- **Process**: Contains pid, arrival_time (at), burst_time (bt), completion_time (ct), waiting_time (wt), turnaround_time (tat), is_completed flag

### Algorithm Steps

1. **Input Phase**
   - Read number of processes (n)
   - For each process i from 1 to n:
     - Assign pid = i
     - Read arrival_time and burst_time
     - Initialize wt, ct, tat, is_completed to 0

2. **Sorting Phase**
   - Sort processes by arrival_time (ascending)
   - If arrival_time is same, sort by burst_time (ascending)
   - If both same, sort by pid (ascending)

3. **Scheduling Phase**
   - Initialize: completed = 0, current_time = 0, total_wt = 0, total_tat = 0
   - While completed < n:
     - **Find shortest job:**
       - Set idx = -1, min_bt = ∞
       - For each process i:
         - If (arrival_time[i] ≤ current_time AND not completed):
           - If burst_time[i] < min_bt:
             - min_bt = burst_time[i]
             - idx = i
           - If burst_time[i] == min_bt AND arrival_time[i] < arrival_time[idx]:
             - idx = i
     
     - **Execute process:**
       - If idx == -1 (no process available):
         - Increment current_time by 1 (CPU idle)
       - Else:
         - current_time += burst_time[idx]
         - completion_time[idx] = current_time
         - turnaround_time[idx] = completion_time[idx] - arrival_time[idx]
         - waiting_time[idx] = turnaround_time[idx] - burst_time[idx]
         - total_tat += turnaround_time[idx]
         - total_wt += waiting_time[idx]
         - Mark is_completed[idx] = 1
         - Increment completed

4. **Output Phase**
   - For each process:
     - Print pid, arrival_time, burst_time, waiting_time, turnaround_time
   - Print average_waiting_time = total_wt / n
   - Print average_turnaround_time = total_tat / n

### Time Complexity
- O(n log n) for sorting + O(n²) for scheduling = **O(n²)**

### Space Complexity
- **O(n)** for storing n processes
