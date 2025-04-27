#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the buffer

// Shared buffer
int buffer[BUFFER_SIZE];

// Semaphores and mutex
sem_t empty;      // Counting semaphore for empty slots
sem_t full;       // Counting semaphore for full slots
pthread_mutex_t mutex;  // Mutex for mutual exclusion

// Function to simulate the producer
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100;  // Produce an item (random number)
        sem_wait(&empty);  // Wait if the buffer is full

        pthread_mutex_lock(&mutex);  // Lock the mutex to access the buffer
        // Add the item to the buffer
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (buffer[j] == 0) {
                buffer[j] = item;
                printf("Produced item %d at position %d\n", item, j);
                break;
            }
        }
        pthread_mutex_unlock(&mutex);  // Unlock the mutex

        sem_post(&full);  // Signal that a new item has been added
        sleep(1);  // Simulate time taken to produce an item
    }
    return NULL;
}

// Function to simulate the consumer
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);  // Wait if the buffer is empty

        pthread_mutex_lock(&mutex);  // Lock the mutex to access the buffer
        // Remove an item from the buffer
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (buffer[j] != 0) {
                item = buffer[j];
                buffer[j] = 0;
                printf("Consumed item %d from position %d\n", item, j);
                break;
            }
        }
        pthread_mutex_unlock(&mutex);  // Unlock the mutex

        sem_post(&empty);  // Signal that a new slot is empty
        sleep(2);  // Simulate time taken to consume an item
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Set the empty slots semaphore to BUFFER_SIZE
    sem_init(&full, 0, 0);  // Set the full slots semaphore to 0
    pthread_mutex_init(&mutex, NULL);  // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}