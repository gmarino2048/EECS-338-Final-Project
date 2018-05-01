
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <time.h>
# include <pthread.h>
# include <limits.h>

int threadCount;
int MAX_THREADS;

pthread_t *pthreads;
pthread_attr_t *attributes;

sem_t mutex;

struct Args {
  int *arr;
  long start;
  long stop;
};

int *randomArray (long size);
void quicksort(int *arr, int threads, long size);
void *quicksort_setup(void *arguments);
int partition(int *arr, long start, long stop);
void swap(int *arr, long index1, long index2);

int main (int argc, char* argv[]) {

  if (sem_init(&mutex, 0, 1) < 0){
    printf ("Could not initialize semaphore\n");
    exit(-1);
  }

  struct timeval start_time, stop_time, elapsed_time;

  for (int threads = 1; threads < 128; threads = threads *2){
    for (int size = 1; size < 100000000; size = size *2){
      int *arr = randomArray(size);

      gettimeofday(&start_time,NULL);
      quicksort(arr, threads, size);
      gettimeofday(&stop_time,NULL);

      timersub(&stop_time, &start_time, &elapsed_time);
      printf("%d,%d,%f\n", threads, size, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
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

void quicksort(int *arr, int threads, int size){
  if (threads == 0){
    printf("Cannot run on 0 threads\n");
    exit(-1);
  }

  threadCount = 0;
  MAX_THREADS = threads;

  pthreads = malloc(threads * sizeof(pthread_t));
  attributes = malloc(threads * sizeof(pthread_attr_t));

  struct Args initial;

  initial.arr = arr;
  initial.start = 0;
  initial.stop = size;

  if (pthread_create(&pthreads[0], &attributes[0], quicksort_setup, (void *) &initial) < 0){
    printf("Could not create thread\n");
    exit(-1);
  }

  pthread_join(pthreads[0], NULL);

  printf("finished\n");

  free (pthreads);
  free (attributes);
}


void *quicksort_setup (void *arguments){

  struct Args args = *((struct Args *) arguments);

  if (args.start < (args.stop - 1)){

    long pivot = partition(args.arr, args.start, args.stop);

    sem_wait(&mutex);
    if (threadCount < (MAX_THREADS - 1)){
      threadCount++;
      int tempCount = threadCount;
      sem_post(&mutex);

      struct Args right = {args.arr, pivot, args.stop};
      if (pthread_create(&pthreads[tempCount], &attributes[tempCount], quicksort_setup, &right) < 0){
        printf("Could not create pthread at section %d\n", tempCount);
        exit(-1);
      }

      struct Args left = {args.arr, args.start, pivot};
      quicksort_setup(&left);

      pthread_join(pthreads[tempCount], NULL);
    }
    else {
      sem_post(&mutex);

      struct Args left = {args.arr, args.start, pivot};
      quicksort_setup(&left);

      struct Args right = {args.arr, pivot, args.stop};
      quicksort_setup(&right);
    }
  }
  return 0;
}

int partition (int *arr, int start, int stop){
 // Partition a sublist of arr using the start and stop indices
 int low = start;
 int high = stop - 1;

 int pivot = arr[high];

 int i = low - 1;

 for (int j = low; j < high; j++){
   if (arr[j] < pivot){
     i = i + 1;
     swap(arr, i, j);
   }
 }

 swap(arr, i + 1, high);
 return i + 1;
}

void swap (int *arr, int index1, int index2){
  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}
