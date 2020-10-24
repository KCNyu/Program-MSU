/*================================================================
* Filename:test2_2.c
* Author: KCN_yu
* Createtime:Sat 24 Oct 2020 10:29:08 AM CST
================================================================*/
#include<sys/types.h>
#include<sys/stat.h>//
#include<fcntl.h>// mmap
#include<unistd.h>// open read write
#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>// uint32_t
#include<string.h>
#include <errno.h>// erron
#include<sys/mman.h>// mmap
#include<time.h>
#include<math.h>

int write_vek(char *file,uint32_t m)
{
    srand(time(NULL));
    int fd;
    fd = open(file,O_CREAT|O_RDWR|O_TRUNC,0600);
    if(fd == -1){
        fprintf(stderr,"Не смогли открыть файл  '%s' с матрицей: %s\n",file,
        strerror(errno));
        return 1;
    }
    write(fd,&m,sizeof(uint32_t));
    uint32_t i;
    for(i = 0; i < m; i++){
        double v[3];
        v[0]=rand()/((double)(RAND_MAX)/100);
        v[1]=rand()/((double)(RAND_MAX)/100);
        v[2]=rand()/((double)(RAND_MAX)/100);
        write(fd,&v[0],sizeof(double));
        write(fd,&v[1],sizeof(double));
        write(fd,&v[2],sizeof(double));
    }
    close(fd);
    return 0;
}

int main(int argc,char **argv)
{
    uint32_t m;
    m = atoi(argv[1]);
    if(write_vek(argv[2],m))
    {
       perror("write");
       return 1;
    }
    int fd = open(argv[2],O_RDWR);
    uint32_t count;
    read(fd,&count,sizeof(uint32_t));
    for(uint32_t i = 0; i < m; i++){
        double x, y, z;
        read(fd,&x,sizeof(double));
        read(fd,&y,sizeof(double));
        read(fd,&z,sizeof(double));
        printf("%9lf %9lf %9lf ",x,y,z);
        double mod = sqrt(x*x+y*y+z*z);
        printf("mod = %9lf\n",mod);
    }
    printf("====================================================\n");
    lseek(fd,sizeof(uint32_t),SEEK_SET);
    for(uint32_t i = 1; i < count; i++){
        for(uint32_t j = 0; j < count-i; j++){
            lseek(fd,sizeof(u_int32_t)+sizeof(double)*3*j,SEEK_SET);

            double x, y, z;
            read(fd,&x,sizeof(double));
            read(fd,&y,sizeof(double));
            read(fd,&z,sizeof(double));
            double mod = sqrt(x*x+y*y+z*z);
            double x_t, y_t, z_t;
            read(fd,&x_t,sizeof(double));
            read(fd,&y_t,sizeof(double));
            read(fd,&z_t,sizeof(double));
            double mod_t = sqrt(x_t*x_t+y_t*y_t+z_t*z_t);

            if(mod > mod_t){
                lseek(fd,sizeof(u_int32_t)+sizeof(double)*3*j,SEEK_SET);

                write(fd,&x_t,sizeof(double));
                write(fd,&y_t,sizeof(double));
                write(fd,&z_t,sizeof(double));

                write(fd,&x,sizeof(double));
                write(fd,&y,sizeof(double));
                write(fd,&z,sizeof(double));
            }
        }
    }
    lseek(fd,sizeof(uint32_t),SEEK_SET);
    for(uint32_t i = 0; i < m; i++){
        double x, y, z;
        read(fd,&x,sizeof(double));
        read(fd,&y,sizeof(double));
        read(fd,&z,sizeof(double));
        printf("%9lf %9lf %9lf ",x,y,z);
        double mod = sqrt(x*x+y*y+z*z);
        printf("mod = %9lf\n",mod);
    }
    close(fd);
    return 0;
}
