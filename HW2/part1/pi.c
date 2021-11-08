/* Program to compute Pi using Monte Carlo methods */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#define SEED 35791246

typedef struct
{
   int thread_id;
   int start;
   int end;
   double *piCount;
} Arg; // 傳入 thread 的參數型別

// pthread_t callThd[numOf_t]; // 宣告建立 pthread
pthread_mutex_t mutexsum;    // pthread 互斥鎖

// 每個 thread 要做的任務
void *count_pi(void *arg)
{
   Arg *data = (Arg *)arg;
   int thread_id = data->thread_id;
   int start = data->start;
   int end = data->end;
   double *piCount = data->piCount;

   // 將原本的 PI 算法切成好幾份
   double x,y;
   double localCount = 0;
   // double step = 1 / MAGNIFICATION;
   for (int i = start; i < end; i++)
   {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      // z = x*x+y*y;
      if ((x*x+y*y)<=1) localCount++;
   }

   // **** 關鍵區域 ****
   // 一次只允許一個 thread 存取
   pthread_mutex_lock(&mutexsum);
   // 將部分的 PI 加進最後的 PI
   *piCount += localCount;
   pthread_mutex_unlock(&mutexsum);
   // *****************

   // printf("Thread %d did %d to %d:  local Pi=%lf global Pi=%.10lf\n", thread_id, start,
   //        end, local_pi, *pi);

   pthread_exit((void *)0);
}

int main(int argc, char** argv)
{
   // clock_t begin = clock();
   int numOf_t = atoi(argv[1]);
   int numOfTosses = atoi(argv[2]);
   // printf("argv1_%d\n",numOf_t);
   // printf("argv1_%d\n",numOfTosses);

   pthread_t callThd[numOf_t]; // 宣告建立 pthread
   // 初始化互斥鎖
   pthread_mutex_init(&mutexsum, NULL);

   // 設定 pthread 性質是要能 join
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   // 每個 thread 都可以存取的 PI
   // 因為不同 thread 都要能存取，故用指標
   double *piCount = malloc(sizeof(*piCount));
   *piCount = 0;

   int part = numOfTosses / numOf_t;

   Arg arg[numOf_t]; // 每個 thread 傳入的參數
   for (int i = 0; i < numOf_t; i++)
   {
      // 設定傳入參數
      arg[i].thread_id = i;
      arg[i].start = part * i;
      arg[i].end = part * (i + 1);
      arg[i].piCount = piCount; // PI 的指標，所有 thread 共用

      // 建立一個 thread，執行 count_pi 任務，傳入 arg[i] 指標參數
      pthread_create(&callThd[i], &attr, count_pi, (void *)&arg[i]);
   }

   // 回收性質設定
   pthread_attr_destroy(&attr);

   void *status;
   for (int i = 0; i <numOf_t; i++)
   {
      // 等待每一個 thread 執行完畢
      pthread_join(callThd[i], &status);
   }

   // 所有 thread 執行完畢，印出 PI
   printf("%.10lf \n",4*(*piCount)/numOfTosses);
   // printf("Pi =  %.10lf \n", 4*(*piCount)/numOfTosses);

   // 回收互斥鎖
   pthread_mutex_destroy(&mutexsum);
   // 離開
   pthread_exit(NULL);
}