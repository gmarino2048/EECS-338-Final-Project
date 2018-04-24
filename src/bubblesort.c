/*Noah Houpt and Guy Marino's Algorithm for
Bubblesort. Inspired by the algorithm available
at URL : https://www.geeksforgeeks.org/bubble-sort*/

#include <stdio.h>

int size;

void swap(int i, int j);

// A function to implement bubble sort
// This method is not yet complete
void bubbleSort(int arr[], int n){
   int i, j;
   size = n;
   for (i = 0; i < n-1; i++){
       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++){
           if (arr[j] > arr[j+1]){
              swap(j, j+1);
			  int temp = arr[j];
			  arr[j] = arr[j+1];
			  arr[j+1] = temp;
		   }
		}
   }
}

// This method has yet to be implemented
void *bubble (void *args){

}


// Swaps the two elements at positions i and j in the array
void swap (int arr[],int i, int j) {
  if (i < j && i >= 0 && j<size){
    int temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
  }
}

// Driver program to test above functions
int main()
{
    return 0;
}
