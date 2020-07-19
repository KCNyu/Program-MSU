#include <stdio.h>
int main()
{
	FILE *f;
	int x,n,count = 0,sum = 0;
	f = fopen("input/input_test128.txt","r");
	if(f == NULL)
	{
		printf("can't find file\n");
		return 0;
	}
	do	
	{
		n = fscanf(f, "%d",&x);
		if (n != 1)
			break;
		sum+=x;
		count++;
	}while(n == 1);
	fclose(f);
	f = fopen("output/output_test128.txt","w");
	fprintf(f,"Average = %f\n",(float)sum/count);
	fclose(f);
	return 0;
}
