/*================================================================
* Filename:shell.c
* Author: KCN_yu
* Createtime:Thu 05 Nov 2020 10:46:46 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <wait.h>
#include <stdbool.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

#define MAX 64

/////////////////////////////////////////////////////////////////////////////////

void Get_username(){
    struct passwd* pwd;
    pwd = getpwuid(getuid());
    printf("%s@",pwd->pw_name);
}
void Get_hostname(){
    char host[128];
    gethostname(host,sizeof(char)*128-1);
    printf("%s",host);
}
void Get_dir(){
    char dir[128];
    getcwd(dir,sizeof(char)*128);
    printf(":%s",dir);
}
void Print_prefix(){
    Get_username();
    Get_hostname();
    Get_dir();
    printf("# ");
}

/////////////////////////////////////////////////////////////////////////////////

char cmd[MAX][MAX];
int cmd_count = 0;
int pid;
int fd_pid[2];
bool IS_BUITIN = false,
     IS_EXTERNAL = false,
     IS_BACKGROUND = false,
     IS_END = false;
const char space[2] = " ";
char path_old[128];

void Input_command(){
    char* input = (char*)calloc(MAX,sizeof(char));
    char** cmd_tmp = (char**)calloc(sizeof(char*),MAX);
    if(fgets(input,MAX,stdin) != NULL){
        cmd_tmp[cmd_count++] = strtok(input,space);
        while((cmd_tmp[cmd_count] = strtok(NULL,space)) != NULL) cmd_count++;
        cmd_tmp[cmd_count-1][strlen(cmd_tmp[cmd_count-1])-1] = '\0';
    }
    for(int i = 0; i < cmd_count; i++) strcpy(cmd[i],cmd_tmp[i]);
}
void Analysis_command(){
    if(!strcmp(cmd[0],"") && IS_BACKGROUND){
        IS_BACKGROUND = false;
        IS_END = true;
    }
    else if(!(strcmp((cmd[0]),"cd")) || !(strcmp(cmd[0],"exit"))) IS_BUITIN = true;
    else{
        IS_EXTERNAL = true;
        if(!strcmp(cmd[cmd_count-1],"&")){
            IS_BACKGROUND = true;
            strcpy(cmd[cmd_count-1],"\0");
            cmd_count--;
        }
    }
}
void Run_builtin(){
    if(!strcmp(cmd[0],"exit")) exit(EXIT_SUCCESS);
    else if(!strcmp(cmd[0],"cd")){
        char cd_path[128];
        struct passwd* pwd;
        pwd = getpwuid(getuid());
        if((strlen(cmd[1])) == 0){
            sprintf(cd_path,"/%s",pwd->pw_name);
            strcpy(cmd[1],cd_path);
            cmd_count++;
        }
        else if(strcmp(cmd[1],"~") == 0){
            sprintf(cd_path,"/%s",pwd->pw_name);
            strcpy(cmd[1],cd_path);
        }
        else if(strcmp(cmd[1],"-") == 0){
            strcpy(cmd[1],path_old);
        }
        getcwd(path_old,sizeof(char)*128);
        if((chdir(cmd[1])) < 0) fprintf(stderr,"%s: failed\n",cmd[0]);
    }
}
bool Run_external_redirect(int left, int right){
    int input_num = 0, output_num = 0;
    char *input_file = NULL, *output_file = NULL;
    int end_index = right;
    for(int i = left; i < right; i++){
        if(!strcmp(cmd[i],"<")){
            input_num++;
            if(i+1 < right) input_file = cmd[i+1];
            if(end_index == right) end_index = i;
        }
        else if(!strcmp(cmd[i],">")){
            output_num++;
            if(i+1 < right) output_file = cmd[i+1];
            if(end_index == right) end_index = i;
        }
    }
    if(input_num == 1){
        int f;
        if((f = open(input_file,O_RDONLY)) < 0){
            fprintf(stderr,"failed to open the file '%s'",input_file);
            return false;
        }
    }
    if(input_num > 1 || output_num > 1){
        fprintf(stderr,"too many redirection operators");
        return false;
    }
    if(fork() == 0){
        if(input_num == 1){
            int f_input = open(input_file,O_RDONLY);
            dup2(f_input,STDIN_FILENO);
        }
        if(output_num == 1){
            int f_output = open(output_file,O_WRONLY|O_CREAT);
            dup2(f_output,STDOUT_FILENO);
        }
        char** cmd_tmp = (char**)calloc(sizeof(char*),MAX);
        for(int i = left; i < end_index; i++){
            cmd_tmp[i] = (char*)calloc(MAX,sizeof(char));
            strcpy(cmd_tmp[i],cmd[i]);
        }
        if(execvp(cmd_tmp[left],cmd_tmp+left) < 0){
            fprintf(stderr,"%s: command not found\n",cmd_tmp[left]);
            exit(1);
        }
    }
    else{
        int status;
        wait(&status);
        if(!WEXITSTATUS(status)) return true;
        return false;
    }
}
bool Run_external_pipe(int left, int right){
    if(left >= right){ perror("pipe"); return false; }
    int pipe_index = -1;
    for(int i = left; i < right; i++){
        if(!strcmp(cmd[i],"|")){
            pipe_index = i;
            break;
        }
    }
    if(pipe_index == -1) return Run_external_redirect(left,right);
    int fd[2];
    pipe(fd);
    if(fork() == 0){
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]); close(fd[1]);
        return Run_external_pipe(left,pipe_index);
    }
    else{
        int status;
        wait(&status);
        if(pipe_index < right){
            dup2(fd[0],STDIN_FILENO);
            close(fd[0]); close(fd[1]);
            return Run_external_pipe(pipe_index+1,right);
        }
    }
}
bool Run_external_and(int left, int right){
    if(left >= right){
        perror("and");
        return false;
    }
    int and_index = -1;
    for(int i = left; i < right; i++){
        if(!strcmp(cmd[i],"&&")){
            and_index = i;
            break;
        }
    }
    if(and_index == -1) return Run_external_pipe(left,right);
    if(fork() == 0){
        if(!Run_external_and(left,and_index)) exit(1);
    }
    else{
        int status;
        wait(&status);
        if(WEXITSTATUS(status)) return false;
        else return Run_external_and(and_index+1,right);
    }
}
void Run_external(){
    if(fork() == 0){
        if(IS_BACKGROUND) printf("\npid = %d\n",getpid());
        Run_external_and(0,cmd_count);
        exit(0);
    }
    else{
        if(IS_BACKGROUND) return;
        int status;
        wait(&status);
    }
}
void Run_command(){
    Analysis_command();
    if(IS_END) return;
    else if(IS_BUITIN) Run_builtin();
    else if(IS_EXTERNAL) Run_external();
}

/////////////////////////////////////////////////////////////////////////////////

void Init(){
    for(int i = 0; i < MAX; i++) strcpy(cmd[i],"\0");
    cmd_count = 0;
    IS_BUITIN = false,
    IS_EXTERNAL = false;
    IS_END = false;
}
