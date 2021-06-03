/*================================================================
* Filename:Chown_matrix.c
* Author: KCN_yu
* Createtime:Mon 12 Oct 2020 07:28:31 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <error.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct passwd *pwd;
    struct group *gr;

    int f1 = open("mat1.txt",O_RDONLY);
    int f2 = open("mat2.txt",O_RDONLY);
    int fd = open("ans.txt",O_CREAT|O_RDWR);

    int m1, n1, m2, n2;
    read(f1, &m1, sizeof(int));
    read(f2, &m2, sizeof(int));
    if(m1 != m2) perror("row");
    read(f1, &n1, sizeof(int));
    read(f2, &n2, sizeof(int));
    if(n1 != n2) perror("col");

    write(fd, &m1, sizeof(int));
    write(fd, &n1, sizeof(int));
    for(int i = 0;  i < m1; i++){
        for(int j = 0; j < n1; j++){
            int num1, num2;
            read(f1,&num1,sizeof(int));
            read(f1,&num2,sizeof(int));
            num1 += num2;
            write(fd,&num1,sizeof(int));
        }
    }
    close(f1);
    close(f2);
    close(fd);

    int ret;

    gr = getgrnam("test_gr");
    if(!gr) return 1;
    ret = chown("ans.txt", -1, gr->gr_gid);
    if(ret) perror("chown");
    return 0;
}
