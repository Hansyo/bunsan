#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

/* N が大きいときに必要なオプション        */
/* icc -mcmodel=medium mat_mul_base.c */

#define N	(10384LL) // 2^13

static void
mat_set(double *m);

static void
mat_mul(double *a, double *b, double *c,int n);

static void
mat_show(double *c);

  int
main(int argc,char *argv[])
{
  static double *a,*b,*c;

  a = (double *)malloc(sizeof(double) * N * N);
  b = (double *)malloc(sizeof(double) * N * N);
  c = (double *)malloc(sizeof(double) * N * N);

  if( argc != 2 ){
    printf("使い方：%s スレッド数\n",argv[0]);
    exit(1);
  }
  mat_set(a);
  mat_set(b);
  omp_set_num_threads(atoi(argv[1]));
  puts("test4");
  mat_mul(a,b,c,N);

  // mat_show(c);

}

  void
mat_set(double *m)
{
  int i,j;
  double d;

  for (i = 0;i < N;i++){
    for (j = 0;j < N;j++){
      /* テスト用 */
      if (i == j){
        d = 1.0;
      }else{
        d = 0.0;
      }
      /* ランダムデータ */
      // d = ((double)random() / INT_MAX) * 10.0;
      m[i*N+j] = d;
    }
  }
}

  void
mat_mul(double a[N*N], double b[N*N], double c[N*N],int n)
{
  int i,j,k,threads_num;
  double st_time,en_time;

  threads_num = omp_get_max_threads();

  for(i = 0;i < n;i++) {
    for(j = 0;j < n;j++) {
      c[i*N+j] = 0;
    }
  }

  printf("%d\n",threads_num);
  scanf("%*c");
  st_time = omp_get_wtime();
#pragma omp parallel for private(i) num_threads(threads_num)
  for(i = 0;i < n;i+=8) {
    int i1,i2,i3,i4,i5,i6,i7,i8;
    i1 = (i + 1)*N;
    i2 = (i + 2)*N;
    i3 = (i + 3)*N;
    i4 = (i + 4)*N;
    i5 = (i + 5)*N;
    i6 = (i + 6)*N;
    i7 = (i + 7)*N;
    i8 = (i + 8)*N;
    for(k = 0;k < n;k+=8) {
      int k1,k2,k3,k4,k5,k6,k7,k8;
      int kn1,kn2,kn3,kn4,kn5,kn6,kn7,kn8;
      k1 = k+1;
      k2 = k+2;
      k3 = k+3;
      k4 = k+4;
      k5 = k+5;
      k6 = k+6;
      k7 = k+7;
      k8 = k+8;
      kn1 = k1*N;
      kn2 = k2*N;
      kn3 = k3*N;
      kn4 = k4*N;
      kn5 = k5*N;
      kn6 = k6*N;
      kn7 = k7*N;
      kn8 = k8*N;

      for(j = 0;j < n; j++) {

        c[i1+j] += a[i1+k1]*b[k1+j];
        c[i1+j] += a[i1+k2]*b[k2+j];
        c[i1+j] += a[i1+k3]*b[k3+j];
        c[i1+j] += a[i1+k4]*b[k4+j];
        c[i1+j] += a[i1+k5]*b[k5+j];
        c[i1+j] += a[i1+k6]*b[k6+j];
        c[i1+j] += a[i1+k7]*b[k7+j];
        c[i1+j] += a[i1+k8]*b[k8+j];

        c[i2+j] += a[i2+k1]*b[k1+j];
        c[i2+j] += a[i2+k2]*b[k2+j];
        c[i2+j] += a[i2+k3]*b[k3+j];
        c[i2+j] += a[i2+k4]*b[k4+j];
        c[i2+j] += a[i2+k5]*b[k5+j];
        c[i2+j] += a[i2+k6]*b[k6+j];
        c[i2+j] += a[i2+k7]*b[k7+j];
        c[i2+j] += a[i2+k8]*b[k8+j];

        c[i3+j] += a[i3+k1]*b[k1+j];
        c[i3+j] += a[i3+k2]*b[k2+j];
        c[i3+j] += a[i3+k3]*b[k3+j];
        c[i3+j] += a[i3+k4]*b[k4+j];
        c[i3+j] += a[i3+k5]*b[k5+j];
        c[i3+j] += a[i3+k6]*b[k6+j];
        c[i3+j] += a[i3+k7]*b[k7+j];
        c[i3+j] += a[i3+k8]*b[k8+j];

        c[i4+j] += a[i4+k1]*b[k1+j];
        c[i4+j] += a[i4+k2]*b[k2+j];
        c[i4+j] += a[i4+k3]*b[k3+j];
        c[i4+j] += a[i4+k4]*b[k4+j];
        c[i4+j] += a[i4+k5]*b[k5+j];
        c[i4+j] += a[i4+k6]*b[k6+j];
        c[i4+j] += a[i4+k7]*b[k7+j];
        c[i4+j] += a[i4+k8]*b[k8+j];

        c[i5+j] += a[i5+k1]*b[k1+j];
        c[i5+j] += a[i5+k2]*b[k2+j];
        c[i5+j] += a[i5+k3]*b[k3+j];
        c[i5+j] += a[i5+k4]*b[k4+j];
        c[i5+j] += a[i5+k5]*b[k5+j];
        c[i5+j] += a[i5+k6]*b[k6+j];
        c[i5+j] += a[i5+k7]*b[k7+j];
        c[i5+j] += a[i5+k8]*b[k8+j];

        c[i6+j] += a[i6+k1]*b[k1+j];
        c[i6+j] += a[i6+k2]*b[k2+j];
        c[i6+j] += a[i6+k3]*b[k3+j];
        c[i6+j] += a[i6+k4]*b[k4+j];
        c[i6+j] += a[i6+k5]*b[k5+j];
        c[i6+j] += a[i6+k6]*b[k6+j];
        c[i6+j] += a[i6+k7]*b[k7+j];
        c[i6+j] += a[i6+k8]*b[k8+j];

        c[i7+j] += a[i7+k1]*b[k1+j];
        c[i7+j] += a[i7+k2]*b[k2+j];
        c[i7+j] += a[i7+k3]*b[k3+j];
        c[i7+j] += a[i7+k4]*b[k4+j];
        c[i7+j] += a[i7+k5]*b[k5+j];
        c[i7+j] += a[i7+k6]*b[k6+j];
        c[i7+j] += a[i7+k7]*b[k7+j];
        c[i7+j] += a[i7+k8]*b[k8+j];

        c[i8+j] += a[i8+k1]*b[k1+j];
        c[i8+j] += a[i8+k2]*b[k2+j];
        c[i8+j] += a[i8+k3]*b[k3+j];
        c[i8+j] += a[i8+k4]*b[k4+j];
        c[i8+j] += a[i8+k5]*b[k5+j];
        c[i8+j] += a[i8+k6]*b[k6+j];
        c[i8+j] += a[i8+k7]*b[k7+j];
        c[i8+j] += a[i8+k8]*b[k8+j];

      }
    }
  }

  en_time = omp_get_wtime();

  printf(
      "threads=%2d time=%.6f\n",omp_get_max_threads(),en_time-st_time
      );

}

  void
mat_show(double c[N*N])
{
  int i,j;

  for (i = 0;i < N;i++){
    for (j = 0;j < N;j++){
      printf ("%2.1lf ",c[i*N+j]);
    }
    printf("\n");
  }
}
