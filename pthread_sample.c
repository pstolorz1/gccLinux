#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    printf("Hello from thread!\n");
    printf("Value passed in argument %d\n", *(unsigned char*)arg);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    unsigned char val = 77;

    // Create thread
    pthread_create(&thread1, NULL, thread_func, &val);
    pthread_create(&thread2, NULL, thread_func, &val);

    // Wait for thread to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread finished\n");
    return 0;
}