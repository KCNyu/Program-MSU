#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
void ReWriteRand (char *name, unsigned long int n) {
    FILE *fp = fopen(name, "w");
    unsigned long int i;
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        int r[1];
        r[0]=rand()%100;
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
_Bool CompRaw(FILE *fp, unsigned long int p1, unsigned long int p2) {
    return ReadRaw(fp,p1) <= ReadRaw(fp,p2);
}
void InsertSort(int *A){
    int i,j,tmp;
    for(i = 0; i < 4; i++){
        tmp = A[i];
        for(j = i-1; j >= 0; j--){
            if(A[j] > tmp){
                A[j+1] = A[j];
                A[j] = tmp;
            }
        }
    }
}
void Partsort(FILE *fp, unsigned long int n){
    int A[4];
    for(int i = 0; i < n/4; i++){
        fread(A,sizeof(int),4,fp);
        InsertSort(A);
        fseek(fp,-4*sizeof(int),SEEK_CUR);
        fwrite(A,sizeof(int),4,fp);
    }
    for(int i = 0; i < 4; i++)
        printf("%d ",A[i]);
}
void MergesortRaw(FILE *fp, unsigned long int n){
    for(unsigned long int i = 4; i < n; i <<= 1){
        for(unsigned long int j = 0; j < n/i; j += 2){
            int *temp = (int*)malloc(sizeof(int)*i*2);
            unsigned long int a = i*j;
            unsigned long int b = i*(j+1);
            for(unsigned long int k = 0; k < 2*i; k++){
                if(a < (j+1)*i && b == (j+2)*i)
                    temp[k] = ReadRaw(fp,a++);
                if(a == (j+1)*i && b < (j+2)*i)
                    temp[k] = ReadRaw(fp,b++);
                if(a < (j+1)*i && b < (j+2)*i)
                    temp[k] = CompRaw(fp,a,b) ? ReadRaw(fp,a++) : ReadRaw(fp,b++);
            }
            fseek(fp,sizeof(int)*i*j,SEEK_SET);
            fwrite(temp,sizeof(int),i*2,fp);
            free(temp);
        }
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
    Partsort(fp,n);
    MergesortRaw(fp,n);
    fclose(fp);
    
    clock_t endtime = clock();
    printf("Running time:%ldms\n",(endtime-begintime));
    return 0;
}
   
