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
   double *pi;
   int numOfTosses;
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
   int numOfTosses=data->numOfTosses;
   double *pi = data->pi;

   // 將原本的 PI 算法切成多份
   double x;
   double local_pi = 0;
   double step = 1.0 / numOfTosses;
   for (int i = start; i < end; i++)
   {
      x = (i + 0.5) * step;
      local_pi += 4 / (1 + x * x);
   }

   local_pi *= step;

   // **** 關鍵區域 ****
   // 一次只允許一個 thread 存取
   pthread_mutex_lock(&mutexsum);
   // 將部分的 PI 加進最後的 PI
   *pi += local_pi;
   pthread_mutex_unlock(&mutexsum);

   pthread_exit((void *)0);
}


int main(int argc, char** argv)
{
   int numOf_t = atoi(argv[1]);
   int numOfTosses = atoi(argv[2]);


   pthread_t callThd[numOf_t]; // 宣告建立 pthread
   // 初始化互斥鎖
   pthread_mutex_init(&mutexsum, NULL);

   // 設定 pthread 性質是要能 join
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   // 每個 thread 都可以存取的 PI
   // 因為不同 thread 都要能存取，故用指標
   double *pi = malloc(sizeof(*pi));
   *pi = 0;

   int part = numOfTosses / numOf_t;

   Arg arg[numOf_t]; // 每個 thread 傳入的參數
   for (int i = 0; i < numOf_t; i++)
   {
      // 設定傳入參數
      arg[i].thread_id = i;
      arg[i].start = part * i;
      arg[i].end = part * (i + 1);
      arg[i].pi = pi; // PI 的指標，所有 thread 共用
      arg[i].numOfTosses=numOfTosses;
      // 建立一個 thread，執行 count_pi 任務，傳入 arg[i] 指標參數
      pthread_create(&callThd[i], &attr, count_pi, (void *)&arg[i]);
   }

   // 回收性質設定
   pthread_attr_destroy(&attr);

   void *status;
   for (int i = 0; i < numOf_t; i++)
   {
      // 等待每一個 thread 執行完畢
      pthread_join(callThd[i], &status);
   }

   // 所有 thread 執行完畢，印出 PI
   printf("%.10lf \n", *pi);

   // 回收互斥鎖
   pthread_mutex_destroy(&mutexsum);
   // 離開
   pthread_exit(NULL);
}