#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

#define BUF_SIZE 100
 
int main(int argc,char* argv[])
{
 int infd,infd2,outfd,forkres;
 char buff[BUF_SIZE];
 
 if(argc!=4)
 {
  printf("ERROR!\n");
  return 0;
 }
 infd=open(argv[1],O_RDONLY);
 if(infd==-1)
 {
  printf("ERROR file 1\n");
  return 1;
 }
 infd2=open(argv[2],O_RDONLY);
 if(infd2==-1)
 {
  printf("ERROR file 2\n");
  return 2;
 }
 outfd=open(argv[3],O_WRONLY);
 if(outfd==-1)
 {
  printf("ERROR file 3\n");
  return 3;
 }
 if((forkres=fork())==0)
 {
  while(read(infd2,&buff,1)!=0)
    write(outfd,&buff,1);
  execv("/home/braude/Labs/Lab4/lab4_8_exec.out",NULL);
 }
 wait();
 while(read(infd,&buff,1)!=0)
  write(outfd,&buff,1);
 close(infd);
 close(infd2);
 close(outfd);
 return 4;
}
