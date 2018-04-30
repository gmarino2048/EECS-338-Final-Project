/* Noah Houpt and Guy Marino EECS 338 Final Project
QuickSort implementation for testing various lengths of array
inputs and number of pthreads in use. Source of merge sort
algorithm is from mycodeschool's Github at URL:
https://gist.github.com/mycodeschool/9678029 */

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

int threadCount;
int MAX_THREADS;

pthread_t *pthreads;
pthread_attr_t *attributes;

struct Args{
  int *arr;
  int start;
  int stop;
}

void mergesort(int *arr, int threads, int size);
void mergesort_setup(void *arguments);
void merge(int *A, int *L, int leftCount, int *R, int rightCount);

int main(){
  int unsorted[10] = {8, 4, 9, 6, 3, 1, 2, 7, 5, 0};

  mergesort(unsorted, 3, 10);

  for(int i = 0; i < 10; i++){
    printf("%d\t", unsorted[i]);
  }
}

void mergesort(int *arr, int threads, int size){
  if(threads == 0){
    printf("Cannot run on 0 threads\n", stderr);
    exit(-1);
  }

  threadCount = 0;
  MAX_THREADS = threads;

  pthread_t tempThreads[threads];
  pthread_attr_t tempAttributes[threads];

  pthreads = tempThreads;
  attributes = tempAttributes;

  if(sem_init(&mutex, 1, 1) < 0){
    printf("Could not initialize semaphore", stderr);
    exit(-1);
  }

  struct Args initial;

  initial.arr = arr;
  initial.start = 0;
  initial.stop = size;

  pthread_create(&pthreads[0], &attributes[0], quicksort_setup, (void *) &initial);
}

void *quicksort_setup(void *arguments){
  struct Args args = *((struct Args *) arguments);


}
