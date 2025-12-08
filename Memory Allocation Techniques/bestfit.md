Develop a C program to simulate the following contiguous memory allocation Techniques: 
a) Best fit b) First fit c) Worest fit. 
## Concept:
One of the simplest methods for memory allocation is to divide memory into several fixed-sized partitions. Each partition may contain exactly one process. In this multiple-partition method, when a partition is free, a process is selected from the input queue and is loaded into the free partition. When the process terminates, the partition becomes available for another process. The operating system keeps a table indicating which parts of memory are available and which are occupied. Finally, when a process arrives and needs memory, a memory section large enough for this process is provided. When it is time to load or swap a process into main memory, and if there is more than one free block of memory of sufficient size, then the operating system must decide which free block to allocate. Best-fit strategy chooses the block that is closest in size to the request.

## Algorithm:
- Step 1- Input memory blocks and processes with sizes. 
- Step 2- Initialize all memory blocks as free. 
- Step 3- Start by picking each process and find the minimum block size that can be  assigned to  current process i.e.,  find min(bockSize[1],    blockSize[2],.....blockSize[n]) >   processSize[current], 
- Step 4: if found then assign    it to the current process. 
- 5- If not then leave that process and keep checking    the further processes. 

OUTPUT: 
$make bf 
$./bf 
Enter the number of blocks: 3 
Enter the number of files: 2 
Enter the size of the blocks:- 
Block 1: 5 
Block 2: 2 
Block 3: 7

Enter the size of the files:- 
File 1: 1 
File 2: 4 
 
File No     File Size               Block No             Block Size           Fragment 
1                              1                             2                             2                             1 
2                              4                              1                              5                             1