// Include necessary header files for pthreads, input/output, and standard library functions
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Global variable to store the cumulative sum (shared data between threads)
int sum = 0; 

// Thread function that will be executed by the created thread
void *runner(void *param) {
    // Convert the string parameter to an integer (the upper limit for summation)
    int upper = atoi(param);
    
    // Loop from 1 to the upper limit, adding each value to the shared sum variable
    for (int i = 1; i <= upper; i++)
        sum += i; // Add current number to the shared sum
    
    // Exit the thread (equivalent to return statement for threads)
    pthread_exit(0);
}

// Main function where program execution begins
int main(int argc, char *argv[]) {
    // Declare a thread identifier variable
    pthread_t tid;
    
    // Declare a thread attribute object
    pthread_attr_t attr;
    
    // Check if the correct number of command-line arguments is provided (1 argument expected)
    if (argc != 2) {
        // Print error message to standard error if incorrect usage
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        // Return 1 to indicate an error
        return 1;
    }
    
    // Initialize the thread attribute object with default attributes
    pthread_attr_init(&attr);
    
    // Create a new thread with default attributes that will execute the runner function
    // Pass the first command-line argument to the thread function
    pthread_create(&tid, &attr, runner, argv[1]);
    
    // Wait for the created thread to finish execution before continuing
    pthread_join(tid, NULL);
    
    // Print the final sum calculated by the thread
    printf("sum = %d\n", sum);
    
    // Return 0 to indicate successful program execution
    return 0;
}
