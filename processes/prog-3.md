## Algorithm: Parent-Child Process Creation and Synchronization

**Input:** None (command-line arguments not used)

**Output:** Process IDs and counter values printed to console

### Main Algorithm:

```
1. START

2. DECLARE pid of type pid_t

3. CREATE child process using fork()
   pid ← fork()

4. CHECK the return value of fork():

   CASE 1: pid == 0 (Child Process)
   ├── 4.1 PRINT "It is the child process and pid is [child_pid]"
   ├── 4.2 INITIALIZE counter i ← 0
   ├── 4.3 LOOP while i < 8
   │   ├── 4.3.1 PRINT i
   │   └── 4.3.2 INCREMENT i by 1
   ├── 4.4 EXIT child process with status 0
   └── END CASE 1

   CASE 2: pid > 0 (Parent Process)
   ├── 4.5 PRINT "It is the parent process and pid is [parent_pid]"
   ├── 4.6 DECLARE status variable
   ├── 4.7 WAIT for child process to terminate
   │   └── wait(&status)
   ├── 4.8 PRINT "Child is reaped"
   └── END CASE 2

   CASE 3: pid < 0 (Fork Failed)
   ├── 4.9 PRINT "Error in forking.."
   ├── 4.10 EXIT program with failure status
   └── END CASE 3

5. RETURN 0 (successful termination)

6. END
```
