#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define P(x)  sem_wait(&x)
#define V(x)  sem_post(&x)
#define n 8
sem_t empty;
sem_t full;

void *producer(void *arg)
{
	while(1)
	{
		P(empty);
		sleep(3);
		printf("producer\n");
		V(full);
	}
}

void *buy(void *arg)
{
	while(1)
	{
		P(full);
		sleep(1);
		printf("buy\n");
		V(empty);
		
	}
}

int main(int argc, const char *argv[])
{
	pthread_t id[2];

	int log = sem_init(&empty, 0, n);
	if(log != 0)
	{
		printf("sem_init erroe");
		return 0;
	}
	log = sem_init(&full, 0, 0);
	if(log != 0)
	{
		printf("sem_init erroe");
		return 0;
	}

	pthread_create(&id[0], NULL, producer, NULL);
	pthread_create(&id[1], NULL, buy, NULL);

	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);

	return 0;
}
