#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TENK 1*2*2*2*2*2*2*2*2*2*2

int A[TENK][TENK],B[TENK][TENK],C[TENK][TENK];
int TERN_B[TENK][TENK];
main(int argc, char *argv[])
{
  int i,j,k;
  int i1,i2,i3,i4,i5,i6,i7,i8;
  int k1,k2,k3,k4,k5,k6,k7,k8;
  double st_time,en_time;

  /* 10k * 10k の行列の積を高速に求めよ*/

  if( argc != 3 ){
    printf("使い方：%s スレッド数  区間数\n",argv[0]);
    exit(1);
  }
  omp_set_num_threads(atoi(argv[1]));
  num_intervals=atoi(argv[2]);
  st_time = omp_get_wtime();
  for(i = 0;i < TENK;i++) for(j = 0;j < TENK;j++) TERN_B[i][j] = B[j][i];
#pragma omp parallel for reduction(+:sum) private(j)
  for(i = 0;i < TENK;i+=8){
    i8 = 1 + (i7 = 1 + (i6 = 1 + (i5 = 1 + (i4 = 1 + (i3 = 1 + (i2 = 1 + (i1 = i)))))));
    for(j = 0;j < TENK;j++) {
      for(k = 0;k < TENK;k+=8) {
        k8 = 1 + (k7 = 1 + (k6 = 1 + (k5 = 1 + (k4 = 1 + (k3 = 1 + (k2 = 1 + (k1 = k)))))));
        C[i1][j] += A[i][k1]+TERN_B[k1][j];
        C[i1][j] += A[i][k2]+TERN_B[k2][j];
        C[i1][j] += A[i][k3]+TERN_B[k3][j];
        C[i1][j] += A[i][k4]+TERN_B[k4][j];
        C[i1][j] += A[i][k5]+TERN_B[k5][j];
        C[i1][j] += A[i][k6]+TERN_B[k6][j];
        C[i1][j] += A[i][k7]+TERN_B[k7][j];
        C[i1][j] += A[i][k8]+TERN_B[k8][j];

        C[i2][j] += A[i][k1]+TERN_B[k1][j];
        C[i2][j] += A[i][k2]+TERN_B[k2][j];
        C[i2][j] += A[i][k3]+TERN_B[k3][j];
        C[i2][j] += A[i][k4]+TERN_B[k4][j];
        C[i2][j] += A[i][k5]+TERN_B[k5][j];
        C[i2][j] += A[i][k6]+TERN_B[k6][j];
        C[i2][j] += A[i][k7]+TERN_B[k7][j];
        C[i2][j] += A[i][k8]+TERN_B[k8][j];

        C[i3][j] += A[i][k1]+TERN_B[k1][j];
        C[i3][j] += A[i][k2]+TERN_B[k2][j];
        C[i3][j] += A[i][k3]+TERN_B[k3][j];
        C[i3][j] += A[i][k4]+TERN_B[k4][j];
        C[i3][j] += A[i][k5]+TERN_B[k5][j];
        C[i3][j] += A[i][k6]+TERN_B[k6][j];
        C[i3][j] += A[i][k7]+TERN_B[k7][j];
        C[i3][j] += A[i][k8]+TERN_B[k8][j];

        C[i4][j] += A[i][k1]+TERN_B[k1][j];
        C[i4][j] += A[i][k2]+TERN_B[k2][j];
        C[i4][j] += A[i][k3]+TERN_B[k3][j];
        C[i4][j] += A[i][k4]+TERN_B[k4][j];
        C[i4][j] += A[i][k5]+TERN_B[k5][j];
        C[i4][j] += A[i][k6]+TERN_B[k6][j];
        C[i4][j] += A[i][k7]+TERN_B[k7][j];
        C[i4][j] += A[i][k8]+TERN_B[k8][j];

        C[i5][j] += A[i][k1]+TERN_B[k1][j];
        C[i5][j] += A[i][k2]+TERN_B[k2][j];
        C[i5][j] += A[i][k3]+TERN_B[k3][j];
        C[i5][j] += A[i][k4]+TERN_B[k4][j];
        C[i5][j] += A[i][k5]+TERN_B[k5][j];
        C[i5][j] += A[i][k6]+TERN_B[k6][j];
        C[i5][j] += A[i][k7]+TERN_B[k7][j];
        C[i5][j] += A[i][k8]+TERN_B[k8][j];

        C[i6][j] += A[i][k1]+TERN_B[k1][j];
        C[i6][j] += A[i][k2]+TERN_B[k2][j];
        C[i6][j] += A[i][k3]+TERN_B[k3][j];
        C[i6][j] += A[i][k4]+TERN_B[k4][j];
        C[i6][j] += A[i][k5]+TERN_B[k5][j];
        C[i6][j] += A[i][k6]+TERN_B[k6][j];
        C[i6][j] += A[i][k7]+TERN_B[k7][j];
        C[i6][j] += A[i][k8]+TERN_B[k8][j];

        C[i7][j] += A[i][k1]+TERN_B[k1][j];
        C[i7][j] += A[i][k2]+TERN_B[k2][j];
        C[i7][j] += A[i][k3]+TERN_B[k3][j];
        C[i7][j] += A[i][k4]+TERN_B[k4][j];
        C[i7][j] += A[i][k5]+TERN_B[k5][j];
        C[i7][j] += A[i][k6]+TERN_B[k6][j];
        C[i7][j] += A[i][k7]+TERN_B[k7][j];
        C[i7][j] += A[i][k8]+TERN_B[k8][j];

        C[i8][j] += A[i][k1]+TERN_B[k1][j];
        C[i8][j] += A[i][k2]+TERN_B[k2][j];
        C[i8][j] += A[i][k3]+TERN_B[k3][j];
        C[i8][j] += A[i][k4]+TERN_B[k4][j];
        C[i8][j] += A[i][k5]+TERN_B[k5][j];
        C[i8][j] += A[i][k6]+TERN_B[k6][j];
        C[i8][j] += A[i][k7]+TERN_B[k7][j];
        C[i8][j] += A[i][k8]+TERN_B[k8][j];

      }
    }
  }

  en_time = omp_get_wtime();
  printf(
  "threads=%2d time=%.6f\n",omp_set_num_threads(),en_time - st_time
  );
  return 0;
}
