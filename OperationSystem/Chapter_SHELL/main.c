/*================================================================
* Filename:main.c
* Author: KCN_yu
* Createtime:Thu 05 Nov 2020 10:46:46 AM CST
================================================================*/
#include "shell.h"

int main(int argc, char *argv[])
{
    while(1){
        Print_prefix();
        Input_command();
        Run_command();
        Init();
    }
    return 0;
}
