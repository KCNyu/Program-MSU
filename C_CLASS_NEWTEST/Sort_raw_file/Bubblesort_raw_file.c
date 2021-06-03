#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void ReWriteRand (char *name, unsigned long int n) {
    FILE *fp = fopen(name, "w");
    unsigned long int i;
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        int r[1];
        r[0]=rand();
        fwrite(r, sizeof(int), 1, fp);
    }
    fclose(fp);
}
int ReadRaw(FILE *fp, unsigned long int position){
    int r[1],i;
    fseek(fp, position*sizeof(int), SEEK_SET);
    fread(r, sizeof(int), 1, fp);
    return r[0];
}
void WriteRaw(FILE *fp, unsigned long int position, int value){
    int r[1];
    r[0] = value;
    fseek(fp, position*sizeof(int), SEEK_SET);
    fwrite(r,sizeof(int),1,fp);
}
int CompRaw(FILE *fp, unsigned long int p1, unsigned long int p2) {
    return ReadRaw(fp,p1) - ReadRaw(fp,p2);
}
void ExchRaw(FILE *fp, unsigned long int p1, unsigned long int p2) {
    int tmp;
    tmp = ReadRaw(fp,p1);
    WriteRaw(fp,p1,ReadRaw(fp,p2));
    WriteRaw(fp,p2,tmp); 
}
void BubblesortRaw(FILE *fp, unsigned long int n) {
    unsigned long int i,j;
    for (i=0; i<n-1; i++)
        for (j=0; j<n-1-i; j++)
            if (CompRaw(fp, j, j+1)>0)
                ExchRaw(fp, j, j+1);
}
int main(int argc, char *argv[])
{
    clock_t begintime = clock();

    FILE *fp;
    unsigned long int n = 1024;
    if (argc>1)
        n=atol(argv[1]);
    ReWriteRand("myfile",n);
    
    fp=fopen("myfile","r+");
    BubblesortRaw(fp,n);
    fclose(fp);
    
    clock_t endtime = clock();
    printf("Runing time;%ldms\n",endtime-begintime);
    return 0;
}
   
