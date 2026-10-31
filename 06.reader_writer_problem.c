#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t lock, wrt;
int value = 0, readers = 0;

void *readData(void *arg) {
    int no;
    no = ((int)arg);

    sem_wait(&lock);
    readers++;
    if (readers == 1)
        sem_wait(&wrt);
    sem_post(&lock);

    printf("Data read by the reader R[%d] is %d\n", no, value);
    sleep(1);

    sem_wait(&lock);
    readers--;
    if (readers == 0)
        sem_post(&wrt);
    sem_post(&lock);
}

void *writeData(void *arg) {
    int no;
    no = ((int)arg);

    sem_wait(&wrt);
    value++;
    printf("Data written by the writer W[%d] is %d\n", no, value);
    sleep(1);
    sem_post(&wrt);
}

int main() {
    int k, tmp;
    pthread_t rd[10], wr[10];

    sem_init(&lock, 0, 1);
    sem_init(&wrt, 0, 1);

    for (k = 0; k <= 3; k++) {
        pthread_create(&wr[k], NULL, writeData, (void *)k);
        pthread_create(&rd[k], NULL, readData, (void *)k);
    }

    for (k = 0; k <= 3; k++) {
        pthread_join(wr[k], NULL);
        pthread_join(rd[k], NULL);
    }

    return 0;
}
