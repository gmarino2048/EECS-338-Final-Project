/*classic quicksort algorithm utilizing a singular process.
This algorithm will be used in testing, and will serve as
a control to compare to our multiprocess quicksort implementation.*/

#include <stdio.h>

void quicksort(int array[], int lowIndex, int highIndex);
int partition(int array[], int lowIndex, int highIndex);
int swap(int *one, int *two);

int main(){
  int i;
  int unsorted[10] = {8, 4, 9, 6, 3, 1, 2, 7, 5, 0};
  int length = sizeof(unsorted)/sizeof(int);
  printf("List Before Sorting\n");
  for(i = 0; i < length; i++){
    printf("%d", unsorted[i]);
  }

  quicksort(unsorted, 0, (length - 1));

  printf("\nList After Sorting\n");
  for(i = 0; i < length; i++){
    printf("%d", unsorted[i]);
  }
  printf("\n");
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
