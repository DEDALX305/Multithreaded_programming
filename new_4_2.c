#include<math.h> 
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#define min_a 1000 //Начальный радиус

double circle(double, double); //Выдает квадрат y в зависимости от координаты Х и радиуса круга.
// -fopenmp
int main(int argc, char* argv[])
{

	int procs = atoi(argv[1]);
	int result = 0;
	double x, y, Pi;
	long long int a = min_a, i = 0;//Счетчик //сторона квадарата
	double Ncirc2 = 0, Ncirc1 = 0;//Количество точек, попавших в круг 
	double Nmax = 100000; //Общее количество точек
	int j;
	/*int fd[2];
	pipe(fd);
	ssize_t size;*/

	/*double data_processed;


	pid_t parent = getpid();
	pid_t Mproc1, Mproc2;
	Mproc1 = fork();

	printf("Original, pid = %d\n", parent);*/
	int n;
	n = Nmax / procs;

	/*if (Mproc1 < 0)
	{
		printf("Can't fork childn");
		exit(-1);
	}*/

	/*else if (Mproc1 > 0) {*/

	//	/* Parent process */
	//	int status;
	///*	waitpid(Mproc1, &status, 0);*/
	//	printf("I parent\n");

		/*close(fd[1]);*/
		/*data_processed = read(fd[0], &Ncirc1, sizeof(Ncirc1));
		data_processed = read(fd[0], &Ncirc2, sizeof(Ncirc2));*/
		//Pi = ((Ncirc1 + Ncirc2) / Nmax) * 4;
		////Pi=(Ncirc/Nmax)*4;

		//printf("pi = %f\n", Pi);

	/*}
	else
	{*/

		/* Child process */
		//for (int x = 0; x < 2; x++) // i, j - cчетчики
		//{

		/*if (Mproc1 == 0)
		{*/
#pragma omp parallel num_threads(procs)
		{
			/*printf("I child. my pid = %d, parent id = %d\n", getpid(), getppid());*/
			Ncirc1 = 0; i = 0;
			//while (i<Nmax) 
			srand(time(NULL) - i * 3);


#pragma omp parallel for private(j) schedule(dynamic) reduction(+:result) 
			for (int j = 0; j < n; j++)
			{
				//x = (rand() % (a * 1000))/1000;  //Рандомный Х с 3 знаками после запятой
				// y = (rand() % (a * 1000))/1000;  //Рандомный Y с 3 знаками после запятой

				double a = 2.0;
				srand(time(NULL) - j * 2);
				x = ((double)rand() / (double)(RAND_MAX)) * a; //Рандомный Х
				x = x - 1;
				srand(time(NULL) - j * i * 2);
				y = ((double)rand() / (double)(RAND_MAX)) * a; //Рандомный Y
				y = y - 1;


				if (y*y <= circle(x, (a / 2)))  //Условие принадлежности точки к кругу
				{
					Ncirc1++;
				}

				result += Ncirc1;
				/*Ncirc1 = Ncirc1;*/
			/*	i++;*/

			}

			//printf("Отправка в pipe tochek Pi= %f \n", Ncirc1);
			////Pi=(Ncirc/Nmax)*4; 
			//close(fd[0]);
			////printf("\n %lld,%.0f,%f\n",a,Nmax,Pi);
			//data_processed = write(fd[1], &Ncirc1, sizeof(Ncirc1));
		}

		Pi = (Ncirc1/Nmax) * 4;
		//Pi=(Ncirc/Nmax)*4;

		printf("pi = %f\n", Pi);
			//printf("Отправка в pipe Pi= %f \n", Pi);
			//printf("Отправка в pipe Pi= %f \n", data_processed);
		/*}*/
		//}

		//if (Mproc1 == 0)
		//{

		//	printf("I child. my pid = %d, parent id = %d\n", getpid(), getppid());
		//	Ncirc2 = 0; i = 0;
		//	//while (i<Nmax) 
		//	for (int j = 0; j < n; j++)
		//	{
		//		//x = (rand() % (a * 1000))/1000;  //Рандомный Х с 3 знаками после запятой
		//		// y = (rand() % (a * 1000))/1000;  //Рандомный Y с 3 знаками после запятой

		//		double a = 2.0;
		//		srand(time(NULL) - j * 2);
		//		x = ((double)rand() / (double)(RAND_MAX)) * a; //Рандомный Х
		//		x = x - 1;
		//		srand(time(NULL) - j * i * 2);
		//		y = ((double)rand() / (double)(RAND_MAX)) * a; //Рандомный Y
		//		y = y - 1;


		//		if (y*y <= circle(x, (a / 2)))  //Условие принадлежности точки к кругу
		//		{
		//			Ncirc2++;
		//		}

		//		i++;

		//	}
		//	printf("Отправка в pipe tochek Pi= %f \n", Ncirc1);
		//	//Pi=(Ncirc/Nmax)*4; 
		//	close(fd[0]);
		//	//printf("\n %lld,%.0f,%f\n",a,Nmax,Pi);
		//	data_processed = write(fd[1], &Ncirc2, sizeof(Ncirc2));
		//	//printf("Отправка в pipe Pi= %f \n", Pi);
		//	printf("Отправка в pipe Pi= %f \n", data_processed);

		//}
		/////////////////////////////////////////////////////////////////////////////

		/*exit(1);*/
	}
	/////////////////////////
//}



double circle(double x, double radius)
{
	double y = radius*radius - x*x;
	return y;
}