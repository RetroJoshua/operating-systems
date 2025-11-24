## CONCEPT: 
- In operating systems, memory allocation refers to the process of assigning memory to different processes or programs running on a computer system. 
- Fixed Size Partitioning: Each process is allotted to a fixed size continuous block in the main memory.  
- Variable Size Partitioning: Each process is allotted space depending upon its requirements. There is no  defined fixed-size block. 
- Worst Fit allocates a process to the partition which is largest sufficient among the freely available 
- partitions available in the main memory. If a large process comes at a later stage, then memory will not  have space to accommodate it. 

## ALGORITHM: 
- Step 1: Input memory blocks and processes with sizes. 
- Step 2: Initialize all memory blocks as free. 
- Step 3: Start by picking each process and find the    maximum block size that can be assigned to  current process i.e., find max(bockSize[1], blockSize[2],.....blockSize[n]) >    processSize[current], 
- Step 4:    if found then assign    it to the current process. 
- Step 5: If not then leave that process and keep checking    the further processes.

## Expected output:
OUTPUT: 
$make wf 
$./wf 
Enter the number of blocks: 3 
Enter the number of files: 2 
Enter the size of the blocks:- 
Block 1: 5 
Block 2: 2 
Block 3: 7 
Enter the size of the files:- 
File 1: 1 
File 2: 4
File No   File Size     Block No       Block   Size                  
1             1            1                            
2             4            3     
                               
           
5                             
7                             
Fragment 
4 
3 