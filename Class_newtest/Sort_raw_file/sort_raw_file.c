#include <stdio.h>
#include <stdlib.h>
/* Функция презаписывает файл name n числами типа int в двоичном виде;
   перед вызовом файл должен быть закрыт */
void ReWriteRand (char *name, unsigned long int n) {
    FILE *fp=fopen(name, "wb");
    unsigned long int i;
    for (i=0; i<n; i++) {
        int r[1];
        r[0]=rand();
        fwrite(r, sizeof(int), 1, fp);
    }
    fclose(fp);
}

/* Функция сравнивает p1-е и p2-е числа (в представлении int) бинарного файла *fp;
   перед вызовом файл должен быть открыт на чтение */
int CompRaw(FILE *fp, unsigned long int p1, unsigned long int p2) {
    int tmp1, tmp2, r[1];
    fseek(fp, p1*sizeof(int), SEEK_SET);
    fread(r, sizeof(int), 1, fp);
    tmp1=r[0];
    fseek(fp, p2*sizeof(int), SEEK_SET);
    fread(r, sizeof(int), 1, fp);
    tmp2=r[0];
    return tmp1-tmp2;
}

/* Функция меняет местами p1-е и p2-е числа (в представлении int) бинарного файла *fp;
   перед вызовом файл должен быть открыт на чтение и запись */
void ExchRaw(FILE *fp, unsigned long int p1, unsigned long int p2) {
    int tmp, r[1];
    fseek(fp, p1*sizeof(int), SEEK_SET);
    fread(r, sizeof(int), 1, fp);
    tmp=r[0];
    fseek(fp, p2*sizeof(int), SEEK_SET);
    fread(r, sizeof(int), 1, fp);
    fseek(fp, p1*sizeof(int), SEEK_SET);
    fwrite(r, sizeof(int), 1, fp);
    fseek(fp, p2*sizeof(int), SEEK_SET);
    r[0]=tmp;
    fwrite(r, sizeof(int), 1, fp);
}

/* Функция сортирует по возрастанию первые n чисел (в представлении int) бинарного файла *fp;
   перед вызовом файл должен быть открыт на чтение и запись */
void SortRaw(FILE *fp, unsigned long int n) {
    unsigned long int i,j;
    for (i=0; i<n-1; i++)
        for (j=0; j<n-1-i; j++)
            if (CompRaw(fp, j, j+1)>0)
                ExchRaw(fp, j, j+1);
}

int main(int argc, char **argv) {
    FILE *fp;
    unsigned long int n=1024;
    if (argc>1)
        n=atol(argv[1]);
    ReWriteRand("RandArr.bin", n);
    
    fp=fopen("RandArr.bin", "r+b");
    SortRaw(fp,n);
    fclose(fp);
    return 0;
}
    
