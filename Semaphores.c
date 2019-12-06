#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
 
sem_t sem1;
sem_t sem2;

void* Monkey1 (void* t){

	while(1){
		 sleep(2);
		 sem_post(&sem1);
		 printf("Monkey 1\n");
	}

}

void* Monkey2 (void* t){

     while(1){
        sem_wait(&sem1);
        sem_wait(&sem1);
        sem_post(&sem2);
        printf("Monkey 2\n");
     }

}

void* Monkey3 (void* t){

    while(1){
       sem_wait(&sem2);
       sem_wait(&sem2);
       printf("Monkey 3\n");
    }

}

int main (){
   pthread_t  m1,m2,m3; 
   int flag1;

   flag1 = sem_init(&sem1,0,0);
   flag1 = sem_init(&sem2,0,0);
   pthread_create (&m1, NULL, Monkey1, (void*)"Thread A" );
   pthread_create (&m2, NULL, Monkey2, (void*)"Thread A" );
   pthread_create (&m3, NULL, Monkey3, (void*)"Thread A" );

   pthread_join(m1, NULL);
   pthread_join(m2, NULL);
   pthread_join(m3, NULL);
   
   return 0;
}
