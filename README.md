# EECS-338-Final-Project

## Summary of Files

### Makefile

The makefile is responsible for compiling all of the files and merging them together. The makefile first compiles all of the c programs into .o files and then stitches them together at the end. The results of the experiment we conducted is in the out file of the zip that was downloaded. There is one csv file per c file.

### mergesort.c

Merge Sort of the list works in such a way that every time the algorithm splits the list, it creates a new child process to sort the second half of the split list while the parent finishes sorting the first half. For a better depiction, see the diagram below:

![Merge Sort](images/mergesort.png)

This method will allow thread reuse while also ensuring that there is a maximal cover of threads for each part of the list. At the end of each sorting cycle, the parent will wait for the child thread to terminate and will merge the two parts of the sorted list back together.


##### Summary of Functions

`void mergesort(int *arr, long threads, long size)`

This function will mergesort the list using the function `mergesort_helper`. This function is a wrapper funciton based designed to sort the entire array. A long is passed for the threads and size arguments to avoid segmentation faults. 

`void *mergesort_helper(void *arguments)`

This function will be called by each child thread and will be responsible for splitting each half and then merging the two halves together using `merge`. The `mergesort_helper` function will see if it can instantiate a new thread, if it can it will add the thread to the array of threads and call `mergesort_helper` on the first part of the list while the child thread sorts the other.

`void merge(int *arr, long start, long middle, long stop)`

The merge function merges the lists from first to second, and then from second to stop. The merge function assumes that both lists are already sorted, and goes through each part of the list comparing the least significant elements until it has completed merging the list. The resulting list should then be sorted. Longs are passed for the 2nd, 3rd, and 4th arguments to avoid segmentation faults.

`int *randomArray (long size)`

Method used to create an array of size `size` filled with random values between 0 and 2147483647. This method is used for testing.

`int main(int argc, char* argv[])`

Main method will test the file when executed and output number of threads, size of array, and time taken to sort. It will do this for threads between 1 and 128, incremented by thread_count * 2, and array sizes between 1 and 100000000, incremented by arraySize * 2.

##### Summary of Data Types

Since the function operates separately on different parts of the array, semaphores are unnecessary. Instead, we will be using an array of pthread tid's and an array of pthread attribute structs to operate on separate parts of the array.

The threads themselves will be allocated in such a way that no two threads will be able to operate on the same elements of the list at a time, to ensure that the entire operation is thread safe. Any global variables used in the merge sort methods (save the array) will be wrapped in a semaphore to ensure that the entire process is thread safe.

The only additional data type will be the struct used to pass information from the functions to the `mergesort_helper` function. This struct will include the start and end values of the array to be sorted, and will enable child processes to know which area of the list to sort.

##### Sample Output

1,1,0.000202
1,2,0.000161
1,4,0.000151
1,8,0.000159
1,16,0.000160
1,32,0.000152
1,64,0.000148
1,128,0.000059
1,256,0.000087
1,512,0.000125
1,1024,0.000265
1,2048,0.000450
1,4096,0.000656
1,8192,0.001443
1,16384,0.002779

### bubblesort.c

This algorithm acts as a modified version of bubblesort. Instead of having one bubble move up the list continuously, this function will have multiple threads that do comparisons and swapping at once. These individual 'bubbles' will move up the list one after another, and will be cycled back to the beginning once they reach the end of the list.

This algorithm has several advantages over traditional bubble sort, since the algorithm runs multiple bubbles at once, it should divide the work needed to be done by the algorithm by a factor of the number of active threads.

Due to limited space on the list, however, the maximum number of threads which can be in use at one time is the number of elements in the list divided by two.

##### Summary of functions

`int[] bubblesort (int *arr, int threads, int size)`

This function will be a wrapper function which will allow the bubble sort method to be called quickly and easily from the main script. This function will also be responsible for calculating the thread requirements for each list and instantiating that many threads.

`void *bubble (void *args)`

This function will be run by each individual thread. The bubble function will be responsible for comparing and swapping values, as well as waiting until all threads have completed before incrementing its thread's position in the list.

`void swap (int *arr, int i, int j)`

This function's sole responsibility is to swap the values at index1 and index2 in the array. Using these three functions, we can implement a version of bubblesort which uses multiple threads to decrease the amount of work that needs to be done.

`int *randomArray (long size)`

Method used to create an array of size `size` filled with random values between 0 and 2147483647. This method is used for testing.

`int main (int argc, char* argv[])`

Method used to test various values of NUM_THREADS and array size. Will test threads between 1 and 128 and increments by threads * 2. Will test array sizes between 1 and 2500 and increments by size *2. 

##### Summary of Data Types

To prevent two of the bubbles from colliding with each other, there will be a global flag which notifies each bubble when to increment value and swap. This will keep the bubbles from attempting to modify the same values at a time, and should yield faster results than other solutions such as maintaining a list of all bubble positions. This allows each bubble to increment itself, instead of incrementing the position of each bubble separately.

