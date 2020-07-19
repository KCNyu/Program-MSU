#include <stdio.h>

#define URL "www.baidu.com"
#define NAME "搜索引擎"
#define BOSS "李彦宏"
#define YEAR 2008
#define MONTH 5
#define DAY 20

int main()
{
	printf("%s成立于%d年%d月%d日\n",NAME,YEAR,MONTH,DAY);
	printf("%s是%s创立的\n",NAME,BOSS);
	printf("%s的域名是%s\n",NAME,URL);
	return 0;

}


