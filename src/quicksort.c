
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

int threadCount
int MAX_THREADS;

pthread_t *pthreads;
pthread_attr *attributes;

sem_t mutex;

struct Args {
  int arr;
  int start;
  int stop;
};

void *quicksort_setup(void *args);
int partition(int arr[], int start, int stop);
void swap(int arr[], int index1, int index2);

int *quicksort(int *arr, int threads, int size){
  if (maxThreads == 0){
    printf("Cannot run on 0 threads\n", stderr);
    exit(-1);
  }
  threadCount = 0;
  MAX_THREADS = maxThreads;

  pthread_t tempThreads[maxThreads];
  pthread_attr tempAttributes[maxThreads];

  pthreads = tempThreads;
  attributes = tempAttributes;

  if (sem_init(&mutex, 1, 1) < 0){
    printf ("Could not initialize semaphore", stderr);
    exit(-1);
  }

  struct Args initial;

  initial.arr = arr;
  initial.start = 0;
  initial.stop = size;

  pthread_create(pthreads[0], attributes[0], quicksort_setup, (void *)initial);
}

void *quicksort_setup (void *args){
  struct Args arguments = (struct Args *) args;

  if (args.start < (args.stop - 1)){
    int pivot = partition(args.arr, args.start, args.stop);

    sem_wait(&mutex);
    if (threadCount < (maxThreads - 1)){
      threadCount++;

      struct Args right = {args.arr, pivot, args.stop};
      pthread_create(pthreads[threadCount])

      sem_post(&mutex);

      struct Args left = {args.arr, args.start, pivot};
      *quicksort_setup((void *)left);
    }
    else {
      sem_post(&mutex);

      struct Args left = {args.arr, args.start, pivot};
      *quicksort_setup((void *)left);

      struct Args right = {args.arr, pivot, args.stop};
      *quicksort_setup((void *)right);
    }
  }
}

int partition (int *arr, int start, int stop){
 // Partition a sublist of arr using the start and stop indices
 int low = start;
 int high = stop - 1;

 int pivot = arr[high];

 int i = low - 1;

 for (int j = low; j < high; j++){
   if (arr[j] < pivot){
     i++;
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
