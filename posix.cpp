#include <pthread.h>
#include <iostream>
#include <ctime>
#include "hpctimer.h"


struct arg_matrix {
    double *a;
    double *b;
    double *c;
    int n;
};

int count = 0;
int num_th;

void *dgemm_def(void *_matrix) {
    int i, j, k;
    int thread_num = count++;
    arg_matrix matrix = (*(arg_matrix *) _matrix);
    int rows = matrix.n / num_th;
    int start = thread_num * rows;
    int end = start + rows;

    for (i = start; i < end; ++i) {
        for (k = 0; k < matrix.n; ++k) {
            for (j = 0; j < matrix.n; ++j) {
                *(matrix.c + i * matrix.n + j) += *(matrix.a + i * matrix.n + k) * *(matrix.b + k * matrix.n + j);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int size = atoi(argv[1]);
    num_th = atoi(argv[2]);
    pthread_t threads_id[num_th];
    arg_matrix matrix;
    


    matrix.a = new double[size * size];
    matrix.b = new double[size * size];
    matrix.c = new double[size * size]{0};
    matrix.n = size;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(matrix.a + i * size + j) = i;
            *(matrix.b + i * size + j) = 1.0;
        }
    }
    double t = hpctimer_getwtime();
    for (int i = 0; i < num_th; i++) {
        pthread_create(&threads_id[i], NULL, dgemm_def, &matrix);

    }
    for (int i = 0; i < num_th; i++) {
        pthread_join(threads_id[i], NULL);

    }
    t = hpctimer_getwtime() - t;
    std::cout << t  << std::endl;

}