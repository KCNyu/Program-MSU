#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include <wait.h>
#include<stdlib.h>
/*
int main()
{
//test1

        pid_t pid;
        pid=fork();
        if(pid==-1)
        {
                perror("Create process");
                return 1;
        }
        if(pid==0)
        {
                printf("we now in son!and my_pid==%d and pid_father==%d \n",
                                (int)getpid(),
                                (int)getppid());
                return 0;
        }
        printf("I am father my pid==%d ,my son pid==%d\n",(int)getpid(),(int)getppid());
*/
//test2
/*
        printf("Hellow");
        //fflush(stdout);
        fork();
        printf("TTT\n");
        */
        
//test3
/*        
        fork();
        fork();
        fork();
        printf("me %d father %d\n",(int)getpid(),(int)getppid());        
        
*/
//test4       
/*   
        fork();
        fork();
        fork();
        wait(NULL);
        wait(NULL);
        wait(NULL);
        printf("me %d father %d\n",(int)getpid(),(int)getppid());  

        return 0;
        
 }

//test 5
 int main(int argc,char **argv)
 {
    if(argc<2)
    {
       printf("Need the number of processes!\n");
       return 1;
    }
    int num=atoi(argv[1]);
    int cont=1;
    pid_t fpid;
    for(int i=0;i<num;i++)
    {
        fpid=fork();
        if(fpid<0)
       {
          perror("erron");
          exit(1);
       }         
        if(fpid==0)
       {
           printf("i am progress%d - %d\n",cont,getpid());
	   cont++;
       }
        else
       {
       
          break;//返回值为大于0的进程是父进程，判断如果此进程是父进程就跳出循环     
       }
    }
    return 0;
 }       
*/
//test 6
 int main(int argc,char **argv)
 {
    if(argc<2)
    {
       printf("Need the number of processes!\n");
       return 1;
    }
    int num=atoi(argv[1]);
    int cont=1;
    pid_t fpid;
    for(int i=0;i<num;i++)
    {
        fpid=fork();
        if(fpid<0)
       {
          perror("erron");
          exit(1);
       }         
        if(fpid==0)
       {   
           
           //printf("i am progress %d - %d\n",cont,getpid());
	   cont++;
       }
        else
       {
       
          wait(NULL);
          printf("i am progress %d - %d\n",cont,getpid());
          break;//返回值为大于0的进程是父进程，判断如果此进程是父进程就跳出循环     
       }
    }
    return 0;
 }               
        
        
        
        
        
        
        
        
        
        
        
        
        
       

