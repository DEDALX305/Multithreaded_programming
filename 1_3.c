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

int main()
{
	int procs = 4;
	int iters = 100000000;

    struct mq_attr attr = {0};
    attr.mq_flags = 0; // флаг очереди : 0, O_NONBLOCK
    attr.mq_maxmsg = 10; // Максимально допустимое количество сообщений
    attr.mq_msgsize = sizeof(int); // Максимальный размер сообщения (в байтах)

    mqd_t mqd = mq_open("/pi", O_CREAT | O_RDWR, 0666, &attr); // mq_open Открытие/создание очереди сообщений
	// O_CREAT при необходимости создает файл с правами доступа, заданными в параметре mode
	// O_RDWR Открытие для чтения и записи
    if (mqd == -1) 
	{ /* Возвращает 0 в случае успешного завершения, –1 – в случае возникновения ошибок */
        int err = errno;
        fprintf(stderr, "%d (%s): не удалось открыть очередь сообщений\n", err, strerror(err));
        return -1;
    }

    for (int i = 0; i < procs; ++i) 
	{
        pid_t pid = fork();
        if (pid == -1) 
		{
            return -1;
        }
        else if (pid == 0) 
		{
            srand(time(NULL) ^ getpid());
			// Начало расчета количества точек в круге -----------------------------------------------
			int inside = 0;
			for (int i = 0; i < iters; ++i) 
			{
				double x;
				double y;
				double divisor = RAND_MAX / 2.0;
				x = rand() / divisor - 1;
				y = rand() / divisor - 1;
				if (((x * x) + (y * y)) <= 1)
				{
					++inside;
				}
			}
			int count = inside;
			// Конец расчета количества точек в круге ------------------------------------------------
            if (mq_send(mqd, (char*)&count, sizeof(count), 0) == -1) // mq_send Отправка сообщения в очередь
			{ /* Возвращает 0 в случае успешного завершения, –1 – в случае возникновения ошибок */
                int err = errno;
                fprintf(stderr, "%d (%s): не удалось отправить сообщение\n", err, strerror(err));
            }
            return 0;
        }
    }

    int count = 0;
    int total = 0;

    while (wait(NULL) > 0) 
	{
        mq_getattr(mqd, &attr); // Получение атрибутов очереди сообщений
        for (int i = 0; i < attr.mq_curmsgs; ++i)
		{
            if (mq_receive(mqd, (char*)&count, sizeof(count), NULL) == -1) // mq_receive Приём сообщения из очереди
			{ /* Возвращает 0 в случае успешного завершения, –1 – в случае возникновения ошибок */
                int err = errno;
                fprintf(stderr, "%d (%s): не удалось отправить сообщение\n", err, strerror(err));
                break;
            }
            total += count;
        }
    }

    mq_close(mqd); // Закрытие очереди сообщений Возвращает 0 в случае успешного завершения. –1 в случае ошибки
    mq_unlink("/pi"); // Удаление очереди сообщений

    double pi = (4.0 * total) / (procs * iters);
    printf("%lf\n", pi);
    return 0;
}

