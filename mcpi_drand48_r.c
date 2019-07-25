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
  for (i = 0;i < NUM_MAX_THREADS;i++){
    srand48_r(i * 2,&drbufx[i]);
    srand48_r(i * 2 + 1,&drbufy[i]);
  }

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
    /* drand48_r は drand48 のスレッドセーフバージョン */
    /* 引数で指定した領域を用いて乱数生成を行う　　　　　　*/
    /* スレッドごとに違う領域を使うことで ，複数スレッドが */
    /* 安全に同時実行できる                           */
    drand48_r(&drbufx[omp_get_thread_num()],&x);
    drand48_r(&drbufy[omp_get_thread_num()],&y);
    if (x * x + y * y < 1.0){
      c++;
    }
  }
  printf("%f\n",c * 4.0 / n);
}
