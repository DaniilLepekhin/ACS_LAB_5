# ABC-lab5
# Многопоточное программирование

* Для программы умножения двух квадратных матриц DGEMM BLAS разработанной в
задании 4 на языке С/С++ реализовать многопоточные вычисления. В потоках
необходимо реализовать инициализацию массивов случайными числами типа
double и равномерно распределить вычислительную нагрузку. Обеспечить
возможность задавать размерность матриц и количество потоков при запуске
программы. Многопоточность реализовать несколькими способами. 

 * С использованием библиотеки стандарта POSIX Threads.
 * С использованием библиотеки стандарта OpenMP.
 * C использованием библиотеки стандарта MPI. Все матрицы помещаются в
общей памяти одного вычислителя. 

* Для всех способов организации многопоточности построить график зависимости
коэффициента ускорения многопоточной программы от числа потоков для заданной
размерностиматрицы, например, 5000, 10000 и 20000 элементов.
* Определить оптимальное число потоков для вашего оборудования.
              
--------------------
* Оптимальное число потоков для моего оборудования: 4, так как мой процессор имеет 4 ядер и 4 потока.
