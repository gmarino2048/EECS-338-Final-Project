/*classic bubblesort algorithm utilizing a singular process.
This algorithm will be used in testing, and will serve as
a control to compare to our multiprocess bubblesort implementation.*/

# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

void bubblesort(int array[], int index);
void swap(int *one, int *two);
int *randomArray(int size);

int main(){
  struct timeval start_time, stop_time, elapsed_time;
  int i;
  for(i = 1; i < 5000000; i = i * 2){
    int *unsorted =  randomArray(i);
    gettimeofday(&start_time,NULL);
    bubblesort(unsorted, i);
    gettimeofday(&stop_time,NULL);

    timersub(&stop_time, &start_time, &elapsed_time);
    printf("N = %d, Time = %f\n", i, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
  }
}

void bubblesort(int array[], int index){
  int i, j;
  for(i = 0; i < index - 1; i++){
    for(j = 0; j < index - i - 1; j++){
      if(array[j] > array[j + 1]){
        swap(&array[j], &array[j + 1]);
      }
    }
  }
}

void swap(int *one, int *two){
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
