#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>
using namespace std;

const int BUFFER_SIZE = 5;
vector<int> buffer(BUFFER_SIZE);
int in = 0;
int out = 0;
int item_counter = 1;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t mutex_buffer;
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg)
{
    int id = *(int *)arg;

    while (true)
    {
        int item = item_counter++;
        usleep(100000);

        sem_wait(&empty_slots);
        pthread_mutex_lock(&mutex_buffer);

        buffer[in] = item;
        pthread_mutex_lock(&print_mutex);
        cout << "[PRODUCER " << id << "] Produced item " << item << " at index " << in << endl;
        pthread_mutex_unlock(&print_mutex);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex_buffer);
        sem_post(&full_slots);

        usleep(150000);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int id = *(int *)arg;

    while (true)
    {
        sem_wait(&full_slots);
        pthread_mutex_lock(&mutex_buffer);

        int item = buffer[out];
        pthread_mutex_lock(&print_mutex);
        cout << "[CONSUMER " << id << "] Consumed item " << item << " from index " << out << endl;
        pthread_mutex_unlock(&print_mutex);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex_buffer);
        sem_post(&empty_slots);

        usleep(200000);
    }
    return NULL;
}

int main()
{
    int num_producers = 2;
    int num_consumers = 2;

    pthread_t p_threads[num_producers], c_threads[num_consumers];
    int p_id[num_producers], c_id[num_consumers];

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    pthread_mutex_init(&mutex_buffer, NULL);

    for (int i = 0; i < num_producers; i++)
    {
        p_id[i] = i + 1;
        pthread_create(&p_threads[i], NULL, producer, &p_id[i]);
    }

    for (int i = 0; i < num_consumers; i++)
    {
        c_id[i] = i + 1;
        pthread_create(&c_threads[i], NULL, consumer, &c_id[i]);
    }

    for (int i = 0; i < num_producers; i++)
    {
        pthread_join(p_threads[i], NULL);
    }
    for (int i = 0; i < num_consumers; i++)
    {
        pthread_join(c_threads[i], NULL);
    }

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&mutex_buffer);

    return 0;
}