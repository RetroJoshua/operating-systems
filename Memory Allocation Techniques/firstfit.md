# Firstfit

## Concept:
This method keeps the free/busy list of jobs organized by memory location, low-ordered to high-ordered memory. In this method, first job claims the first available memory with space more than or equal to it's size. 
First Fit : This algorithm searches along the list looking for the first segment that is large enough to accommodate the process. The segment is then split into a hole and a process. This method is fast as the first available hole that is large enough to accommodate the process is used. 

## Algorithm:
Step 1: Input memory blocks with size and processes with size. 
Step 2: Initialize all memory blocks as free. 
Step 3: Start by picking each process and check if it can    be assigned to current block.  
Step 4:  If size-of-process <= size-of-block if yes then   assign and check for next process. 
Step 5: If not then keep checking the further blocks. 

OUTPUT:  
 $make ff 
 $./ff 
 
Process No.    Process Size    Block no. 
1              212             2 
2              417             5         
3              112             2 
4              426             Not Allocated