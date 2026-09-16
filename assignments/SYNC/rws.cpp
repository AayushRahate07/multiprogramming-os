#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

sem_t rw_mutex;       
sem_t mutex_readcnt;  
int read_count = 0;   

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER; 

void* reader(void* arg)
{
    int id = *(int*)arg;

    while(true)
    {
        sem_wait(&mutex_readcnt);
        read_count++;
        if(read_count == 1) {
            sem_wait(&rw_mutex); 
        }
        sem_post(&mutex_readcnt);

        pthread_mutex_lock(&print_mutex);
        cout << "Reader " << id << " is READING. (Total readers: " << read_count << ")" << endl;
        pthread_mutex_unlock(&print_mutex);
        usleep(100000); 

        sem_wait(&mutex_readcnt);
        read_count--;
        if(read_count == 0) {
            sem_post(&rw_mutex); 
        }
        sem_post(&mutex_readcnt);

        pthread_mutex_lock(&print_mutex);
        cout << "Reader " << id << " finished reading." << endl;
        pthread_mutex_unlock(&print_mutex);
        usleep(150000); 
    }
    return NULL;
}

void* writer(void* arg)
{
    int id = *(int*)arg;

    while(true)
    {
        sem_wait(&rw_mutex);

        pthread_mutex_lock(&print_mutex);
        cout << "[WRITER] Writer " << id << " is WRITING." << endl;
        pthread_mutex_unlock(&print_mutex);
        usleep(200000); 

        sem_post(&rw_mutex);

        pthread_mutex_lock(&print_mutex);
        cout << "[WRITER] Writer " << id << " finished writing." << endl;
        pthread_mutex_unlock(&print_mutex);
        usleep(250000); 
    }
    return NULL;
}

int main()
{
    int num_readers = 3;
    int num_writers = 2;

    pthread_t r_threads[num_readers], w_threads[num_writers];
    int r_id[num_readers], w_id[num_writers];

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex_readcnt, 0, 1);

    for (int i = 0; i < num_readers; i++) {
        r_id[i] = i + 1;
        pthread_create(&r_threads[i], NULL, reader, &r_id[i]);
    }

    for (int i = 0; i < num_writers; i++) {
        w_id[i] = i + 1;
        pthread_create(&w_threads[i], NULL, writer, &w_id[i]);
    }

    for (int i = 0; i < num_readers; i++) {
        pthread_join(r_threads[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(w_threads[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex_readcnt);

    return 0;
}