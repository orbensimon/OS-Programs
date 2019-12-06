#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>

#define N 5

pthread_t threadarr[N];
int curr_thread;
void* f(void*)
;

int main()
{
 int arr[N];
 int i;

 for(i=0;i<N;i++)
 {
  arr[i]=i;
  if((pthread_create(&threadarr[i],NULL,f,&arr[i])) != 0)
  {
    printf("ERROR!\n");
    return 0;
  }
 }

 for(i=0;i<N;i++)
  pthread_join(threadarr[i],NULL);
 printf("Finish main\n");
 return 1;
}

void* f(void* a)
{
 struct timeval t1,t2;
 double eltime;
 int curr=*(int*)a;
 while(1)
 {
  gettimeofday(&t1,NULL);
  curr_thread=curr;
  while(curr_thread==curr)
   gettimeofday(&t2,NULL);
 
  gettimeofday(&t2,NULL);
  eltime=(t2.tv_sec-t1.tv_sec)*1000.0;
  eltime+=(t2.tv_usec-t1.tv_usec)/1000.0;
  printf("Time slice for thread %d= %lf ms\n",curr+1,eltime);
 }
}
 
   
 



