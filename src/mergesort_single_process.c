/*classic mergesort algorithm utilizing a singular process.
This algorithm will be used in testing, and will serve as
a control to compare to our multiprocess mergesort implementation.*/

#include <stdio.h>

void sort(int array[], int temp[], int low, int high);
void merge(int array[], int temp[], int low, int mid, int high);


int main(){
  int i;
  int unsorted[10] = {8, 4, 9, 6, 3, 1, 2, 7, 5, 0};
  int length = sizeof(unsorted)/sizeof(int);
  int temp[length + 1];
  printf("List Before Sorting\n");
  for(i = 0; i < length; i++){
    printf("%d", unsorted[i]);
  }

  sort(unsorted, temp, 0, (length - 1));

  printf("\nList After Sorting\n");
  for(i = 0; i < length; i++){
    printf("%d", unsorted[i]);
  }
  printf("\n");
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
