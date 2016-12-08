#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

main()
{
	pid_t parent = getpid();
	pid_t p1;
	pid_t p2;
	printf("Оригинальная программа, pid = %d\n", parent);
	p1 = fork();
	if (p1 == 0)
	{
		printf("Я дочерний процесс 1. Мой pid = %d, родительский id = %d\n", getpid(), getppid());
		exit(0);
	}
	else
	{
		int status;
		waitpid(p1, &status, 0);
		p2 = fork();
		if (p2 == 0)
		{
			printf("Я дочерний процесс 2. Мой pid = %d, родительский id = %d\n", getpid(), getppid());
			exit(0);
		}	
		waitpid(p2, &status, 0);
		printf("Я родительский процесс. Hello World.\n");
	}
}
