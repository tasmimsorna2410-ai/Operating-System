#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOTAL 5

sem_t stick[TOTAL];

void *dine(void *arg) {
    int me = *(int *)arg;

    printf("Philosopher %d is Thinking......\n", me);
    sleep(1);

    sem_wait(&stick[me]);
    sem_wait(&stick[(me + 1) % TOTAL]);

    printf("\nPhilosopher %d is Eating!!!!!!\n", me);
    sleep(2);

    sem_post(&stick[me]);
    sem_post(&stick[(me + 1) % TOTAL]);
    printf("\nPhilosopher %d finished eating and left chopsticks........\n", me);

    return NULL;
}

int main() {
    pthread_t th[TOTAL];
    int num[TOTAL], k;

    for (k = 0; k < TOTAL; k++)
        sem_init(&stick[k], 0, 1);

    for (k = 0; k < TOTAL; k++) {
        num[k] = k;
        pthread_create(&th[k], NULL, dine, &num[k]);
    }

    for (k = 0; k < TOTAL; k++)
        pthread_join(th[k], NULL);

    for (k = 0; k < TOTAL; k++)
        sem_destroy(&stick[k]);

    printf("\n\nAll philosophers have finished eating.\n");

    return 0;
}
