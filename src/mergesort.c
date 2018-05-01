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

sem_t mutex;

struct Args{
  int *arr;
  int start;
  int stop;
};

void mergesort(int *arr, int threads, int size);
void *mergesort_setup(void *arguments);
void merge(int *arr, int start, int middle, int stop);

void mergesort(int *arr, int threads, int size){
  if (threads == 0){
    printf("Cannot run on 0 threads\n");
    exit(-1);
  }

  threadCount = 0;
  MAX_THREADS = threads;

  pthread_t tempThreads[threads];
  pthread_attr_t tempAttributes[threads];

  pthreads = malloc(sizeof(tempThreads));
  attributes = malloc(sizeof(tempAttributes));

  if (sem_init(&mutex, 0, 1) < 0){
    printf ("Could not initialize semaphore\n");
    exit(-1);
  }

  struct Args initial;

  initial.arr = arr;
  initial.start = 0;
  initial.stop = size - 1;

  if (pthread_create(&pthreads[0], &attributes[0], mergesort_setup, (void *) &initial) < 0){
    printf("Could not create thread\n");
    exit(-1);
  }

  printf ("Thread Created with tid %ld\n", pthreads[0]);

  pthread_join(pthreads[0], NULL);

  free (pthreads);
  free (attributes);
}

void *mergesort_setup (void *arguments){

  struct Args args = *((struct Args *) arguments);

  if (args.start < args.stop){
    int split = (args.start + (args.stop - 1)) / 2;

    sem_wait(&mutex);
    if (threadCount < (MAX_THREADS - 1)){
      threadCount++;
      int tempCount = threadCount;
      sem_post(&mutex);

      struct Args right = {args.arr, split + 1, args.stop};
      if (pthread_create(&pthreads[tempCount], &attributes[tempCount], mergesort_setup, &right) < 0){
        printf("Could not create pthread at section %d\n", tempCount);
        exit(-1);
      }
      printf("Thread Created\n");

      struct Args left = {args.arr, args.start, split};
      mergesort_setup(&left);

      pthread_join(pthreads[tempCount], NULL);

      printf("Running Merge\n");
      merge(args.arr, args.start, split, args.stop);
    }
    else {
      sem_post(&mutex);

      struct Args left = {args.arr, args.start, split};
      mergesort_setup(&left);

      struct Args right = {args.arr, split + 1, args.stop};
      mergesort_setup(&right);

      printf("Running Merge\n");
      merge(args.arr, args.start, split, args.stop);
    }
  }
  return 0;
}

void merge(int *arr, int start, int middle, int stop)
{
    int i, j, k;
    int left = middle - start + 1;
    int right =  stop - middle;

    int L[left], R[right];

    for (i = 0; i < left; i++)
        L[i] = arr[start + i];
    for (j = 0; j < right; j++)
        R[j] = arr[middle + 1+ j];


    i = 0;
    j = 0;
    k = start;
    while (i < left && j < right){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < left){
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < right)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
