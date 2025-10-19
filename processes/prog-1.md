### **Algorithm: Forking Processes in C**

1. **Start the program.**

2. **Declare a variable** `pid` of type `pid_t` to store the process ID.

3. **Call the `fork()` system call** and assign its return value to `pid`.

4. **Check the value of `pid`:**
   - **Case 1:** If `pid == 0`  
     → The current process is the **child process**.  
     → Print `"It is the child process and pid is <child_pid>"`.  
     → Exit the child process using `exit(0)`.

   - **Case 2:** If `pid > 0`  
     → The current process is the **parent process**.  
     → Print `"It is the parent process and pid is <parent_pid>"`.  
     → Call `wait(NULL)` to wait for the child process to finish (prevents zombie process).

   - **Case 3:** If `pid < 0`  
     → Forking failed due to some error (e.g., system resource limits).  
     → Print `"Error while forking"`.  
     → Exit the program using `exit(EXIT_FAILURE)`.

5. **End the program** by returning `0` (successful execution).

---

### **Flow Summary**
- `fork()` creates a duplicate process.  
- The child and parent run in parallel from the point of the `fork()` call.  
- `getpid()` retrieves each process’s unique ID.  
- `wait(NULL)` ensures the parent waits for the child.
