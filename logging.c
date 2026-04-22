
#include <stdio.h>
#include <pthread.h>

#define SIZE 5
char buffer[SIZE][100];
int count = 0;

pthread_mutex_t lock;

void produce(const char *msg) {
    pthread_mutex_lock(&lock);
    if (count < SIZE) {
        snprintf(buffer[count++], 100, "%s", msg);
    }
    pthread_mutex_unlock(&lock);
}

void consume() {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < count; i++) {
        printf("[LOG] %s\n", buffer[i]);
    }
    count = 0;
    pthread_mutex_unlock(&lock);
}
