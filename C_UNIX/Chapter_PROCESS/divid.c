/*================================================================
* Filename:mydivid.c
* Author: KCN_yu
* Createtime:Mon 21 Dec 2020 11:01:42 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>
#include <sys/prctl.h>

#define MAX 100000000
#define N 10
#define AVE (MAX/N)
double *res = NULL;
int fd[2];
double fabs(double x){
    if(x >= 0) return x;
    else return -x;
}
double mydivid(double x){
    double x0 = 1e-10;
    double x1;
    double tmp;
    do{
        x1 = x0*(2-x*x0);
        //printf("x1  = %0.20lf\n",x1);
        tmp = x0;
        //printf("tmp = %0.20lf\n",tmp);
        x0 = x1;
        //printf("x0  = %0.20lf\n",x0);
    }while(fabs(x1-tmp) >= 1e-15);
    return x1;
}
double sum(int x){
    double res = 0;
    for(int i = 1; i <= x; i++){
        double num = 1/((double)i);
        res += num;
        //printf("num = %0.20f\n",num);
    }
    return res;
}
double mysum(int x){
    double res = 0;
    for(int i = 1; i <= x; i++){
        double num = mydivid((double)i);
        res += num;
        //printf("num = %0.20f\n",num);
    }
    return res;
}
void* sum_work(void* arg){
    intptr_t n = (intptr_t)arg;
    long long start = n*AVE+1;
    long long end = start + AVE -1;
    long long i;
    res[n] = 0;

    for(i = start; i <= end; i++){
        res[n] += mydivid((double)i);
    }
    pthread_exit(0);
}
double sum1(int x){
    double res = 0;
    for(int i = 1; i <= x>>2; i++){
        double num = mydivid((double)i);
        res += num;
    }
    return res;
}
double sum2(int x){
    double res = 0;
    for(int i = (x>>2)+1; i <= x>>1; i++){
        double num = mydivid((double)i);
        res += num;
    }
    return res;
}
double sum3(int x){
    double res = 0;
    for(int i = (x>>1)+1; i <= (x>>1)+(x>>2); i++){
        double num = mydivid((double)i);
        res += num;
    }
    return res;
}
double sum4(int x){
    double res = 0;
    for(int i = (x>>1)+(x>>2)+1; i <= x; i++){
        double num = mydivid((double)i);
        res += num;
    }
    return res;
}
double res1 = 0,res2 = 0,res3 = 0, res4 = 0;
double sum5(int x){
    pipe(fd);
    if(fork() == 0){
        res1 = sum1(x);
        write(fd[1],&res1,sizeof(double));
        exit(0);
    }
    else{
        res2 = sum2(x);
        read(fd[0],&res1,sizeof(double));
    }
    if(fork() == 0){
        res3 = sum3(x);
        write(fd[1],&res3,sizeof(double));
        exit(0);
    }
    else{
        res4 = sum4(x);
        read(fd[0],&res3,sizeof(double));
    }
    return res1+res2+res3+res4;
}
int main(int argc, char *argv[])
{
    pthread_t *pthread_id = NULL;
    pthread_id = (pthread_t*)malloc(N*sizeof(pthread_t));
    res = (double*)malloc(N*sizeof(double));
    double result = 0;
    intptr_t i;
    clock_t start, end;
    /*
    double x1 = 0.00295857988165680423; // x1 = 1/338;
    double x2 = x1*(2-x1*338);
    printf("%0.20f\n",x2);
    double x3 = x2*(2-x2*338);
    printf("%0.20f\n",x3);
    double x4 = x3*(2-x3*338);
    printf("%0.20f\n",x4);
    if(x4 == x2) printf("right\n");
    printf("%0.20f\n",mydivid(338));
    */
    start = clock();
    printf("%0.20f\n",  sum(MAX));
    end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf( "sum = %f seconds\n", duration );


    start = clock();
    printf("%0.20f\n",  mysum(MAX));
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf( "mysum = %f seconds\n", duration );



    start = clock();
    for(i = 0; i < N; i++){
        pthread_create(pthread_id+i,NULL,sum_work,(void*)i);
    }
    for(i = 0; i < N; i++){
        pthread_join(pthread_id[i],NULL);
        result += res[i];
    }
    printf( "%0.20f\n",result);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf( "sum_work = %f seconds\n",duration);
    free(pthread_id);
    free(res);

    start = clock();
    printf("%0.20f\n",sum5(MAX));
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf( "sum5 = %f seconds\n", duration );

    return 0;
}
