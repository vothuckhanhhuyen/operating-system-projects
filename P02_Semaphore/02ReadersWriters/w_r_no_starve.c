#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t mutex;
sem_t turnstile;
sem_t roomEmpty;
int reader = 0;
int num1 = 0;
int num2 = 0; 
	
void *writer(void *a){
	sleep(1);
	sem_wait(&turnstile);
	sem_wait(&roomEmpty);
	int m = ++ num1;
	printf("The writer %d is writing\n", m);
	sleep(2);
	printf("The writer %d is stop writing\n", m);
	sem_post(&turnstile);
	sem_post(&roomEmpty);
}
void *readers(void *b){
	sleep(1);
	sem_wait(&turnstile);
	sem_post(&turnstile);
	sem_wait(&mutex);
	reader += 1;
	if(reader == 1){
		sem_wait(&roomEmpty);
	}
	sem_post(&mutex);
	sleep(1);
	int m = ++ num2;
	printf("The reader %d is reading\n", m);
	sleep(2);
	sem_wait(&mutex);
	printf("The reader %d is stop reading\n", m);
	reader -= 1;
	if(reader == 0){
		sem_post(&roomEmpty);
	}
	sem_post(&mutex);
}

int main( int argc, char *argv[] )  {
	int n = 12;
	sem_init(&mutex, 0, 1);
	sem_init(&roomEmpty, 0, 1);
	sem_init(&turnstile, 0, 1);
	pthread_t pthread_id[n];
	pthread_create(&pthread_id[1], NULL, writer, NULL);
	pthread_create(&pthread_id[2], NULL, readers, NULL);
	pthread_create(&pthread_id[3], NULL, writer, NULL);
	pthread_create(&pthread_id[4], NULL, readers, NULL);
	pthread_create(&pthread_id[5], NULL, readers, NULL);
	pthread_create(&pthread_id[6], NULL, readers, NULL);
	pthread_create(&pthread_id[7], NULL, readers, NULL);
	pthread_create(&pthread_id[8], NULL, writer, NULL);
	pthread_create(&pthread_id[9], NULL, readers, NULL);
	pthread_create(&pthread_id[10], NULL, readers, NULL);
	pthread_create(&pthread_id[11], NULL, readers, NULL);
	pthread_create(&pthread_id[12], NULL, writer, NULL);
	getch();
	return 0;
}
