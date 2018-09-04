#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define P(x) sem_wait(&x)
#define V(x) sem_post(&x)


sem_t empty;
sem_t full;
pthread_mutex_t mutex;
void *producer(void *arg)
{
	while(1)
	{
		P(empty);
		pthread_mutex_lock(&mutex);
		sleep(1);
		printf("producer\n");
		pthread_mutex_unlock(&mutex);
		usleep(100);
		V(full);
	}

}

void *consumer(void *arg)
{
	while(1)
	{
		P(full);
		pthread_mutex_lock(&mutex);
		sleep(1);
		printf("consumer\n");
		pthread_mutex_unlock(&mutex);
		usleep(100);
		V(empty);
	}

}

int main(int argc, const char *argv[])
{
	pthread_t id[2];
	int log;
	log = sem_init(&empty, 0, 8);
	if(log != 0)
	{
		printf("sem_init empty error!");
		return 0;
	}
	log = sem_init(&full, 0, 0);
	if(log != 0)
	{
		printf("sem_init full error!");
		return 0;
	}
	pthread_mutex_init(&mutex, NULL);
	
	pthread_create(&id[0], NULL, producer, NULL);
	pthread_create(&id[1], NULL, consumer, NULL);
	
	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);

	return 0;
}
