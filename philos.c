#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room;
sem_t chopstick[5];
void *philosopher(void*);
void eat(int);

int main() {
    int i;
    int a[5];
    pthread_t tid[5];

    // Initialize room and chopsticks
    sem_init(&room, 0, 4);
    for (i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1);
        a[i] = i;
    }

    // Create philosopher threads
    for (i = 0; i < 5; i++) {
        if (pthread_create(&tid[i], NULL, philosopher, &a[i]) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < 5; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

void* philosopher(void* num) {
    int phil = *(int*)num;

    sem_wait(&room);
    printf("\nPhilosopher %d has entered the room", phil);
    fflush(stdout);

    sem_wait(&chopstick[phil]);
    sem_wait(&chopstick[(phil + 1) % 5]);

    eat(phil);
    sleep(2);

    printf("\nPhilosopher %d has finished eating", phil);
    fflush(stdout);

    sem_post(&chopstick[(phil + 1) % 5]);
    sem_post(&chopstick[phil]);
    sem_post(&room);

    return NULL;
}

void eat(int phil) {
    printf("\nPhilosopher %d is eating", phil);
    fflush(stdout);
}

