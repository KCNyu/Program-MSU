#include<stdio.h>
#include<string.h>
#define MAX_LEN 200
char str1[MAX_LEN+10];
char str2[MAX_LEN+10];
int num1[MAX_LEN+10];
int num2[MAX_LEN+10];
int ans[MAX_LEN+10]; 
//每次除就是做一次减法,看能减被除数的最高倍几次 
//str1.len < str2.len  0
//
int subtract(int *num1,int *num2,int len1,int len2){
	//len1<len2 -1
	if(len1<len2)
		return -1;
	if(len1 == len2){
		//相等长度,比较最高位 
		for(int i=len1-1;i>=0;i--){
			if(num1[i]>num2[i])
				break;
			if(num1[i]<num2[i])
				return -1;
			//num1[i]==num2[i] 找下一位,所以需要循环 
				
		}
	}
	//相减 
	for(int i=0;i<len1;i++){
		num1[i]-=num2[i];
		if(num1[i]<0){
			num1[i]+=10;
			num1[i+1]--;		
		}
	}
	//计算新的长度 
	for(int i=len1-1;i>=0;i--){
		if(num1[i]!=0){
			return i+1;
		}
	}
	return 0;//相等 
}


int main(){
	scanf("%s%s",str1,str2);
	int i,j,len1,len2;
	int di_len; 
	len1 = strlen(str1);
	len2 = strlen(str2);
	
	memset(num1,0,sizeof(num1));
	memset(num2,0,sizeof(num2));
	memset(ans,0,sizeof(ans));
	
	//倒放字符到INT数组 
	j=0;
	for(int i=len1-1;i>=0;i--)
		num1[j++]=str1[i]-'0';
	j=0;
	for(int i=len2-1;i>=0;i--)
		num2[j++]=str2[i]-'0';
	
	di_len = len1 - len2;
	if(di_len<0)
	{
			printf("0\n");
			return 0;
	} 
	//扩充除数
	for(int i=len1-1;i>=0;i--){
		if(i>=di_len)
			num2[i]=num2[i-di_len];
		else
			num2[i]=0;
	}	
	len2=len1;
	//从最高倍,开始做循环
	//0 代表,最高倍数,1代表减少10倍(num2从i 开始) 
	for(int i=0;i<=di_len;i++){
		int count; 
		//开始相减,统计减了几次 
		while((count=subtract(num1,num2+i,len1,len2-i))>=0){
			ans[di_len-i]++;
			len1=count;
		}
	}
		
	//输出结果
	int flag =0;
	for(int i=len2;i>=0;i--){
		if(flag==1)
			printf("%d",ans[i]);
		else if(ans[i]!=0)
		{
			printf("%d",ans[i]);
			flag=1;
		}
	} 
	
	return 0;
} 

