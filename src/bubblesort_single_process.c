/*classic bubblesort algorithm utilizing a singular process.
This algorithm will be used in testing, and will serve as
a control to compare to our multiprocess bubblesort implementation.*/

#include <stdio.h>

void bubblesort(int array[], int index);
void swap(int *one, int *two);

int main(){
  int i;
  int unsorted[10] = {8, 4, 9, 6, 3, 1, 2, 7, 5, 0};
  int length = sizeof(unsorted)/sizeof(int);
  printf("List Before Sorting\n");
  for(i = 0; i < length; i++){
    printf("%d", unsorted[i]);
  }

  bubblesort(unsorted, length);

  printf("\nList After Sorting\n");
  for(i = 0; i < length; i++){
    printf("%d", unsorted[i]);
  }
  printf("\n");
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
