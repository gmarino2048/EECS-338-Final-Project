/*Noah Houpt and Guy Marino's Algorithm for
Bubblesort. Inspired by the algorithm available
at URL : https://www.geeksforgeeks.org/bubble-sort*/

#include <stdio.h>
 
// A function to implement bubble sort
void bubbleSort(int arr[], int n){
   int i, j;
   for (i = 0; i < n-1; i++){    
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++){
           if (arr[j] > arr[j+1]){
              swap(&arr[j], &arr[j+1]);
			  int temp = arr[j];
			  arr[j] = arr[j+1];
			  arr[j+1] = temp;
		   }
		}
   }	
}
 
// Driver program to test above functions
int main()
{
    return 0;
}