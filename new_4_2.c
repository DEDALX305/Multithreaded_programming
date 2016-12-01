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

#define min_a 1000 //��������� ������

double circle(double, double); //������ ������� y � ����������� �� ���������� � � ������� �����.
// -fopenmp
int main(int argc, char* argv[])
{

	int procs = atoi(argv[1]);
	int result = 0;
	double x, y, Pi;
	long long int a = min_a, i = 0;//������� //������� ���������
	double Ncirc2 = 0, Ncirc1 = 0;//���������� �����, �������� � ���� 
	double Nmax = 100000; //����� ���������� �����
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
		//for (int x = 0; x < 2; x++) // i, j - c�������
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
				//x = (rand() % (a * 1000))/1000;  //��������� � � 3 ������� ����� �������
				// y = (rand() % (a * 1000))/1000;  //��������� Y � 3 ������� ����� �������

				double a = 2.0;
				srand(time(NULL) - j * 2);
				x = ((double)rand() / (double)(RAND_MAX)) * a; //��������� �
				x = x - 1;
				srand(time(NULL) - j * i * 2);
				y = ((double)rand() / (double)(RAND_MAX)) * a; //��������� Y
				y = y - 1;


				if (y*y <= circle(x, (a / 2)))  //������� �������������� ����� � �����
				{
					Ncirc1++;
				}

				result += Ncirc1;
				/*Ncirc1 = Ncirc1;*/
			/*	i++;*/

			}

			//printf("�������� � pipe tochek Pi= %f \n", Ncirc1);
			////Pi=(Ncirc/Nmax)*4; 
			//close(fd[0]);
			////printf("\n %lld,%.0f,%f\n",a,Nmax,Pi);
			//data_processed = write(fd[1], &Ncirc1, sizeof(Ncirc1));
		}

		Pi = (Ncirc1/Nmax) * 4;
		//Pi=(Ncirc/Nmax)*4;

		printf("pi = %f\n", Pi);
			//printf("�������� � pipe Pi= %f \n", Pi);
			//printf("�������� � pipe Pi= %f \n", data_processed);
		/*}*/
		//}

		//if (Mproc1 == 0)
		//{

		//	printf("I child. my pid = %d, parent id = %d\n", getpid(), getppid());
		//	Ncirc2 = 0; i = 0;
		//	//while (i<Nmax) 
		//	for (int j = 0; j < n; j++)
		//	{
		//		//x = (rand() % (a * 1000))/1000;  //��������� � � 3 ������� ����� �������
		//		// y = (rand() % (a * 1000))/1000;  //��������� Y � 3 ������� ����� �������

		//		double a = 2.0;
		//		srand(time(NULL) - j * 2);
		//		x = ((double)rand() / (double)(RAND_MAX)) * a; //��������� �
		//		x = x - 1;
		//		srand(time(NULL) - j * i * 2);
		//		y = ((double)rand() / (double)(RAND_MAX)) * a; //��������� Y
		//		y = y - 1;


		//		if (y*y <= circle(x, (a / 2)))  //������� �������������� ����� � �����
		//		{
		//			Ncirc2++;
		//		}

		//		i++;

		//	}
		//	printf("�������� � pipe tochek Pi= %f \n", Ncirc1);
		//	//Pi=(Ncirc/Nmax)*4; 
		//	close(fd[0]);
		//	//printf("\n %lld,%.0f,%f\n",a,Nmax,Pi);
		//	data_processed = write(fd[1], &Ncirc2, sizeof(Ncirc2));
		//	//printf("�������� � pipe Pi= %f \n", Pi);
		//	printf("�������� � pipe Pi= %f \n", data_processed);

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