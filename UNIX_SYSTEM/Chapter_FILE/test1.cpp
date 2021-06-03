/*================================================================
* Filename:test1.cpp
* Author: KCN_yu
* Createtime:Tue 18 May 2021 12:43:55 AM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <dirent.h>
using namespace std;

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;
    if(argc != 2){
        cerr << "usage: ls directory_name" << endl;
    }
    if((dp = opendir(argv[1])) == nullptr){
        cerr << "can't open " << argv[1] << endl;
    }
    while((dirp = readdir(dp)) != nullptr){
        cout << dirp->d_name << endl;
    }
    closedir(dp);
    return 0;
}

