//Consumer
//Nathaniel Wainwright


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define bSize 5
#define Items 5

sem_t empty;
sem_t full;


int in=0;
int out=0;

int buffer[bSize];
pthread_mutex_t mutex;

void *consumer(void *con){
    
    for(int i=0; i<Items; ++i){
        sem_wait(&full);
        
        pthread_mutex_lock(&mutex);

        int item = buffer[out];

        printf("Consumer %d: Consume Item %d from %d\n", *((int *)con), item, out);

        out=(out+1)%bSize;

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);
    }

}

void *producer(void *pro){
    
    for(int i = 0; i<Items; ++i){
    
        int prod = rand();
    
        sem_wait(&empty);

        pthread_mutex_lock(&mutex);
    
        buffer[in] = prod;

        printf("Producer %d: Insert Item %d at %d\n", *((int *)pro),buffer[in],in);

        in = (in+1)%bSize;
    
        pthread_mutex_unlock(&mutex);

        sem_post(&full);
    }
}

int main(){

    pthread_t con[5],pro[5];
    pthread_mutex_init(&mutex, NULL);

    sem_init(&empty, 0, bSize);

    sem_init(&full, 0, 0);

    int c[5] = {1,2,3,4,5};

    for(int i=0; i<5; ++i){
        pthread_create(&pro[i], NULL, (void *)consumer, (void *)&c[i]);
    }

    for(int i=0; i<5; ++i){
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&c[i]);
    }

    for(int i = 0; i<5; ++i){
        pthread_join(pro[i], NULL);
    }

    for(int i = 0; i<5; ++i){
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}