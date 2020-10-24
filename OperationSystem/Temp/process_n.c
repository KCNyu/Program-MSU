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
   pid_t pid;
   char *program_list=argv[1];
   int start_pos=1;
   int states;
   for(int i=1;i<argc;i++)
   {
     if(strcmp(argv[i],"--")==0)
     {
       pid=fork();
         if(pid<0)
         {
            perror("FORK");
            return 1;
         } 
         if(pid==0)
         {
            char **args=argv+start_pos;
            argv[i]=NULL;
            if(execvp(program_list,args)<0)
               {
                 fprintf(stderr,"We can not create the program '%s': %s\n",program_list,strerror(errno));
                 return 1;
               }
         }
         wait(&states);
         if(WIFEXITED(states))
        {
         if(WEXITSTATUS(states)==0)
          printf("OK\n");
         else
          printf("He successfully %d\n",WEXITSTATUS(states));    
        }
         program_list=argv[i+1];
         start_pos=i+1;
       
     }
     
   }
   return 0;
   
}
