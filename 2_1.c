#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <cstdio>
#include <pthread.h>
#include <cstdlib>
#include <math.h> 
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void *thread_func(void *vptr_args)
{
	printf("hello world!\n");
	return NULL;
}

int main(int argc, char *argv[])
{
	int procs;
	procs = atoi(argv[1]);
	for (int i = 0; i < procs; i++)
	{
		pthread_t thread;
		pthread_create(&thread, NULL, thread_func, NULL);
		pthread_join(thread, NULL);
	}
	printf("Goodbye world\n");
	return 0;
}
