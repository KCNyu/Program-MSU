/*================================================================
* Filename:Myls.cpp
* Author: KCN_yu
* Createtime:Thu 17 Sep 2020 08:55:21 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    char s[100];
    string res[1000];
    DIR *dir;
    struct dirent *rent;
    if(argv[1]) dir = opendir(argv[1]);
    else dir = opendir(".");
    int count = 0;
    while(rent = readdir(dir)){
        strcpy(s,rent->d_name);
        if(s[0] != '.' && s) res[count++] = s;
    }
    for(int i = 0; i< count; i++) cout << res[i] << " ";
    cout << endl;
    closedir(dir);
    return 0;
}

