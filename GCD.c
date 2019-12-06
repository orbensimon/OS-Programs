#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/time.h>

#define N 6

int gcd_sec_vol(int,int);
int gcd(int,int);


void main()
{
 struct timeval t1,t2,t3,t4;
 double eltime,eltime2;
 int arr[N];
 int i,j,forkres,forkres2,gcdres;
 srand(time(NULL));
 for(i=0;i<N;i++)
  arr[i]=2 + rand() % 200; // to restrict the range of the random numbers
 forkres=fork();
 if(forkres==0)
 {
  gettimeofday(&t1,NULL);
   for(i=0;i<N;i++)
   {
    for(j=0;j<N;j++)
    {
     if(arr[i]>arr[j])
      gcdres=gcd(arr[i],arr[j]);
     else
      gcdres=gcd(arr[j],arr[i]);
     if(gcdres != 1)
      printf("GCD(%d,%d)= %d mypid is %d\n",arr[i],arr[j],gcdres,getpid());
    }
   }
  gettimeofday(&t2,NULL);
  eltime=(t2.tv_sec - t1.tv_sec) * 1000.0;
  eltime+=(t2.tv_usec - t1.tv_usec) / 1000.0;
  printf("I am child number 1 my pid is: %d\ntime elapsed is: %lf\n\n",getpid(),eltime);
  exit(0);
 }

 else
 {
  forkres2=fork();
  if(forkres2==0)
  {
   gettimeofday(&t3,NULL);
   for(i=0;i<N;i++)
   {
    for(j=0;j<N;j++)
     if((gcdres = (gcd_sec_vol(arr[i],arr[j]))) != 1 && i != j)
      printf("GCD(%d,%d)= %d mypid is %d\n",arr[i],arr[j],gcdres,getpid());
   }
  }
  gettimeofday(&t4,NULL);
  eltime2=(t4.tv_sec - t3.tv_sec) * 1000.0;
  eltime2+=(t4.tv_usec - t3.tv_usec) / 1000.0;
  printf("I am child number 2 my pid is: %d\ntime elapsed is: %lf\n\n",getpid (),eltime2);
  exit(0);
 } 
 printf("Main Proces end!\n");
}

int gcd(int a,int b)
{
 if(a==0)
  return b;
 return gcd(b%a,a);
}

int gcd_sec_vol(int a,int b)
{
 int min;
 int i;
 if(a>b)
  min=b;
 else
  min=a;
 for(i=min;i>2;i++)
  if(a % i == 0 && b % i == 0)
   return i;
 return 1;
}
