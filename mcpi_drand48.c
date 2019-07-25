/*

円周率を計算する OpenMP プログラム(富士通のパンフレットから引用)

○x86-64 のコードを生成

% icc -openmp -O3 mcpi.c -o mcpi.x86-64

○XeonPhi のコードを生成

% icc -openmp -mmic -O3 -parallel mcpi.c -o mcpi.phi

*/

#include<stdio.h>
#include<stdlib.h>
#define NUM_MAX_THREADS 256

main(int argc,char **argv)
{
  long long i,c,n;
  double x,y;
  struct drand48_data drbufx[NUM_MAX_THREADS],drbufy[NUM_MAX_THREADS];

  n = 10000000;
  c = 0;
  //for (i = 0;i < NUM_MAX_THREADS;i++){
  //  srand48(&drbufx[i]);
  //  srand48(&drbufy[i]);
  //}
  srand48(100);

#pragma omp parallel
  {
#pragma omp single
    {
      printf("現在使用中のスレッド数は「%d」です。\n", omp_get_num_threads());
      printf("使用可能なスレッド数は最大「%d」です。\n", omp_get_max_threads());
    }
  }

#pragma omp parallel for private(x,y) reduction(+:c)
  for (i = 0;i < n;i++){
    /* drand48()はスレッドセーフでないので，結果が保証されない */
    x = drand48();
    y = drand48();
    if (x * x + y * y < 1.0){
      c++;
    }
  }
  printf("%f\n",c * 4.0 / n);
}