There will also be a global count which will show how many active threads have been completed. This variable will be the trigger for each of the active threads to increment once it reaches the total number of threads. This variable must be controlled by a semaphore.

The program must also contain a flag which notifies the program once the list has been sorted. This flag will either be 0 or 1, and will change value after a thread reaches the end of the function without having to perform any swaps.

Since we are incrementing each thread's position at the same time, we do not need to surround each element with semaphores, as the threads will be kept from ever interacting with the same values at the same time. This will allow us to keep the memory cost of this implementation low, while also maintaining its thread safety.

##### Sample Output

1,1,0.000000
1,2,0.000001
1,4,0.005199
1,8,0.000293
1,16,0.001427
1,32,0.002988
1,64,0.012255
1,128,0.052896
1,256,0.203736
1,512,0.889829
1,1024,3.605456

### quicksort.c

Quick sort of the list works in a way such that after every partition is created, a new child thread will be created that will take the second part of the patitioned list. After the list is split, the parent will work on their half while the child works on theirs. The list will continue splitting until either the list is sorted, or the maximum number of usable threads is reached. Once any section of the list is sorted, the parent will wait for the child. This will cascade until the entire list is completely sorted.


##### Summary of functions

`int[] quicksort(int *arr, int threads, long size)`

This function will be a wrapper class designed to be called in the main.c file. Longs passed to avoid segmentation faults. 

`void swap(int *arr, long index1, long index2)`

The swap function of the "quicksort.c" file can take an array "list[]", and two indexes; "index1", and "index2". This method will then modify the "list[]" variable in such a way that the element at "index1" swaps with the element at "index2" of the list.

`int partition(int *arr, long start, long stop)`

The partition function of the "quicksort.c" file can take an array "arr[]" and a partition index. The list will then partition at the index, sending one of of the array to be sorted by the parent thread recursively, and the other half of the array to be sorted recursively by the child. This will continue until either the maximum number of the threads are reached, or a section of the list is sorted. The parent will wait for its child, and this will cascade until the list is completley sorted.

 `int quicksort_setup(void *arguments)`

 This method of the "quicksort.c" file is used to ensure that the maximum number of threads are not in use.
 
 `int *randomArray (long size)`

Method used to create an array of size `size` filled with random values between 0 and 2147483647. This method is used for testing.

`int main(int argc, char* argv[])`

Main method will test the file when executed and output number of threads, size of array, and time taken to sort. It will do this for threads between 1 and 128, incremented by thread_count * 2, and array sizes between 1 and 100000000, incremented by arraySize * 2.

##### Summary of Data Types

Similarly to Merge Sort, since the function will operate on seperate sections of the array, semaphores are unecessary here. Additionally, Quick Sort uses an array of pthreads with different tid's and and an array of different attributes. 

However, there will be a semaphore used to protect any global variables that may be used during the process. 

The only data type that we created for this file is the struct `params` that will be used to hold the array of tids, attributes, and various other values. 

##### Sample Output

1,1,0.000246
1,2,0.000162
1,4,0.000137
1,8,0.000107
1,16,0.000125
1,32,0.000101
1,64,0.000069
1,128,0.000084
1,256,0.000092
1,512,0.000188
1,1024,0.000206
1,2048,0.000297
1,4096,0.000593
1,8192,0.001565
1,16384,0.002851
1,32768,0.006150
1,65536,0.014101
1,131072,0.029801
1,262144,0.057098
1,524288,0.112673

### mergesort_single_process.c

This file contains the classic mergesort algorithm for that is run with a single process. We are using it to compare to the multiprocess sorting algorithms we created as a sort of control in the experiment that will be conducted in `main.c`.

##### Summary of functions

`void sort(int array[], int temp[], long low, long high)`

This function contained in `mergesort_single_process.c` is used as the main call to sort an array in ascending order using the classic mergesort algorithm. The way it works is by repeatedly calling the sort function recursively, and the merge function that will be discussed following this. The sort function will split the array in half as evenly as possible repeatably. Array and Temp is passed in order to get the place in memory from the `main()` method to the `merge()` method. Longs are passed to avoid segmentation faults.

`void merge(int array[], int temp[], long low, long mid, long high)`

This function of the `mergesort_single_process.c` file merges the array back together after it has been split based off which value is larger. It does this by utilizing the array `temp[]` to store the values of `array[]` in the desired order. At the end of the algorithm, the updated values in `temp[]` are placed in `array[]`, and `temp[]` is emptied to ensure no overflow errors. Longs are passed to avoid segmentation faults.

`int *randomArray (long size)`

Method used to create an array of size `size` filled with random values between 0 and 2147483647. This method is used for testing.

