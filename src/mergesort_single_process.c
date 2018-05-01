/*classic mergesort algorithm utilizing a singular process.
This algorithm will be used in testing, and will serve as
a control to compare to our multiprocess mergesort implementation.*/

# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

void sort(int array[], int temp[], int low, int high);
void merge(int array[], int temp[], int low, int mid, int high);
int *randomArray(int size);


int main(){
  struct timeval start_time, stop_time, elapsed_time;
  int i;
  for(i = 1; i < 5000000; i = i * 2){
    int *unsorted =  randomArray(i);
    int temp[i];
    gettimeofday(&start_time,NULL);
    sort(unsorted, temp, 0, (i - 1));
    gettimeofday(&stop_time,NULL);

    timersub(&stop_time, &start_time, &elapsed_time);
    printf("N = %d, Time = %f\n", i, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
  }
}

void sort(int array[], int temp[], int low, int high){
  int mid;

  if(low < high){
    int middle = low + (high - low) / 2;
    sort(array, temp, low, middle);
    sort(array, temp, middle + 1, high);
    merge(array, temp,  low, middle, high);
  }
  else
    return;
}

void merge(int array[], int temp[], int low, int mid, int high){
  int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(array[l1] <= array[l2])
         temp[i] = array[l1++];
      else
         temp[i] = array[l2++];
   }

   while(l1 <= mid)
      temp[i++] = array[l1++];

   while(l2 <= high)
      temp[i++] = array[l2++];

   for(i = low; i <= high; i++)
      array[i] = temp[i];
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
