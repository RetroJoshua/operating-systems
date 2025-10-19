#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

// Semaphores and mutex
sem_t empty;  // Count of empty slots
sem_t full;   // Count of full slots
pthread_mutex_t mutex;  // Mutex for critical section

// Buffer
int buffer[BUFFER_SIZE];
int in = 0;   // Index for producer
int out = 0;  // Index for consumer

// Function to produce an item and add it to the buffer
void* producer(void* arg) {
    int item = *((int*)arg);
    
    // Wait if buffer is full
    sem_wait(&empty);
    
    // Lock the critical section
    pthread_mutex_lock(&mutex);
    
    // Add item to buffer
    buffer[in] = item;
    printf("\nProducer produces item %d at position %d", item, in);
    in = (in + 1) % BUFFER_SIZE;
    
    // Unlock the critical section
    pthread_mutex_unlock(&mutex);
    
    // Signal that buffer has one more full slot
    sem_post(&full);
    
    return NULL;
}

// Function to consume an item and remove it from buffer
void* consumer(void* arg) {
    int item;
    
    // Wait if buffer is empty
    sem_wait(&full);
    
    // Lock the critical section
    pthread_mutex_lock(&mutex);
    
    // Remove item from buffer
    item = buffer[out];
    printf("\nConsumer consumes item %d from position %d", item, out);
    out = (out + 1) % BUFFER_SIZE;
    
    // Unlock the critical section
    pthread_mutex_unlock(&mutex);
    
    // Signal that buffer has one more empty slot
    sem_post(&empty);
    
    return NULL;
}

// Driver Code
int main() {
    int choice;
    int item_count = 0;
    pthread_t tid;
    
    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially all slots are empty
    sem_init(&full, 0, 0);              // Initially no slots are full
    pthread_mutex_init(&mutex, NULL);
    
    printf("\n1. Press 1 for Producer");
    printf("\n2. Press 2 for Consumer");
    printf("\n3. Press 3 for Exit\n");
    
    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                // Check if buffer is full
                int empty_val;
                sem_getvalue(&empty, &empty_val);
                
                if (empty_val > 0) {
                    item_count++;
                    int* item = malloc(sizeof(int));
                    *item = item_count;
                    
                    pthread_t prod_thread;
                    pthread_create(&prod_thread, NULL, producer, item);
                    pthread_detach(prod_thread);
                } else {
                    printf("Buffer is full!");
                }
                break;
            }
            
            case 2: {
                // Check if buffer is empty
                int full_val;
                sem_getvalue(&full, &full_val);
                
                if (full_val > 0) {
                    pthread_t cons_thread;
                    pthread_create(&cons_thread, NULL, consumer, NULL);
                    pthread_detach(cons_thread);
                } else {
                    printf("Buffer is empty!");
                }
                break;
            }
            
            case 3:
                // Cleanup
                sem_destroy(&empty);
                sem_destroy(&full);
                pthread_mutex_destroy(&mutex);
                printf("\nExiting...\n");
                exit(0);
                
            default:
                printf("Invalid choice!");
        }
        
        // Small delay to allow threads to complete
        usleep(100000);
    }
    
    return 0;
}