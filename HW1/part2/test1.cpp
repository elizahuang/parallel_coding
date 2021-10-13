#include <iostream>
#include "test.h"
#include "fasttime.h"

void test1(float* __restrict a, float* __restrict b, float* __restrict c, int N) {
  __builtin_assume(N == 1024);
  a = (float *)__builtin_assume_aligned(a, 32);
  b = (float *)__builtin_assume_aligned(b, 32);
  c = (float *)__builtin_assume_aligned(c, 32);

  // double totalTime=0;
  // for(int i=0;i<20;i++){
  //   fasttime_t time1 = gettime();
  //   for (int i=0; i<I; i++) {
  //     for (int j=0; j<N; j++) {
  //       c[j] = a[j] + b[j];
  //     }
  //   }
  //   fasttime_t time2 = gettime();
  //   double elapsedf = tdiff(time1, time2);
  //   totalTime+=elapsedf;
  // }

  // std::cout << "Elapsed execution time of the loop in test1():\n" 
  //   << totalTime/20.0 << "sec (N: " << N << ", I: " << I << ")\n";

  fasttime_t time1 = gettime();
  for (int i=0; i<I; i++) {
    for (int j=0; j<N; j++) {
      c[j] = a[j] + b[j];
    }
  }
  fasttime_t time2 = gettime();

  double elapsedf = tdiff(time1, time2);

  std::cout << "Elapsed execution time of the loop in test1():\n" 
    << elapsedf << "sec (N: " << N << ", I: " << I << ")\n";

}