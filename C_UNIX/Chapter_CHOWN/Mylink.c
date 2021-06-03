/*================================================================
* Filename:Mylink.c
* Author: KCN_yu
* Createtime:Tue 13 Oct 2020 01:37:53 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>

int main(int argc, char* argv[]) 
{
  if(link(argv[1], argv[2]) == -1){
    perror("link");
  }
  return 0;
}