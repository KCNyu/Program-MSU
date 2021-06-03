#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}
void WriteArray(int A[], char fName[], int MAX)
{
	int i;
	FILE *f;
	srand(time(NULL));
	f = fopen(fName,"w");
	for(i = 0; i < MAX; i++)
	{	
		A[i] = randomInt(100);
		fprintf(f,"%d ",A[i]);
	}
	fclose(f);
	return;
}
int ReadArray(int A[], char fName[], int MAX)
{
	int N = 0, k;
	FILE *f;
	f = fopen(fName,"r");
	while(1)
	{
		k = fscanf(f, "%d",&A[N]);
		if (k != 1)
			break;
		N++;
		if (k >= MAX)
			break;
	}
	fclose(f);
	return N;
}
void startingdigit(int A[],int length)
{
	int i,j,tmp;
	for(i = 0; i < length-1; i++)
	{
		for(j = 0; j < length-i-1; j++)
		{
			if(A[j]%10 > A[j+1]%10)
			{
				tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
		}
	}
	return;
}
void endingdigit(int A[],int length)
{
	int i,j,tmp;
	for(i = 0; i < length-1; i++)
	{
		for(j = 0; j < length-i-1; j++)
		{
			if(A[j]%10 < A[j+1]%10)
			{
				tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}			
			if ((A[j]%10) == (A[j+1])%10)
			{
				if (((A[j]/10)%10) < ((A[j+1]/10)%10))
				{
					tmp = A[j];
					A[j] = A[j+1];
					A[j+1] = tmp;
				}
			}	
		}
	}
	return;
}
int sumdigits(int n)
{
	int i,sum = 0;
	while(n != 0)
	{
		sum += n%10;
		n /= 10;
	}
	return sum;
}
void set_sumdigits(int A[],int length)
{
	int i,j,tmp;
	for(i = 0; i < length-1; i++)
	{
		for(j = 0; j < length-i-1; j++)
		{
			if(sumdigits(A[j]) > sumdigits(A[j+1]))
			{
				tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
		}
	}
	return;
}
void putArrayfile(int A[],char fName[],int MAX)
{
	int N = 0,k;
	FILE *f;
	f = fopen (fName,"w");
	for(k = 0; k < MAX; k++)
		fprintf(f,"%d ",A[k]);
	fclose(f);
	return;
}
void even_uneven(int A[],int length)
{
	int i,new[length],count = 0;
	for(i = 0; i < length; i++)
	{
		if(A[i]%2 == 0)
		{
			new[count] = A[i];
			count++;
		}
	}
	for(i = 0; i < length; i++)
	{
		if(A[i]%2 != 0)
		{
			new[count] = A[i];
			count++;
		}
	}
	putArrayfile(new,"output/output_test129.txt",count);
	return;
}
#define N 100
int main()
{
	FILE *f;
	int a[N],i;
	WriteArray(a,"input/input_test129.txt",N);
	startingdigit(a,N);
//	set_sumdigits(a,N);
//	even_uneven(a,N);
	return 0;
}
