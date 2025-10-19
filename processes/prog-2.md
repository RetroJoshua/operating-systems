## Algorithm: Process Creation and Execution Monitoring

### **START**

**Step 1: Initialize Variables**
- Declare `pid` (process ID) = 0
- Declare `status` (exit status variable)

**Step 2: Create Child Process**
- Call `fork()` system call
- Store returned value in `pid`

**Step 3: Check Fork Result and Branch**

---

### **CASE A: Child Process (pid == 0)**

**Step 3.1:** Print "I am the child."

**Step 3.2:** Execute new program
- Call `execl("/bin/ls", "ls", "-l", "/home/ubuntu/", NULL)`
- Replace current process image with `ls` command

**Step 3.3:** If exec fails (only reached if execl fails)
- Print error message using `perror()`
- Exit with status 1

---

### **CASE B: Parent Process (pid > 0)**

**Step 3.4:** Print "I am the parent, and the child is [pid]."

**Step 3.5:** Wait for child process
- Call `wait(&status)` to block until child terminates
- Store returned child PID

**Step 3.6:** Print "End of process [pid]: "

**Step 3.7:** Check termination type

**Sub-step 3.7.1:** IF child exited normally (`WIFEXITED(status)`)
- Extract exit code using `WEXITSTATUS(status)`
- Print "The process ended with exit([code])."

**Sub-step 3.7.2:** IF child was killed by signal (`WIFSIGNALED(status)`)
- Extract signal number using `WTERMSIG(status)`
- Print "The process ended with kill -[signal]."

---

### **CASE C: Fork Failed (pid < 0)**

**Step 3.8:** Print error message using `perror()`

---

**Step 4: Terminate Program**
- Return 0 (success)

### **END**
