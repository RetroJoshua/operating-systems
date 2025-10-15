#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Function that will be executed by the thread
void* thread_function(void* arg) {
    printf("Inside the thread function\n");
    sleep(2); // Simulate some work
    printf("Thread execution completed\n");
    return NULL;
}

int main() {
    pthread_t thread_id;

    printf("Creating a new thread\n");

    // Create a new thread
    if (pthread_create(&thread_id, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for the thread to finish\n");

    // Wait for the thread to complete
    if (pthread_join(thread_id, NULL) != 0) {
        perror("Failed to join thread");
        exit(EXIT_FAILURE);
    }

    printf("Thread has finished execution\n");

    return 0;
}