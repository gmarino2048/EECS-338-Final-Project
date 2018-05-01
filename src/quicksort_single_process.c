/*classic quicksort algorithm utilizing a singular process.
This algorithm will be used in testing, and will serve as
a control to compare to our multiprocess quicksort implementation.*/

# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

void quicksort(int array[], int lowIndex, int highIndex);
int partition(int array[], int lowIndex, int highIndex);
int swap(int *one, int *two);
int *randomArray(int size);

int main(int argc, char* argv[]){
  struct timeval start_time, stop_time, elapsed_time;
  int i;
  for(i = 1; i < 5000000; i = i * 2){
    int *unsorted =  randomArray(i);
    int temp[i];
    gettimeofday(&start_time,NULL);
    quicksort(unsorted, 0, (i - 1));
    gettimeofday(&stop_time,NULL);

    timersub(&stop_time, &start_time, &elapsed_time);
    printf("N = %d, Time = %f\n", i, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
  }
}

void quicksort(int array[], int lowIndex, int highIndex){
  if(lowIndex < highIndex){
    int i = partition(array, lowIndex, highIndex);
    quicksort(array, lowIndex, i - 1);
    quicksort(array, i + 1, highIndex);
  }
}

int partition(int array[], int lowIndex, int highIndex){
  int pivot = array[highIndex];
  int i = (lowIndex - 1);

  for(int j = lowIndex; j <= highIndex - 1; j++){
    if(array[j] <= pivot){
      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[highIndex]);
  return (i + 1);
}

int swap(int *one, int *two){
  int temp = *one;
  *one = *two;
  *two = temp;
}


int *randomArray (int size){
  int *arr = malloc(size * sizeof(int));
  srand(time(0));

  for (int i = 0; i < size; i++){
    int num = (rand() % INT_MAX);
    arr[i] = num;
  }

  return arr;
}
