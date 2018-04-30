# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>

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

void bubblesort(int *arr, int threads, int size);
void *bubble (void *args);
void swap(int *arr, int i, int j);

int main() {
  int unsorted[10] = {8, 4, 9, 6, 3, 1, 2, 7, 5, 0};

  bubblesort(unsorted, 3, 10);

  for (int i = 0; i < 10; i++){
    printf("%d\t", unsorted[i]);
  }
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

   // Initialize global variables
   stop = 0;
   reset = 0;
   completed = 0;

   //Initialize the semaphores
   if (sem_init(&srmutex, 0, 1) < 0){
     printf ("Could not initialize semaphore\n");
     exit(-1);
   }
   if (sem_init(&stopmutex, 0, 1) < 0){
     printf ("Could not initialize semaphore\n");
     exit(-1);
   }
   if (sem_init(&srmutex, 0, 1) < 0){
     printf ("Could not initialize semaphore\n");
     exit(-1);
   }
   if (sem_init(&scmutex, 0, 1) < 0){
     printf ("Could not initialize semaphore\n");
     exit(-1);
   }

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
   sem_wait(&srmutex);
   int thisStop = stop;
   sem_post(&srmutex);

   while (thisStop == 0){
     int haveCompleted = 0;

     // Wait for all children to complete
     while (haveCompleted < actualThreads && thisStop != 1){
       sem_wait(&scmutex);
       haveCompleted = completed;
       sem_post(&scmutex);

       sem_wait(&srmutex);
       thisStop = stop;
       sem_post(&srmutex);
     }

     sem_wait(&scmutex);
     completed = 0;
     sem_post(&scmutex);

     printf ("Resetting bubbles\n");

     sem_wait(&srmutex);
     reset = !reset;
     sem_post(&srmutex);

     sem_wait(&srmutex);
     thisStop = stop;
     sem_post(&srmutex);
   }

   for (int i = 0; i < actualThreads; i++) {
     pthread_join(pthreads[i], NULL);
   }
}

// This method has yet to be implemented
void *bubble (void *arguments){
  struct Args args = *((struct Args *) arguments);

  int streak;
  int thisStop;

  sem_wait(&srmutex);
  thisStop = stop;
  sem_post(&srmutex);

  while (thisStop == 0){

    // Swap this one and the one above it
    if (args.arr[args.position] > args.arr[args.position + 1]){
      swap(args.arr, args.position, args.position + 1);
      streak = 0;
    }
    else {
      streak ++;
    }
    printf("Finished swapping. Streak is: %d\n", streak);

    // Increment or wrap around
    if (args.position < args.size - 2){
      args.position ++;
    }
    else {
      args.position = 0;
    }
    printf("Finished incrementing. Current position is: %d\n", args.position);

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
    while (wait == currentVal){
      sem_wait(&srmutex);
      wait = reset;
      sem_post(&srmutex);
    }
  }
  pthread_exit(NULL);
}


// Swaps the two elements at positions i and j in the array
void swap (int *arr,int i, int j) {
  int temp = arr[j];
  arr[j] = arr[i];
  arr[i] = temp;
}
