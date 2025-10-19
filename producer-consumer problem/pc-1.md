Here's the **algorithm** for the Producer-Consumer problem:

---

## **Algorithm: Producer-Consumer with Semaphores**

### **Initialization:**
```
1. Create buffer[BUFFER_SIZE]
2. Initialize semaphore empty = BUFFER_SIZE (all slots available)
3. Initialize semaphore full = 0 (no items in buffer)
4. Initialize mutex = 1 (unlocked)
5. Set in = 0 (producer index)
6. Set out = 0 (consumer index)
7. Set item_count = 0
```

---

### **Producer Algorithm:**
```
1. START Producer(item)
2. wait(empty)                    // Wait if buffer is full
3. lock(mutex)                    // Enter critical section
4.     buffer[in] = item          // Add item to buffer
5.     Print "Producer produces item"
6.     in = (in + 1) % BUFFER_SIZE // Move to next position
7. unlock(mutex)                  // Exit critical section
8. signal(full)                   // Increment full count
9. END Producer
```

---

### **Consumer Algorithm:**
```
1. START Consumer()
2. wait(full)                     // Wait if buffer is empty
3. lock(mutex)                    // Enter critical section
4.     item = buffer[out]         // Remove item from buffer
5.     Print "Consumer consumes item"
6.     out = (out + 1) % BUFFER_SIZE // Move to next position
7. unlock(mutex)                  // Exit critical section
8. signal(empty)                  // Increment empty count
9. END Consumer
```

---

### **Main Algorithm:**
```
1. START Main
2. Initialize semaphores and mutex
3. Display menu options
4. REPEAT
5.     Read user choice
6.     CASE choice OF
7.         1: // Producer
8.             IF empty > 0 THEN
9.                 item_count = item_count + 1
10.                Create thread and call Producer(item_count)
11.            ELSE
12.                Print "Buffer is full!"
13.            END IF
14.        
15.        2: // Consumer
16.            IF full > 0 THEN
17.                Create thread and call Consumer()
18.            ELSE
19.                Print "Buffer is empty!"
20.            END IF
21.        
22.        3: // Exit
23.            Destroy semaphores and mutex
24.            EXIT program
25.    END CASE
26. UNTIL choice = 3
27. END Main
```

---

## **Key Concepts:**

- **wait(semaphore)**: Decrements semaphore; blocks if value is 0
- **signal(semaphore)**: Increments semaphore; wakes waiting threads
- **lock(mutex)**: Acquires exclusive access to critical section
- **unlock(mutex)**: Releases critical section
- **Circular Buffer**: Uses modulo to wrap around buffer indices

This ensures **mutual exclusion** and prevents **race conditions**! 🔒