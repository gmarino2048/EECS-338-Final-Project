
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

int index;
int MAX_THREADS;
sem_t semaphore;

struct params {
  pthread_t pthreads[];
  pthread_attr attributes[];
  int list[];
  int start;
  int stop;
};

void swap (int list[], int index1, int index2);


int quicksort_setup (int list[], int maxThreads){
  if (maxThreads == 0){
    printf("Cannot run on 0 threads\n", stderr);
    return -1;
  }

  MAX_THREADS = maxThreads;

  if (sem_init(&semaphore, 0, 1) != 0){
    printf("Failed to instantiate semaphore\n", stderr);
    return -1;
  }

  pthread_t pthreads[maxThreads];
  pthread_attr attributes[maxThreads];


}
