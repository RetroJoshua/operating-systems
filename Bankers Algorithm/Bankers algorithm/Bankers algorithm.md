PROGRAM STATEMENT: 
Develop a C program to simulate Bankers Algorithm for DeadLock Avoidance. 
CONCEPT: 
Deadlock is a situation where in two or more competing actions are waiting f or the other to 
finish, and thus neither ever does. When a new process enters a system, it must declare the maximum 
number of instances of each resource type it needed. This number may exceed the total number of 
resources in the system. When the user request a set of resources, the system must determine whether the 
allocation of each resources will leave the system in safe state. If it will the resources are allocation; 
otherwise the process must wait until some other process release the resources. 
Data structures 
n-Number of process, m-number of resource types. 
Available: Available[j]=k, k – instance of resource type Rj is available. Max: If max[i, j]=k, Pi may 
request at most k instances resource Rj. 
Allocation: If Allocation [i, j]=k, Pi allocated to k instances of resource Rj Need: If Need[I, j]=k, Pi may 
need k more instances of resource type Rj, Need[I, j]=Max[I, j]-Allocation[I, j]; 
Safety Algorithm 
1.Work and Finish be the vector of length m and n respectively, Work=Available and Finish[i] =False. 
2.Find an i such that both 
Finish[i] =False Need<=Work 
If no such I exists go to step 4. 
3. work= work + Allocation, Finish[i] =True; 
4. if Finish[1]=True for all I, then the system is in safe state. 
Resource request algorithm 
Let Request i be request vector for the process Pi, If request i=[j]=k, then process Pi wants k instances of 
resource type Rj. 
1. if Request<=Need I go to step 2. Otherwise raise an error condition. 
2. if Request<=Available go to step 3. Otherwise Pi must since the resources are available. 
3. Have the system pretend to have allocated the requested resources to process Pi by modifying the 
state as follows;  
 
Available=Available-Request I; Allocation I =Allocation +Request I; Need i=Need i-Request I; 
If the resulting resource allocation state is safe, the transaction is completed and process Pi is allocated 
its resources. However if the state is unsafe, the Pi must wait for Request i and the old 
resource-allocation state is restored. 

## Algorithm
1. Start the program. 
2. Get the values of resources and processes. 
3. Get the avail value. 
4. After allocation find the need value. 
5. Check whether its possible to allocate. 
6. If it is possible then the system is in safe state. 
7. Else system is not in safety state. 
8. If the new request comes then check that the system is in safety. 
9. or not if we allow the request. 
10. stop the program. 
11. end 


OUTPUT: 
 $make dal 
 $./dal 
Enter the no. of processes and resources: 4 3 
Enter the claim matrix: 
3 2 2 
6 1 3 
3 1 4 
4 2 2 
Enter the allocation matrix: 
1 0 0 
6 1 2 
2 1 1 
0 0 2 
Resource vector:9 3 6 
All the resources can be allocated to Process 2 
Available resources are: 6 2 3 
Process 2 executed?:y 
All the resources can be allocated to Process 3 
Avaiable resources are: 8 3 4 
30     
Prcess 3 executed?:y 
All the resources can be allocated to Process 4 
Avilable resources are: 8 3 6 
Prcess 4 executed?:y 
All the resources can be allocated to Process 1 
Aailable resources are: 9 3 6 
Prcess 1 executed?:y 
System is in safe mode 
The given state is safe state 