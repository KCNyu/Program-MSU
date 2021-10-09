//A23EF4S->A2233EF44S （单个字符的读写）
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
void err_sys(const char* info)
{
	perror(info);
	exit(1);
}
int main(int argc, char** argv)
{

	if (argc != 2)
	{
		printf("Usage: changefile <filename>");
		return 1;
	}
	char s[300];
	int f1 = open(argv[1], O_RDONLY);
	if (f1 == -1)
		err_sys(argv[1]);
	struct stat statbuf;
	if (stat(argv[1], &statbuf) != 0)
		err_sys(argv[1]);
	char* tmpfilename = "tmpfile.tmp";
	int f2 = open(tmpfilename, O_WRONLY | O_CREAT | O_TRUNC,
		statbuf.st_mode);
	if (f2 == -1)
		err_sys(tmpfilename);
	size_t sz = statbuf.st_size; //or:sz = lseek(f1, 0, SEEK_END)
	printf("sz = %ld\n", sz);
	char c;
	for (off_t i = 0; i < sz ; i++)
	{
		lseek(f1, i, SEEK_SET);
		read(f1, &c, 1);
		write(f2, &c, 1);
		putchar(c);
		*s = c;
		if (*s >= '0' && *s <= '9')//数字的取值范围
		{
			write(f2, &c, 1);
			putchar(c);
		}
	}
	close(f1);
	close(f2);
	rename(tmpfilename, argv[1]);
	printf("\nOK");
	return 0;
}