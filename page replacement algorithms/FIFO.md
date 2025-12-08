The FIFO page-replacement algorithm is easy to understand and program. However, its 
performance is not always good. 
On the one hand, the page replaced may be an initialization module that was used a long time ago and is 
no longer needed. 
On the other hand, it could contain a heavily used variable that was initialized early and is in constant 
use. 
ALGORITHM: 
1. Start the process 
2. Read number of pages n 
3. Read number of pages no 
4. Read page numbers into an array a[i] 
5. Initialize avail[i]=0 .to check page hit 
6. Replace the page with circular queue, while re-placing check page availability in the frame 
Place avail[i]=1 if page is placed in the frame Count page faults 
7. Print the results. 
8. Stop the process. 

Expected Output: 
2 -1 -1 
2  3 -1 
2  3 -1 
2  3  1 
5  3  1 
5  2  1 
5  2  4 
5  2  4 
3  2  4 
3  2  4 
3  5  4 
3  5  2 
Number of page faults: 6 

This program implements the FIFO (First-In-First-Out) Page Replacement Algorithm, which is used in operating systems for memory management.

What it does:
Simulates page replacement in a system with 3 frames of memory
Processes a sequence of 12 page references: {2,3,2,1,5,2,4,5,3,2,5,2}
Uses FIFO strategy: when memory is full, the oldest page is replaced
Counts and displays page faults (when a requested page isn't in memory)
Key issues in the code:
Bug in line 19: for(i=0;i<12;i++) should be for(i=0;i<3;i++) - it's checking frames, not pages
Incorrect page fault counting: It only counts replacements, not initial loads into empty frames
Uses deprecated conio.h (non-standard header)
How FIFO works:
Pages are loaded into frames in order
When all frames are full and a new page is needed, the oldest page (first-in) is removed
The top variable tracks which frame to replace next (circular queue)

The program displays the frame contents after each page reference and shows the total page faults at the end.