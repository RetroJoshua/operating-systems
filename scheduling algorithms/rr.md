Absolutely 👍 Here’s a **clear and structured algorithm** describing the **Round Robin Scheduling Program** implemented in your C code:  

---

### **Algorithm: Round Robin CPU Scheduling**

**Goal:**  
Simulate Round Robin CPU scheduling for a set of processes and compute each process’s **Completion Time (CT)**, **Turnaround Time (TAT)**, and **Waiting Time (WT)** along with average TAT and WT.

---

#### **Step 1: Input number of processes**
1. Read the total number of processes `n`.

---

#### **Step 2: Input process details**
2. For each process `i` (from 1 to n):
   - Assign a **process ID** = `i`.
   - Read its **Arrival Time (AT)**.
   - Read its **Burst Time (BT)**.
   - Set **Remaining Burst Time (rem_bt = BT)**.
   - Initialize **CT**, **WT**, **TAT**, and **is_completed** = 0.

---

#### **Step 3: Sort processes**
3. Sort all processes according to:
   - Arrival time (ascending),
   - If tie → Burst time (ascending),
   - If tie again → Process ID (ascending).  
   *(Ensures fairness and order of arrival.)*

---

#### **Step 4: Input time quantum**
4. Read the **Time Quantum (TQ)** value.

---

#### **Step 5: Initialize queue and variables**
5. Create a circular **queue** to store process indices.  
6. Initialize:
   - `current_time` = arrival time of the first process.
   - `next` = index of the next unqueued process (initially 0).
   - `completed` = 0 (number of processes finished).

7. Enqueue all processes that have already **arrived** by `current_time`.

---

#### **Step 6: Main scheduling loop**
8. **While** (number of completed processes < total number of processes):

   - **Case 1:** If queue is empty:
     - Move time to the arrival time of the next process (`current_time = p[next].at`).
     - Enqueue any new processes that have now arrived.
     - **Continue** to next iteration.

   - **Case 2:** If queue is not empty:
     - **Dequeue** a process index `idx`.
     - **Run** this process for:
       \[
       exec = \min(rem\_bt[idx], time\_quantum)
       \]
       Meaning, process executes for either TQ or until it finishes.
     - Reduce its remaining burst:  
       \[
       rem\_bt[idx] = rem\_bt[idx] - exec
       \]
     - Increment the current time:  
       \[
       current\_time += exec
       \]

     - Enqueue all newly arrived processes whose arrival time ≤ current_time.

     - **If** process finished (`rem_bt == 0`):
       - Compute and set  
         \[
         CT = current\_time
         \]
         \[
         TAT = CT - AT
         \]
         \[
         WT = TAT - BT
         \]
       - Mark process as completed.  
       - Increment `completed`.

     - **Else** (still has remaining burst):
       - Re-enqueue the process back into the queue.

---

#### **Step 7: After scheduling**
9. For each process, print:
   - Process ID, Arrival Time, Burst Time, Completion Time, Turnaround Time, and Waiting Time.

---

#### **Step 8: Compute averages**
10. Compute and display:
    - **Average Turnaround Time**
      \[
      Avg\_TAT = \frac{\sum TAT}{n}
      \]
    - **Average Waiting Time**
      \[
      Avg\_WT = \frac{\sum WT}{n}
      \]

---

#### **Step 9: End**
11. Free dynamically allocated memory (for queue and process array).  
12. **End of program.**

---

### **Output:**
- Tabular report of all processes (PID, AT, BT, CT, TAT, WT)
- Average Waiting Time  
- Average Turnaround Time  

---

Would you like me to also give you a **flowchart** version of this algorithm (can be image-based)? It would visually show how the Round Robin scheduling loop works.
