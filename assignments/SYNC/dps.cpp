#include<iostream>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

sem_t chopstick[5];
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER; // Protects terminal output

void* philosopher(void* arg)
{
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % 5;

    while(true)
    {
        // 1. Thinking Phase (Crucial to give other threads time to run)
        pthread_mutex_lock(&print_mutex);
        cout << "Philosopher " << id << " is Thinking." << endl;
        pthread_mutex_unlock(&print_mutex);
        usleep(100000); // 100ms

        // 2. Grabbing Phase
        if(id == 4)
        {
            sem_wait(&chopstick[right]);
            sem_wait(&chopstick[left]);
        }
        else
        {
            sem_wait(&chopstick[left]);
            sem_wait(&chopstick[right]);
        }

        // 3. Eating Phase
        pthread_mutex_lock(&print_mutex);
        cout << "Philosopher " << id << " is EATING." << endl;
        pthread_mutex_unlock(&print_mutex);
        usleep(150000); // 150ms

        // 4. Putting Down Phase
        sem_post(&chopstick[left]);
        sem_post(&chopstick[right]);

        pthread_mutex_lock(&print_mutex);
        cout << "Philosopher " << id << " finished eating." << endl;
        pthread_mutex_unlock(&print_mutex);
    }
    return NULL;
}

int main()
{
    pthread_t threads[5];
    int id[5];

    for (int i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1);
        id[i] = i; 
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}