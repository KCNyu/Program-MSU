#include <stdio.h>
/*int main()
{
	int a;
	scanf("%d",&a);
	switch(a)
	{
		case 1:printf("Monday\n");break;
		case 2:printf("Tuesday\n");break;
		case 3:printf("Wednesday\n");break;
		case 4:printf("Thursday\n");break;
		case 5:printf("Friday\n");break;
		case 6:printf("Saturday\n");break;
		case 7:printf("Sunday\n");break;
		default:printf("Erro!\n");
	}
	return 0;
}*/

int main()
{
	int n1,n2,n3,number,n;
	for(number = 11; number <= 999; number++)
	{
		n1 = number/100;
		n2 = (number/10)%10;
		n3 = number % 10;
//		if((n1 == n2 || n1 == n3 || n2 == n3) && !(n1 == n2 && n1 == n3))
//		if(n1 != n2 && n1 != n3 && n2 != n3)
		if(n1 == n3 && number >= 100 || n3 == n2 && number < 100)
		{
			n++;
			printf("%d ",number);
		}
	}
	printf("\n%d\n",n);
	return 0;
/*	
	do
	{
		scanf("%d",&n);
		length++;
	}while(n != 0);
	printf("length = %d\n",length-1);

	scanf("%d",&n);
	while (n != 0)
	{
		length++;
		scanf("%d",&n);
	}
	printf("length = %d\n",length);

	scanf("%d",&n);
	for(length = 0; n != 0; length++)
	{
		scanf("%d",&n);
	}
	printf("length = %d\n",length);

	int i,sum;
	for(i = 0,sum = 0;i <= 100;sum += i++);
	printf("%d\n",sum);
	return 0;
*/	
}
		
