#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int room1 = 0;
int room2 = 0;
sem_t t1;
sem_t t2;
sem_t mutex;

void m_1(){
	sem_wait(&mutex);
	room1 ++;
	sem_post(&mutex);
	
	sem_wait(&t1);
	room2 ++;
	sem_wait(&mutex);
	room1 --;
	
	if(room1 == 0) {
		sem_post(&mutex);
		sem_post(&t2);
	}
	else {
		sem_post(&mutex);
		sem_post(&t1);
	}
		
		sem_wait(&t2);
		room2 --;
}
void m_2() {
	
	if(room2 == 0) {
		sem_post(&t1);
	}
	else {
		sem_post(&t2);
	}
}

void *r1() {
	while(1){
		m_1();
		sleep(0);
		printf("Hello\n");
		m_2();
	}
}

void *r2() {
	while(1){
		m_1();
		sleep(2);
		printf("Thanks\n");
		m_2();
	}
}
void *r3() {
	while(1){
		m_1();
		sleep(1);
		printf("Goodbye\n");
		m_2();
	}
}
int main(){
	sem_init(&mutex, 0, 1);
	sem_init(&t1, 0, 1);
	sem_init(&t2, 0, 0);
	int n = 3;
	pthread_t pthread_id[n];
	pthread_create(&pthread_id[0], NULL, r1,NULL); 
	pthread_create(&pthread_id[1], NULL, r2,NULL);  
	pthread_create(&pthread_id[2], NULL, r3,NULL); 
	getch();
	return 0;
}
