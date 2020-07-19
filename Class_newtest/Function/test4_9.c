/*************************************************************************
	> File Name: test4.c
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 09:10:52 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int N = 10;
void InputArr(int *Arr){
    int i,r;
    for(i = 0; i < N; i++){
        r = rand()%100;
        if(r == 0)
            i--;
        else
            Arr[i] = r;
    }
}
void PrintArr(int *Arr){
    int i;
    for(i = 0; i < N; i++)
        printf("%d ",Arr[i]);
    printf("\n");
}
int SearchMax(int *Arr){
    int i,max = Arr[0],max_index = 0;
    for(i = 1; i < N; i++){
        if(Arr[i] > max){
            max = Arr[i];
            max_index = i;
        }
    }
    return max_index;
}
int SearchMin(int *Arr){
    int i,min = Arr[0],min_index = 0;
    for(i = 1; i < N; i++){
        if(Arr[i] < min){
            min = Arr[i];
            min_index = i;
        }
    }
    return min_index;
}
void Shift(int *Arr,int t){
    int i;
    for(i = t; i < N-1; i++){
        Arr[i] = Arr[i+1];
    }
    N--;
}
void DeleteAll(int *Arr, int x){
    int i;
    for(i = 0; i < N; i++){
        if(Arr[i] == x){
            Shift(Arr,i);
            i--;
        }
    }
}
void Delete(int *Arr,int x){
    int i;
    for(i = 0; i < N; i++){
        if(Arr[i] == x){
            Shift(Arr,i);
            break;
        }
    }
}
void Shift_m(int *Arr, int m){
    int i,temp;
    while(m != 0){
        temp = Arr[N-1];
        for(i = N-1; i > 0; i--){
            Arr[i] = Arr[i-1];
        }
        Arr[0] = temp;
        m--;
    }
}
void Reverse(int *Arr, int from, int to){
    int i,temp;
    for(i = 0; i < (to-from+1)/2; i++){
        temp = Arr[from+i];
        Arr[from+i] = Arr[to-i];
        Arr[to-i] = temp;
    }
}
void Converse(int *Arr, int n, int m){
    Reverse(Arr,0,N-m-1);
    Reverse(Arr,N-m,n-1);
    Reverse(Arr,0,n-1);
}
int Judge_alternate(int *Arr){
    int i,flag = 1;
    for(i = 0; i < N-1; i++){
        if(Arr[i] * Arr[i+1] >= 0){
            flag = 0;
            break;
        }
    }
    int p;
    if(flag == 1)
        p = 0;
    else
        p = 1;
    for(i = 0; i < N; i++){
        if(flag == 1 && Arr[i] > 0){
            p += Arr[i];
        }
        if(flag == 0 && Arr[i] < 0){
            p *= Arr[i];
        }
    }
    return p;
}
void Only(int *Arr){
    int i,j;
    for(i = 0; i < N-1; i++){
        if(Arr[i] == Arr[i+1]){
            Shift(Arr,i);
            i--;
        }
    }
}
void Only1(int *Arr, int x){
    int i;
    for(i = 0; i < N-1; i++){
        if(Arr[i] == x && Arr[i+1] == x){
                Shift(Arr,i);
                i--;
        }
    }
}
int main()
{
    int Arr[N];
    srand(time(NULL));
    InputArr(Arr);
    PrintArr(Arr);
  
    int x;
    scanf("%d",&x);
    Converse(Arr,N,x);
    PrintArr(Arr);


/*
    int p = Judge_alternate(Arr);
    printf("p = %d\n",p);

    int x;
    scanf("%d",&x);
    Only1(Arr,x);
    Only(Arr);
    PrintArr(Arr);
*/
    return 0;
}
