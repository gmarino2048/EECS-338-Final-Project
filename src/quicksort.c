
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>

int threadCount;
int MAX_THREADS;

pthread_t *pthreads;
pthread_attr_t *attributes;

sem_t mutex;

struct Args {
  int *arr;
  int start;
  int stop;
};

void quicksort(int *arr, int threads, int size);
void *quicksort_setup(void *arguments);
int partition(int arr[], int start, int stop);
void swap(int arr[], int index1, int index2);

int main() {
  int unsorted[10] = {8, 4, 9, 6, 3, 1, 2, 7, 5, 0};

  quicksort(unsorted, 3, 10);

  for (int i = 0; i < 10; i++){
    printf("%d\t", unsorted[i]);
  }
}

void quicksort(int *arr, int threads, int size){
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
  initial.stop = size;

  if (pthread_create(&pthreads[0], &attributes[0], quicksort_setup, (void *) &initial) < 0){
    printf("Could not create thread\n");
    exit(-1);
  }

  printf ("Thread Created with tid %ld\n", pthreads[0]);

  pthread_join(pthreads[0], NULL);

  free (pthreads);
  free (attributes);
}


void *quicksort_setup (void *arguments){
  fflush(stdout);

  struct Args args = *((struct Args *) arguments);

  if (args.start < (args.stop - 1)){
    int pivot = partition(args.arr, args.start, args.stop);

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
  printf ("%d\t%d\n", arr[index1], arr[index2]);

  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;

  printf ("%d\t%d\n", arr[index1], arr[index2]);
}
