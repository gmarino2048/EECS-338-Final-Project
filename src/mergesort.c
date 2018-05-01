/* Noah Houpt and Guy Marino EECS 338 Final Project
QuickSort implementation for testing various lengths of array
inputs and number of pthreads in use. Source of merge sort
algorithm is from mycodeschool's Github at URL:
https://gist.github.com/mycodeschool/9678029 */

# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

//gcc mergesort.c -o mergesort -lpthread -Wall -DTRACE --std=c99 -D_BSD_SOURCE -lrt

int threadCount;
int MAX_THREADS;

//pthread_t *pthreads;
//pthread_attr_t *attributes;

sem_t mutex;

struct Args{
  int *arr;
  long start;
  long stop;
};

int *randomArray (long size);
void mergesort(int *arr, int threads, long size);
void *mergesort_setup(void *arguments);
void merge(int *arr, long start, long middle, long stop);



int main (int argc, char* argv[]) {

  if (sem_init(&mutex, 0, 1) < 0){
    printf ("Could not initialize semaphore\n");
    exit(-1);
  }

  struct timeval start_time, stop_time, elapsed_time;

  for (int threads = 1; threads < 128; threads = threads *2){
    for (long size = 1; size < 100000000; size = size *2){
      int *arr = randomArray(size);

      gettimeofday(&start_time,NULL);
      mergesort(arr, threads, size);
      gettimeofday(&stop_time,NULL);

      timersub(&stop_time, &start_time, &elapsed_time);
      printf("%d,%ld,%f\n", threads, size, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
    }
  }

  sem_destroy(&mutex);
}

int *randomArray (long size){
  int *arr = malloc(size * sizeof(int));
  srand(time(0));

  for (long i = 0; i < size; i++){
    int num = (rand() % INT_MAX);
    arr[i] = num;
  }

  return arr;
}

void mergesort(int *arr, int threads, long size){
  if (threads == 0){
    printf("Cannot run on 0 threads\n");
    exit(-1);
  }

  threadCount = 1;
  MAX_THREADS = threads;

  pthread_t parent;
  /*pthreads = malloc(threads * sizeof(pthread_t));
  attributes = malloc(threads * sizeof(pthread_attr_t));*/

  struct Args initial;

  initial.arr = arr;
  initial.start = 0;
  initial.stop = size - 1;

  if (pthread_create(&parent, NULL, mergesort_setup, (void *) &initial) < 0){
    printf("Could not create thread\n");
    exit(-1);
  }

  pthread_join(parent, NULL);

  /*free (pthreads);
  free (attributes);*/
}

void *mergesort_setup (void *arguments){

  struct Args args = *((struct Args *) arguments);

  if (args.start < args.stop){
    int split = (args.start + (args.stop - 1)) / 2;
    pthread_t myid;
    sem_wait(&mutex);
    if (threadCount < MAX_THREADS){
      int tempCount = threadCount++;
      sem_post(&mutex);

      struct Args right = {args.arr, split + 1, args.stop};
      if (pthread_create(&myid, NULL, mergesort_setup, &right) < 0){
        printf("Could not create pthread at section %d\n", tempCount);
        exit(-1);
      }

      struct Args left = {args.arr, args.start, split};
      mergesort_setup(&left);

      pthread_join(myid, NULL);

      merge(args.arr, args.start, split, args.stop);
    }
    else {
      sem_post(&mutex);

      struct Args left = {args.arr, args.start, split};
      mergesort_setup(&left);

      struct Args right = {args.arr, split + 1, args.stop};
      mergesort_setup(&right);

      merge(args.arr, args.start, split, args.stop);
    }
  }
  return 0;
}

void merge(int *arr, long start, long middle, long stop)
{
    long i, j, k;
    long left = middle - start + 1;
    long right =  stop - middle;

    int *L = malloc(left * sizeof (int));
    int *R = malloc(right * sizeof(int));

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
    free(L);
    free(R);
}
