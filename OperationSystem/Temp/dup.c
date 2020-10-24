#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/wait.h>
#include<string.h>
int main(int argc,char **argv)
{
    int fd1;
    int fd2;
    pid_t pid;
    int status;
    fd1 = open(argv[1],O_CREAT|O_WRONLY,0600);
    if(fd1<0)
    {
      perror("CREATE");
      exit(-1);
    }
    fd2 = open(argv[2],O_RDONLY);
    
    pid=fork();
    if(pid<0)
    {
      perror("fork");
      exit(-1);
    }
    if(pid==0)
    {
      char *a[4]={argv[3],argv[4],argv[5],NULL};
      dup2(fd1,1);
      dup2(fd2,0);
      close(fd1);
      close(fd2);
      execvp(argv[3],a);
      fprintf(stderr,"We can not create the program '%s': %s\n",argv[3],strerror(errno));
      exit(1);   
    }
    close(fd1);
    close(fd2);
    wait(&status);
    if(WIFEXITED(status))
    {
      if(WEXITSTATUS(status)==0)
          printf("OK\n");
      else
          printf("He successfully %d\n",WEXITSTATUS(status));    
    }
  
    return 0;
}
