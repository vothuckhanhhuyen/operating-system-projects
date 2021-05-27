#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t reader_mutex;
sem_t no_writer;
sem_t no_reader;
sem_t writer_mutex;
int reader = 0;
int writers = 0;
int num1 = 0;
int num2 = 0; 
void *writer(void *a){
	sleep(0);
	sem_wait(&writer_mutex);
	writers ++;
	if(writers == 1){
		sem_wait(&no_reader);
	}
	sem_post(&writer_mutex);
	sem_wait(&no_writer);
	int m = ++ num1;
	printf("The writer %d is writing\n",m);
	sleep(2);
	printf("The writer %d is stop writing\n",m);
	sem_post(&no_writer);
	sem_wait(&writer_mutex);
	writers --;
	if(writers == 0){
		sleep(1);
		sem_post(&no_reader);
	}
	sem_post(&writer_mutex);
}
void *readers(void *b){
	sleep(0);
	sem_wait(&no_reader);
	sem_wait(&reader_mutex);
	reader += 1;
	if(reader == 1){
		sem_wait(&no_writer);
	}
	sem_post(&reader_mutex);
	sem_post(&no_reader);
	sleep(1);
	int m = ++ num2;
	printf("The reader %d is reading\n",m);
	sleep(2);
	sem_wait(&reader_mutex);
	printf("The reader %d is stop reading\n",m);
	reader -= 1;
	if(reader == 0){
		sem_post(&no_writer);
	}
	sem_post(&reader_mutex);
}
 
int main( int argc, char *argv[] )  {
	int n = 15;
	sem_init(&writer_mutex, 0, 1);
	sem_init(&reader_mutex, 0, 1);
	sem_init(&no_writer, 0, 1);
	sem_init(&no_reader, 0, 1);
	pthread_t pthread_id[n];
	pthread_create(&pthread_id[0], NULL, readers, NULL);
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
	pthread_create(&pthread_id[13], NULL, readers, NULL);
	pthread_create(&pthread_id[14], NULL, writer, NULL);
	pthread_create(&pthread_id[15], NULL, writer, NULL);	
	getch();
	return 0;
}
