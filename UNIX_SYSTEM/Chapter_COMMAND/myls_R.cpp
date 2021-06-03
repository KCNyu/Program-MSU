/*================================================================
* Filename:myls.cpp
* Author: KCN_yu
* Createtime:Sun 23 May 2021 12:56:24 AM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>

#define PATH_LEN 512

using namespace std;
void fetchDir(const char* dir);
void lsFile(const char* name);

void lsFile(const char* name){
    struct stat sbuf;
    if(lstat(name,&sbuf) == -1){
        cerr << "invalid filename/dirname" << endl;
        return;
    }
    if((sbuf.st_mode & S_IFMT) == S_IFDIR){
        fetchDir(name);
    }
    cout.width(6);
    cout << sbuf.st_size << " "  << name << endl;
}
void fetchDir(const char* dir){
    char path[PATH_LEN];
    struct dirent *sdp;
    DIR *dp;

    if((dp = opendir(dir)) == NULL){
        cerr << "can't open " << dir << endl;
        return;
    }
    while((sdp = readdir(dp)) != NULL){
        if(strcmp(sdp->d_name,".") == 0 || strcmp(sdp->d_name, "..") == 0){
            continue;
        }
        if(strlen(dir)+strlen(sdp->d_name)+2 > sizeof(path)){
            cerr << "name " << dir << sdp->d_name << " too long" << endl;
        }
        else{
            //cout << "dir: " << dir << endl;
            //cout << "sdp->d_name: " << sdp->d_name << endl;
            sprintf(path, "%s/%s", dir ,sdp->d_name);
            lsFile(path);
        }
    }
    closedir(dp);
}
int main(int argc, char *argv[])
{
    if(argc == 1){
        lsFile(".");
    }
    else{
        argv++;
        while(argc-- > 1){
            lsFile(*argv++);
        }
    }
    // this program has bug which is  doesn't need to '/' in the end of input
    return 0;
}
