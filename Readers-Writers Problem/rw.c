#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex, wrt;
int readcount = 0;
int shared_data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);  // First reader blocks writers
    sem_post(&mutex);
    
    // READING
    printf("Reader %d: read data = %d\n", id, shared_data);
    sleep(1);
    
    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);  // Last reader allows writers
    sem_post(&mutex);
    
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&wrt);  // Request exclusive access
    
    // WRITING
    shared_data++;
    printf("Writer %d: wrote data = %d\n", id, shared_data);
    sleep(2);
    
    sem_post(&wrt);  // Release exclusive access
    
    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    
    pthread_t readers[3], writers[2];
    int ids[5] = {1, 2, 3, 4, 5};
    
    // Create threads
    pthread_create(&readers[0], NULL, reader, &ids[0]);
    pthread_create(&readers[1], NULL, reader, &ids[1]);
    pthread_create(&writers[0], NULL, writer, &ids[2]);
    pthread_create(&readers[2], NULL, reader, &ids[3]);
    pthread_create(&writers[1], NULL, writer, &ids[4]);
    
    // Wait for completion
    for(int i = 0; i < 3; i++)
        pthread_join(readers[i], NULL);
    for(int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);
    
    return 0;
}