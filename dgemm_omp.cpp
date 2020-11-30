#include <omp.h>
#include <iostream>
#include "hpctimer.h"

int size = 1000;
int THREADS = 1;

void matrix_vector_product_omp(double*,double*,double*);

int main(int argc, char **argv)
{
    size = atoi(argv[1]);
    THREADS = atoi(argv[2]);
    double *a, *b, *c;
    a = new double[size * size];
    b = new double[size * size];
    c = new double[size * size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *(a + i * size + j) = i;
            *(b + i * size + j) = 1.0;
        }
    }
    double t;

    t = hpctimer_getwtime();
    matrix_vector_product_omp(a,b,c);
    t = hpctimer_getwtime() - t;

    printf("Elapsed time (Num threads: %d): %.6f sec.\n size", THREADS, t);
    std::cout << t << std::endl;

    return 0;
}

void matrix_vector_product_omp(double *a, double *b, double *c)
{

#pragma omp parallel num_threads(THREADS)
    {
        int threadId = omp_get_thread_num();
        int itemsPerThread = size / THREADS;
        int lb = threadId * itemsPerThread;
        int ub = (threadId == THREADS - 1) ? (size) : (lb + itemsPerThread);
        int i, j, k;

        // for (i = lb; i < ub; ++i)
        // {
        //     for (j = 0; j < size; ++j)
        //         c[i] += a[i * size + j] * b[j];
        // }
        for (i = lb; i < ub; ++i)
        {
            for (k = 0; k < size; ++k)
            {
                for (j = 0; j < size; ++j)
                {
                    *(c + i * size + j) += *(a + i * size + k) * *(b + k * size + j);
                }
            }
        }
    }
}
