#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

//sems
sem_t sem_agent;
sem_t sem_tobacco;
sem_t sem_paper;
sem_t sem_match;
sem_t tobacco;
sem_t match;
sem_t paper;
sem_t sem_mutex;

int tobaccoNum = 0;
int paperNum = 0;
int matchesNum = 0;

void *agentA(void *);
void *agentB(void *);
void *agentC(void *);
void *pusherA(void *);
void *pusherB(void *);
void *pusherC(void *);
void *smoker_with_tobacco(void *);
void *smoker_with_paper(void *);
void *smoker_with_match(void *);

pthread_mutex_t print_mutex;

int main( int argc, char *argv[] )  {
	
   pthread_t a1, a2, a3, p1, p2, p3, s1, s2, s3;
 

	sem_init(&sem_agent, 0, 1);
	sem_init(&sem_tobacco, 0, 0);
	sem_init(&sem_paper, 0, 0);
	sem_init(&sem_match, 0, 0);
	sem_init(&tobacco, 0, 0);
	sem_init(&paper, 0, 0);
	sem_init(&match, 0, 0);	
	sem_init(&sem_mutex, 0, 1);
    pthread_mutex_init(&print_mutex, NULL);

    pthread_create(&a1, NULL, agentA, NULL);
    pthread_create(&a2, NULL, agentB, NULL);
    pthread_create(&a3, NULL, agentC, NULL);
    pthread_create(&s1, NULL, smoker_with_tobacco, NULL);
    pthread_create(&s2, NULL, smoker_with_paper, NULL);
    pthread_create(&s3, NULL, smoker_with_match, NULL);
    pthread_create(&p1, NULL, pusherA, NULL);
    pthread_create(&p2, NULL, pusherB, NULL);
    pthread_create(&p3, NULL, pusherC, NULL);

    while(1){
    }

}


void *agentA(void *a){
	while(1){
		sem_wait(&sem_agent);
		sem_post(&sem_tobacco);
		sem_post(&sem_paper);
		sem_post(&sem_agent);
	}
}

void *agentB(void *b){
	while(1){
		sem_wait(&sem_agent);
		sem_post(&sem_tobacco);
		sem_post(&sem_match);
		sem_post(&sem_agent);
	}
}

void *agentC(void *c){
	while(1){
		sem_wait(&sem_agent);
		sem_post(&sem_paper);
		sem_post(&sem_match);
		sem_post(&sem_agent);
	}
}

void *smoker_with_tobacco(void *a){
	while(1){
		pthread_mutex_lock(&print_mutex);
		printf("S1 needs tobacco\n");
		pthread_mutex_unlock(&print_mutex);
		
		sem_wait(&tobacco);

		pthread_mutex_lock(&print_mutex);
		printf("S1 gets tobacco, roll cigarette\n");
		pthread_mutex_unlock(&print_mutex);
		


		pthread_mutex_lock(&print_mutex);
		printf("S1 rolls one and drops the tabacco\n\n" );
		pthread_mutex_unlock(&print_mutex);
		sleep(4);
	}
}

void *smoker_with_paper(void *b){
	while(1){
		pthread_mutex_lock(&print_mutex);
		printf("S2 needs Paper\n");
		pthread_mutex_unlock(&print_mutex);

		sem_wait(&paper);

		pthread_mutex_lock(&print_mutex);
		printf("S2 gets paper, roll cigarette\n");
		pthread_mutex_unlock(&print_mutex);

	
		pthread_mutex_lock(&print_mutex);
		printf("S2 rolls one and drops papers\n\n" );
		pthread_mutex_unlock(&print_mutex);
		sleep(4);
	}
}

void *smoker_with_match(void *c){
	while(1){
		pthread_mutex_lock(&print_mutex);
		printf("S3 needs matches\n");
		pthread_mutex_unlock(&print_mutex);

		sem_wait(&match);
		pthread_mutex_lock(&print_mutex);
		printf("S3 gets matches, roll cigarette\n");
		pthread_mutex_unlock(&print_mutex);


		pthread_mutex_lock(&print_mutex);
		printf("S3 rolls one and drops matches\n\n" );
		pthread_mutex_unlock(&print_mutex);

		sleep(4);
	}
}

void *pusherA(void *a){
	while(1){
			sem_wait(&sem_tobacco);
			pthread_mutex_lock(&print_mutex);
		
			pthread_mutex_unlock(&print_mutex);

			sem_wait(&sem_mutex);
				if(paperNum){
					paperNum -= 1;
					sem_post(&paper);
				}else if(matchesNum){
					matchesNum -= 1;
					sem_post(&match);
				}else{
					tobaccoNum += 1;
				}
			sem_post(&sem_mutex);
	}
}


void *pusherB(void *b){
	while(1){
		sem_wait(&sem_match);
		pthread_mutex_lock(&print_mutex);
		
		pthread_mutex_unlock(&print_mutex);

		sem_wait(&sem_mutex);
			if(paperNum){
				paperNum -= 1;
				sem_post(&match);
			}else if(tobaccoNum){
				tobaccoNum -= 1;
				sem_post(&tobacco);
			}else{
				matchesNum += 1;
			}
		sem_post(&sem_mutex);
	}
}

void *pusherC(void *c){
	while(1){
		sem_wait(&sem_paper);
		pthread_mutex_lock(&print_mutex);
	
		pthread_mutex_unlock(&print_mutex);

		sem_wait(&sem_mutex);
			if(tobaccoNum){
				tobaccoNum -= 1;
				sem_post(&tobacco);
			}else if(matchesNum){
				matchesNum -= 1;
				sem_post(&match);
			}else{
				paperNum += 1;
			}
		sem_post(&sem_mutex);
	}
}