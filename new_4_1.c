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

int main(int argc, char* argv[]) {

	if (argc != 2)
	{
		printf("Введите количество потоков\n");
		exit(1);
	}

	int threads = atoi(argv[1]);

	#pragma omp parallel num_threads(threads)
	{
		printf("Hello, World! \n");
	}

	printf("Goodbye, World! \n");
}