`int main()`

Method utilized to print the times it takes to sort the array at increments i = i * 2, up to 1000000. The times will be compared to our multi-threaded algorithm.

##### Summary of Data Types

Two arrays are utilized in this file, `temp[]` and `array[]`. `array[]` contains the values that is to be sorted, and is updated by the values within `temp[]` at every merge call. The reason this was implemented like this was to ensure that memory would not overflow in the tests where we utilizes arrays of size 500000000. We wanted a single `temp[]` that was written and overwritten continuously in order to ensure this error would be avoided, and also it would allow for O(N) runtime.

##### Sample Output

1,0.000000
2,0.000001
4,0.000001
8,0.000001
16,0.000002
32,0.000004
64,0.000008
128,0.000015
256,0.000029
512,0.000066
1024,0.000145
2048,0.000306
4096,0.000637
8192,0.001333
16384,0.002948
32768,0.005698
65536,0.014336
131072,0.028031
262144,0.057995
524288,0.121642

### bubblesort_single_process.c

This is the classic bubblesort algorithm for a single process. We are using it to compare to the multiprocess sorting algorithms we created as a sort of control in the experiment that will be conducted in `main.c`.

##### Summary of functions

`bubblesort(int array[], long index)`

This method of the `mergesort_single_process.c` file will sort a list of values in an ascending order. It does this by looking through the list of values linearly, and at each increment it will compare the index value to the next sequential value. It will swap the values and continue searching the list linearly until the list is sorted. A long is passed to avoid segmentation faults.

`swap(int *arr, long index1, long index2)`

This method of the `mergesort_single_process.c` file is a helper method for the `bubblesort(int array[], long index)` method. It is used to swap the value of index1, and index2. Utilized primarily to make the code more readable, longs are passed to avoid segmentation faults.

`int *randomArray (long size)`

Method used to create an array of size `size` filled with random values between 0 and 2147483647. This method is used for testing.

`int main()`

Method utilized to print the times it takes to sort the array at increments i = i * 2, up to 2500. The times will be compared to our multi-threaded algorithm.

##### Summary of Data Types

This function operates on only a single array. Since it is a single process function, no variables are necessary to be protected.

##### Sample Output

1,0.000001
2,0.000000
4,0.000001
8,0.000001
16,0.000003
32,0.000007
64,0.000020
128,0.000067
256,0.000211
512,0.000691
1024,0.002768
2048,0.012035

### quicksort_single_process.c

This is the classic bubblesort algorithm for a single process. We are using it to compare to the multiprocess sorting algorithms we created as a sort of control in the experiment that will be conducted in `main.c`.

##### Summary of functions

`void quicksort(int array[], long lowIndex, long highIndex)`

This function of `quicksort_single_process.c` is the classic quicksort algorithm for a single process. Recursively calls itself and splits the array in half at a partition index. Takes an `array[]` and sorts the array ascending. Longs are used for lowIndex and highIndex in order to avoid segmentation faults.

`int partition(int array[], long lowIndex, long highIndex)`

This function of `quicksort_single_process.c` determines the partition index to be utilized in the `void quicksort(int array[], long lowIndex, long highIndex)` function. Longs are passed in order to avoid segmentation faults.

`int swap(int *arr, long index1, long index2)`

This function is a helper method that swaps two values within an array. Longs are passed to avoid segmentation faults.

`int *randomArray (long size)`

Method used to create an array of size `size` filled with random values between 0 and 2147483647. This method is used for testing.

`int main()`

Method utilized to print the times it takes to sort the array at increments i = i * 2, up to 100000000. The times will be compared to our multi-threaded algorithm.

##### Summary of Data Types

The file `quicksort_single_process.c` contains a single array as its data structure. It will continuously swap values in this array through the functions discussed in the previous section until the array is sorted ascendingly. 

##### Sample Output

1,0.000001
2,0.000001
4,0.000000
8,0.000015
16,0.000001
32,0.000017
64,0.000006
128,0.000025
256,0.000038
512,0.000054
1024,0.000114
2048,0.000261
4096,0.000661
8192,0.001302
16384,0.002762
32768,0.006269
65536,0.012259

## Work Distribution

#### Noah Houpt

I completed the mergesort_single_process.c, bubblesort_single_process.c, and quicksort_single_process.c in their entirety in order to have a sort of control in our experiment. I also contributed a significant amount to our readme file. Additionally I worked to create the makefile. I helped Guy with quicksort.c, mergesort.c, and bubblesort.c with errors. We had significant issues with segmentation faults, so bug fixing took up a significant portion of our time with this project, I helped with fixing these errors. 

#### Guy Marino

I completed the mergesort.c, quicksort.c, and bubblesort.c files. I also helped with the makefile. I modified the readme also. I implemented the multi-threaded processes in almost their entirety outside of bug fixing.
