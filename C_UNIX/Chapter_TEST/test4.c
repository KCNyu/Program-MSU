/*================================================================
* Filename:test4.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 06:55:42 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    struct stat sb;
    stat(argv[1],&sb);
    int mode = sb.st_mode;
    int mode_u = 0;
    int mode_g = 0;
    int mode_o = 0;
    if((mode&S_IRUSR) == S_IRUSR) mode_u += 4;
    if((mode&S_IWRITE) == S_IWRITE) mode_u += 2;
    if((mode&S_IEXEC) == S_IEXEC) mode_u += 1;

    if((mode&S_IRGRP) == S_IRGRP) mode_g += 4;
    if((mode&S_IWGRP) == S_IWGRP) mode_g += 2;
    if((mode&S_IXGRP) == S_IXGRP) mode_g += 1;

    if((mode&S_IROTH) == S_IROTH) mode_o += 4;
    if((mode&S_IWOTH) == S_IWOTH) mode_o += 2;
    if((mode&S_IXOTH) == S_IXOTH) mode_o += 1;

    printf("%d%d%d\n",mode_u,mode_g,mode_o);
    if(mode_u < 4) mode_u += 4;
    if(mode_g < 4) mode_g += 4;
    if(mode_o < 4) mode_o += 4;

    int mod = mode_u*8*8 + mode_g*8 + mode_o;
   chmod(argv[1],mod);
    return 0;
}
