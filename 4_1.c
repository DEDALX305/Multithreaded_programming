#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

// -fopenmp
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
