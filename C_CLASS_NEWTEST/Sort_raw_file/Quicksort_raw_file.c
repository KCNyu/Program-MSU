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
void QuicksortRaw(FILE *fp, long int left, long int right){
    if(left < right){
        int i = left, j = right, temp = ReadRaw(fp,left);
        while(i < j){
            while(i < j && ReadRaw(fp,j) >= temp)
                j--;
            if(i < j)
                WriteRaw(fp,i++,ReadRaw(fp,j));
            while(i < j && ReadRaw(fp,i) < temp)
                i++;
            if(i < j)
                WriteRaw(fp,j--,ReadRaw(fp,i));
        }
        WriteRaw(fp,i,temp);
        QuicksortRaw(fp,left,i-1);
        QuicksortRaw(fp,i+1,right);
    }
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
    QuicksortRaw(fp,0,n-1);
    fclose(fp);

    clock_t endtime = clock();
    printf("Runing time:%ldms\n",endtime-begintime);
    return 0;
}

