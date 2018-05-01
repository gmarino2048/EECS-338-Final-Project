# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

int stop;

int reset;

int completed;

int sorted = 0;

pthread_t *pthreads;
pthread_attr_t *attributes;

sem_t srmutex;
sem_t stopmutex;
sem_t scmutex;

struct Args {
  int *arr;
  int position;
  int size;
};

int *randomArray (long size);
void bubblesort(int *arr, int threads, int size);
void *bubble (void *args);
void swap(int *arr, int i, int j);


int main (int argc, char* argv[]) {

  //Initialize the semaphores
  if (sem_init(&srmutex, 0, 1) < 0){
    printf ("Could not initialize semaphore\n");
    exit(-1);
  }
  if (sem_init(&stopmutex, 0, 1) < 0){
    printf ("Could not initialize semaphore\n");
    exit(-1);
  }
  if (sem_init(&scmutex, 0, 1) < 0){
    printf ("Could not initialize semaphore\n");
    exit(-1);
  }

  struct timeval start_time, stop_time, elapsed_time;

  for (int threads = 1; threads < 128; threads = threads *2){
    for (int size = 1; size < 2048; size = size *2){
      int *arr = randomArray(size);

      gettimeofday(&start_time,NULL);
      bubblesort(arr, threads, size);
      gettimeofday(&stop_time,NULL);

      timersub(&stop_time, &start_time, &elapsed_time);
      printf("%d,%d,%f\n", threads, size, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
    }
  }

  sem_destroy(&srmutex);
  sem_destroy(&scmutex);
  sem_destroy(&stopmutex);
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

// A function to implement bubble sort
// This method is not yet complete
void bubblesort(int *arr, int threads, int size){
   // Calculate out the number of bubbles to use
   int maxThreads = (size - 1) / 2;

   int actualThreads;
   // Take the minimum of the two
   if (maxThreads < threads){
     actualThreads = maxThreads;
   }
   else {
     actualThreads = threads;
   }

   if (actualThreads == 0){
     return;
   }

   // Initialize global variables
   stop = 0;
   reset = 0;
   completed = 0;
   // Allocate the memory
   pthreads = malloc(actualThreads * sizeof(pthread_t));
   attributes = malloc(actualThreads * sizeof(pthread_attr_t));

   struct Args argsList[actualThreads];

   // Instantiate the pthreads
   for (int i = 0; i < actualThreads; i++) {
     argsList[i].arr = arr;
     argsList[i].position = i * 2;
     argsList[i].size = size;
     pthread_create(&pthreads[i], &attributes[i], bubble, (void *) &argsList[i]);
   }

   // Bubble Controller
   sem_wait(&stopmutex);
   int thisStop = stop;
   sem_post(&stopmutex);

   while (thisStop == 0){
     int haveCompleted = 0;

     // Wait for all children to complete
     while (haveCompleted < actualThreads && thisStop != 1){
       sem_wait(&scmutex);
       haveCompleted = completed;
       sem_post(&scmutex);

       sem_wait(&stopmutex);
       thisStop = stop;
       sem_post(&stopmutex);
     }

     sem_wait(&scmutex);
     completed = 0;
     sem_post(&scmutex);

     sem_wait(&srmutex);
     reset = !reset;
     sem_post(&srmutex);

     sem_wait(&stopmutex);
     thisStop = stop;
     sem_post(&stopmutex);
   }

   for (int i = 0; i < actualThreads; i++) {
     pthread_join(pthreads[i], NULL);
   }

   free(pthreads);
   free(attributes);
}

// This method has yet to be implemented
void *bubble (void *arguments){
  struct Args args = *((struct Args *) arguments);

  int streak;
  int thisStop;

  sem_wait(&stopmutex);
  thisStop = stop;
  sem_post(&stopmutex);

  while (thisStop == 0){

    // Swap this one and the one above it
    if (args.arr[args.position] > args.arr[args.position + 1]){
      swap(args.arr, args.position, args.position + 1);
      streak = 0;
    }
    else {
      streak ++;
    }

    // Increment or wrap around
    if (args.position < args.size - 2){
      args.position ++;
    }
    else {
      args.position = 0;
    }

    // Check the streak
    if (streak == args.size - 1){
      sem_wait(&stopmutex);
      stop = 1;
      sem_post(&stopmutex);
    }

    // Replace thisStop
    sem_wait(&stopmutex);
    thisStop = stop;
    sem_post(&stopmutex);


    // Wait for controller to increment
    sem_wait(&srmutex);
    int wait = reset;
    int currentVal = reset;
    sem_post(&srmutex);

    // Increment completed
    sem_wait(&scmutex);
    completed ++;
    sem_post(&scmutex);

    // Wait for wait to not equal currentVal
    while (wait == currentVal && thisStop != 1){
      sem_wait(&srmutex);
      wait = reset;
      sem_post(&srmutex);
    }
  }
  pthread_exit(NULL);
}

void swap (int *arr, int index1, int index2){
  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}
