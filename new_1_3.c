#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>

void random_point(double* x, double* y) {
    double divisor = RAND_MAX / 2.0;
    *x = rand() / divisor - 1;
    *y = rand() / divisor - 1;
}

int count_points_inside_circle(int iters) {
    int inside = 0;
    for (int i = 0; i < iters; ++i) {
        double x;
        double y;
        random_point(&x, &y);
        if (((x * x) + (y * y)) <= 1) {
            ++inside;
        }
    }
    return inside;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: pi_mq <procs> <iters>\n");
        return 0;
    }

    int procs = atoi(argv[1]);
    int iters = atoi(argv[2]);

    struct mq_attr attr = {0};
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(int);

    mqd_t mqd = mq_open("/pi", O_CREAT | O_RDWR, 0666, &attr);
    if (mqd == -1) {
        int err = errno;
        fprintf(stderr, "%d (%s): failed to open message queue\n", err, strerror(err));
        return -1;
    }

    for (int i = 0; i < procs; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            return -1;
        }
        else if (pid == 0) {
            srand(time(NULL) ^ getpid());
            int count = count_points_inside_circle(iters);
            if (mq_send(mqd, (char*)&count, sizeof(count), 0) == -1) {
                int err = errno;
                fprintf(stderr, "%d (%s): failed to send message\n", err, strerror(err));
            }
            return 0;
        }
    }

    int count = 0;
    int total = 0;

    while (wait(NULL) > 0) {
        mq_getattr(mqd, &attr);
        for (int i = 0; i < attr.mq_curmsgs; ++i) {
            if (mq_receive(mqd, (char*)&count, sizeof(count), NULL) == -1) {
                int err = errno;
                fprintf(stderr, "%d (%s): failed to receive message\n", err, strerror(err));
                break;
            }
            total += count;
        }
    }

    mq_close(mqd);
    mq_unlink("/pi");

    double pi = (4.0 * total) / (procs * iters);
    printf("%lf\n", pi);
    return 0;
}

