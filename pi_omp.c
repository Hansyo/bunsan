#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
  円周率を計算するプログラ
  C言語によるOpenMP入門(東京大学情報基盤センタープログラミング講習会資料)から引用，改変
　  http://www.cc.u-tokyo.ac.jp/support/kosyu/03/kosyu-openmp_c.pdf
*/

#define F(X) 4.0L/(1.0L+(X)*(X))

main(int argc, char *argv[])
{
  int i,num_intervals;
  long double x,step,sum=0.0L;
  double st_time,en_time;

  if( argc != 3 ){
    printf("使い方：%s スレッド数  区間数\n",argv[0]);
    exit(1);
  }
  omp_set_num_threads(atoi(argv[1]));
  num_intervals=atoi(argv[2]);
  st_time = omp_get_wtime();
  step = 1.0L/num_intervals;

  /*
     for 文の i を 区間数 / スレッド数 ずつ分担して並列実行する
       private(x)       ：x はスレッドごとに別の変数を持つ
  */

  /* リダクションを使うバージョン　多分一番速い                     */
  /* reduction(+:sum)　：各スレッドで計算したsumを最後に全部足す    */
#if 0
  #pragma omp parallel for reduction(+:sum) private(x)
  for(i = 0;i < num_intervals;i++){
    x = (i + 0.5L) * step;
    sum += F(x);
  }
#endif

  /* atomic を使うバージョン　まあまあ速い       */
  /* atomic 演算は，特定の演算子しか指定できない  */
  /* += の演算が atomic に実行されることを保証   */
#if 0
  #pragma omp parallel for private(x)
  for(i = 0;i < num_intervals;i++){
    x = (i + 0.5L) * step;
    #pragma omp atomic
    sum += F(x);
  }
#endif
  
  /* critical を使うバージョン 遅い 　　　　   */
  /* 同時に複数のスレッドが　critical section */
  /* を実行しないことが保証されている          */
#if 1
  #pragma omp parallel for private(x)
  for(i = 0;i < num_intervals;i++){
    x = (i + 0.5L) * step;
    #pragma omp critical
    {
      sum += F(x);
    }
  }
#endif

  /* バグ入りバージョン 　　　　   　                   */
  /* sum に対するアクセスを保護しない                   */
  /* 複数スレッドで実行した場合、正しい結果が得られないはず */
#if 0
  #pragma omp parallel for private(x)
  for(i = 0;i < num_intervals;i++){
    x = (i + 0.5L) * step;
    sum += F(x);
  }
#endif
  
  sum *= step;
  en_time = omp_get_wtime();
  printf(
    "threads=%2d time=%.6f sum=%.30Lf\n",omp_get_max_threads(),
    en_time-st_time,sum
  );
  return 0;
}
