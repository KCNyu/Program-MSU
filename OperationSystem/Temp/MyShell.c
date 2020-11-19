#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdbool.h>
#include <fcntl.h>
#define Size 128

char commands[Size][Size];

int analyse_commands(char command[Size]);
void Do_command(int num);
void for_pipe(int left, int right);
void for_redi(int left, int right);
void for_andand(int left, int right);

int main() {
	char buf[Size],username[20],hostname[20],path[64];
	while(1){
		struct passwd* pwd=getpwuid(getuid());
		strcpy(username,pwd->pw_name);
		gethostname(hostname,20);
		getcwd(path,64);
		printf("MyShell_%s_%s_%s$",username,hostname,path);
		
		fgets(buf,Size,stdin);
		int len=strlen(buf);
		if (len!=Size) buf[len-1]='\0';
		
		int num=analyse_commands(buf);
		if (num!=0) {
			if (strcmp(commands[0],"exit") == 0) exit(0);
		       	else if (strcmp(commands[0],"cd") == 0) chdir(commands[1]);
			else Do_command(num);
		}
	}
}

int analyse_commands(char buf[Size]) {
	int num=0,row=0,col=0;
	int len=strlen(buf);
	for (; row<len; row++){
		if (buf[row]!= ' ') commands[num][col++]=buf[row];
		else{
			if (col!=0) {
				commands[num++][col]='\0';
				col=0;
			}
		}
	}
	if(col!=0) commands[num++][col]='\0';
	return num;
}

void Do_command(int num) {
	if(fork()){
		int status;
		wait(&status);
	}else{
		int infd=dup(0);
		int outfd=dup(1);
		for_andand(0,num);
		dup2(infd,0);
		dup2(outfd,1);
		exit(0);
	}
}

void for_pipe(int left, int right) {
	int flagpipe=-1;
	for (int i=left; i<right; ++i) {
		if (strcmp(commands[i], "|") == 0) {
			flagpipe = i;
			break;
		}
	}
	if (flagpipe == -1) {
		for_redi(left, right);
		return;
	} else if (flagpipe+1 == right) return;
	int fd[2];
	if (pipe(fd) == -1) return;
	if (fork()){
		int status;
		wait(&status);
		if (flagpipe+1 < right){
			close(fd[1]);
			dup2(fd[0], 0); 
			close(fd[0]);
			for_pipe(flagpipe+1, right);
		}else return;
	}else{
		close(fd[0]);
		dup2(fd[1], 1); 
		close(fd[1]);
		for_redi(left, flagpipe);
		exit(0);
	}
	return;
}

void for_redi(int left, int right) { 
	int flagin=0, flagout=0, flagoo=0, flagmv=0, flagback=0, flagMV=0, idxMV=0;
	char *filein=NULL, *fileout=NULL, *fileoo=NULL;
	int end=right;
	for (int i=left; i<right; ++i) {
		if (strcmp(commands[i],"<")==0){
			flagin++;
			if(i+1<right) filein=commands[i+1];
			if(end==right) end=i;
		} else if(strcmp(commands[i],">")==0){
			flagout++;
			if(i+1<right) fileout=commands[i+1];		
			if(end==right) end=i;
		} else if(strcmp(commands[i],">>")==0){
			flagoo++;
			if(i+1<right) fileoo=commands[i+1];	
			if(end==right) end=i;
		} else if(strcmp(commands[i],"&")==0){
				if(i==right-1){ 
					flagback++;
					if(flagin||flagout||flagoo==0)
						end--;
				}
		} else if(strcmp(commands[i],"MV")==0){
			flagMV++;
			idxMV=i;
		}
	}
	int fdpid[2];
	pipe(fdpid);
	if (fork()){
		if(flagback==1){
			int cpid;
			read(fdpid[0],&cpid,sizeof(cpid));
			printf("pid: %d  cpid: %d \n", getpid(), cpid);
			return;
		}
		int status;
		wait(&status);
	}else{
		if(flagin==1){
			int fin=open(filein,O_RDONLY);
			dup2(fin,STDIN_FILENO);
		}
		if(flagout==1){
			remove(fileout);
			int fout=open(fileout,O_WRONLY|O_CREAT,0744);
			dup2(fout,STDOUT_FILENO);
		}
		if(flagoo==1){
			int foo=open(fileoo,O_WRONLY|O_CREAT|O_APPEND,0744);
			dup2(foo,STDOUT_FILENO);
		}
		if(flagMV==1){
			char temp;
			int fold=open(commands[idxMV+1],O_RDONLY);
			int fnew=open(commands[idxMV+2],O_CREAT|O_WRONLY,0744);
			while(read(fold,&temp,sizeof(temp))>0)
				write(fnew,&temp,sizeof(temp));
			close(fold); close(fnew);
			remove(commands[idxMV+1]);
			exit(0);
		}
		int cpidtmp=getpid();
		write(fdpid[1],&cpidtmp,sizeof(cpidtmp));
		char* tcomm[Size];
		for (int idx=0; idx<end-left; idx++) tcomm[idx]=commands[idx+left];
		tcomm[end-left]=NULL;
		execvp(tcomm[0], tcomm);
		exit(0);
	}
	return;
}

void for_andand(int left, int right){
	int flag=-1;
	for(int i=left; i<right; i++) {
		if(strcmp(commands[i],"&&")==0){
			flag=i;
			break;
		}
	}
	if(flag==-1){
		for_pipe(left, right);
		return;
	}else if(flag+1==right) return;
	else{
		for_andand(left,flag);
		for_andand(flag+1,right);
	}
}
