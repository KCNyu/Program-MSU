#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <ctype.h>

void err_sys(const char* info)
{
	perror(info);
	exit(1);
}

char testfilename[100];
char* controlfilename = "control.dat";

int filecompare(char* name1, char* name2)
{
	int f1 = open(name1, O_RDONLY);
	int f2 = open(name2, O_RDONLY);
	char buf1[100];
	char buf2[100];
	int n1 = read(f1, buf1, sizeof(buf1));
	int n2 = read(f2, buf2, sizeof(buf2));
	close(f1);
	close(f2);
	if (n1 != n2)
		return 1;
	for (int i = 0; i < n1; i++)
		if (buf1[i] != buf2[i])
			return 2;
	return 0;
}

void dataB(char* filename, int tasknum)
{
	for (int i = 0; i < 8; i++)
		filename[i] = (char)(rand() % 26 + 97);
	filename[8] = '\0';
	int f = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	int sz = (10 + rand() % 10) * 2;
	if (tasknum == 10)
		sz = 9 + rand() % 8;
	if (tasknum != 4 && tasknum != 6)
		sz += rand() % 2;
	char c[50];
	int r[4];
	do
	{
		for (int i = 0; i < 4; i++)
			r[i] = 0;

		for (int i = 0; i < sz; i++)
			switch (rand() % 4)
			{
			case 0:
				c[i] = (char)(rand() % 10 + 48);
				r[0]++;
				break;
			case 1:
				c[i] = (char)(rand() % 26 + 65);
				r[1]++;
				break;
			case 2:
				c[i] = (char)(rand() % 26 + 97);
				r[2]++;
				break;
			case 3:
				c[i] = (char)(rand() % 16 + 33);
				r[3]++;
				break;
			}
	} while (r[0] < 2 || r[1] < 2 || r[2] < 2 || r[3] < 2);
	write(f, c, sz);
	close(f);
	f = open(controlfilename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	char c0 = 'A';
	char* xx = "XX";
	char* aaa = "AAA";
	switch (tasknum)
	{
	case 1:
		for (int i = sz - 1; i >= 0; i--)
			write(f, &c[i], 1);
		break;
	case 2:
		for (int i = sz - 1; i >= 0; i--)
		{
			c[i] = tolower(c[i]);
			write(f, &c[i], 1);
		}
		break;
	case 3:
		for (int i = 0; i < 10; i++)
			write(f, &c[i], 1);
		break;
	case 4:
		for (int i = 0; i < sz / 2; i++)
			write(f, &c[i], 1);
		break;
	case 5:
		for (int i = sz - 10; i < sz; i++)
			write(f, &c[i], 1);
		break;
	case 6:
		for (int i = sz / 2; i < sz; i++)
			write(f, &c[i], 1);
		break;
	case 7:
		for (int i = 0; i < sz; i++)
			if (i % 2 == 0)
				write(f, &c[i], 1);
		break;
	case 8:
		for (int i = 0; i < sz; i++)
			if (!isdigit(c[i]))
				write(f, &c[i], 1);
		break;
	case 9:
		for (int i = sz - 1; i >= 0; i--)
			if (!isupper(c[i]))
				write(f, &c[i], 1);
		break;
	case 10:
		for (int i = 0; i < 20 - sz; i++)
			write(f, &c0, 1);
		for (int i = 0; i < sz; i++)
			write(f, &c[i], 1);
		break;
	case 11:
		for (int i = 0; i < sz; i++)
			write(f, &c[i], 1);
		for (int i = 0; i < sz; i++)
			write(f, &c[i], 1);
		break;
	case 12:
		for (int i = 0; i < sz; i++)
			write(f, &c[i], 1);
		for (int i = sz - 1; i >= 0; i--)
			write(f, &c[i], 1);
		break;
	case 13:
		for (int i = 0; i < sz; i++)
		{
			write(f, &c[i], 1);
			if (i % 2 == 0)
				write(f, &c[i], 1);
		}
		break;
	case 14:
		for (int i = 0; i < sz; i++)
		{
			write(f, &c[i], 1);
			if (isdigit(c[i]))
				write(f, &c[i], 1);
		}
		break;
	case 15:
		for (int i = 0; i < sz; i++)
		{
			if (i % 2 == 0)
				write(f, &c[i], 1);
			else
				write(f, xx, 2);
		}
		break;
	case 16:
		for (int i = 0; i < sz; i++)
		{
			if (!isdigit(c[i]))
				write(f, &c[i], 1);
			else
				write(f, aaa, 3);
		}
		break;
	case 17:
		for (int i = 0; i < sz / 2; i++)
		{
			write(f, &c[i], 1);
			write(f, &c[sz - i - 1], 1);
		}
		if (sz % 2 != 0)
			write(f, &c[sz / 2], 1);
		break;
	}
	close(f);
}


char firsttaskgroup = 'B';
char lasttaskgroup = 'B';

int main(int argc, char* argv[])
{
	srand((unsigned)time(0));
	if (argc != 3)
	{
		printf("Format: TaskChecker <task name> <checking program>\n");
		exit(2);
	}
	int f = open(argv[2], O_RDONLY);
	if (f == -1)
		err_sys("Error when opening checking program: ");
	close(f);
	char taskgroup = argv[1][0];
	int tasknum = atoi(argv[1] + 1);
	if (taskgroup < firsttaskgroup || taskgroup > lasttaskgroup)
	{
		printf("Error: Wrong task group: %c\n", taskgroup);
		exit(3);
	}
	if (tasknum == 0)
	{
		printf("Error: Wrong task number: %d\n", tasknum);
		exit(4);
	}
	char logfilename[300];
	strcpy(logfilename, argv[2]);
	strcat(logfilename, ".gcclog");
	char outfilename[300];
	strcpy(outfilename, argv[2]);
	strcat(outfilename, ".out");
	int flog = open(logfilename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (flog == -1)
		err_sys("Error during creation log-file: ");
	printf("Compilation...\n");
	unlink(outfilename);
	int pid = fork();
	if (pid == 0)
	{
		dup2(flog, 2);
		close(flog);
		execlp("gcc", "gcc", "-Wall", argv[2], "-o", outfilename, (char*)0);
		err_sys("Error when running gcc: ");
	}

	close(flog);
	int status;
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
		err_sys("Error during compilation: ");
	f = open(outfilename, O_RDONLY);
	if (f == -1)
	{
		printf("Error: Compiler outputs some error messages\n");
		printf("(see file %s)\n", logfilename);
		exit(5);
	}
	close(f);
	struct stat statbuf;
	stat(logfilename, &statbuf);
	if (statbuf.st_size > 0)
	{
		printf("Compiler outputs some warnings\n");
		printf("(see file %s)\n", logfilename);
		puts("Compilation is partially successful");
	}
	else
	    puts("Compilation is successful");
	char filename[20];
	switch (taskgroup)
	{
	case 'B':
		dataB(filename, tasknum);
		break;
	}
	printf("Running...\n");
	pid = fork();
	if (pid == 0)
	{
		execl(outfilename, outfilename, filename, (char*)0);
		printf("Error when running program %s", outfilename);
		exit(6);
	}
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
		err_sys("Error during running: ");
	puts("Running is successful");
	printf("Checking results...\n");
	switch (filecompare(filename, controlfilename))
	{
	case 0:
		puts("Success!");
		return 0;
	case 1:
		puts("The file sizes are different");
		return 7;
	case 2:
		puts("The contents of the files are different");
		return 8;
	}
}