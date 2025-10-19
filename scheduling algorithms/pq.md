## **Algorithm: Non-Preemptive Priority Scheduling**

### **Input:**
- Number of processes (n)
- For each process: Arrival Time (AT), Burst Time (BT), Priority

### **Output:**
- Completion Time (CT), Turnaround Time (TAT), Waiting Time (WT) for each process
- Average WT and Average TAT

---

### **Steps:**

1. **Initialize:**
   - Read number of processes `n`
   - For each process `i` (1 to n):
     - Assign Process ID = i
     - Read Arrival Time, Burst Time, Priority
   - Set `current_time = 0`, `completed = 0`
   - Create array `is_completed[]` initialized to 0 (false)

2. **Sort processes by Arrival Time** (for optimization)
   - If arrival times are equal, sort by priority
   - If priorities are also equal, sort by PID

3. **Main Scheduling Loop:**
   - **While** `completed < n`:
     
     a. **Select highest priority process:**
        - Initialize `idx = -1`, `highest_priority = ∞`
        - For each process `i`:
          - If process is **not completed** AND **has arrived** (AT ≤ current_time):
            - If priority[i] < highest_priority:
              - Update `highest_priority = priority[i]`
              - Update `idx = i`
            - **Tie-breaking:** If priorities are equal, choose process with:
              - Earlier arrival time, OR
              - Smaller PID (if arrival times also equal)
     
     b. **Handle CPU idle time:**
        - If `idx == -1` (no process available):
          - Increment `current_time` by 1
          - Continue to next iteration
     
     c. **Execute selected process:**
        - `current_time = current_time + BT[idx]`
        - `CT[idx] = current_time`
        - `TAT[idx] = CT[idx] - AT[idx]`
        - `WT[idx] = TAT[idx] - BT[idx]`
        - Mark `is_completed[idx] = 1`
        - Increment `completed`

4. **Calculate Averages:**
   - `total_wt = sum of all WT`
   - `total_tat = sum of all TAT`
   - `avg_wt = total_wt / n`
   - `avg_tat = total_tat / n`

5. **Display Results:**
   - Print table: PID, AT, BT, Priority, CT, TAT, WT
   - Print Average WT and Average TAT

6. **End**

---

### **Key Points:**
- **Non-preemptive:** Once a process starts, it runs until completion
- **Priority-based:** Lower priority number = Higher priority
- **Handles arrival times:** CPU may remain idle if no process has arrived
- **Time Complexity:** O(n²) in worst case

---

### **Example Trace:**

| Process | AT | BT | Priority |
|---------|----|----|----------|
| P1 | 0 | 4 | 2 |
| P2 | 1 | 3 | 1 |
| P3 | 2 | 1 | 3 |

**Execution:**
- Time 0: P1 arrives (priority 2), starts executing
- Time 4: P1 completes, P2 (priority 1) and P3 (priority 3) available → P2 selected
- Time 7: P2 completes, P3 executes
- Time 8: P3 completes

**Result:**
- P1: CT=4, TAT=4, WT=0
- P2: CT=7, TAT=6, WT=3
- P3: CT=8, TAT=6, WT=5
