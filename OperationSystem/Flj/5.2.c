#include <stdio.h>
#include<stdlib.h> 
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

 void error(char * str, char*filename){	
	 printf(str,filename); exit(-1); 
 }
 int main(int argc,char *argv[]) { 
	int f1,f2,n;  
	int block = argv[1][0] - '0';
	char buf[block];


	f1 = open(argv[2], O_RDONLY);

	 
	char ch; int total = 0;
	while ((n = read(f1, &ch, 1)) > 0) total++;
	
	int file2_i = 0;
	while ((n = read(f1, buf, total/block)) > 0){
		f2 = open(&argv[3][file2_i++], O_CREAT|O_WRONLY|O_TRUNC);
		if (write(f2, buf, n ) != n) 
	        	exit(-1);
	}
	if (n<0) printf("error read from file");
	
	close( f1); close(f2); 
	
	return 0; 
}
