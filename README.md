# EECS-338-Final-Project

## Summary of Files

### Makefile

The makefile is responsible for compiling all of the files and merging them together. The makefile first compiles all of the c programs into .o files and then stitches them together at the end. The result of a successful make should be a binary file titled run in the root folder of the project.

### mergesort.c

Merge Sort of the list works in such a way that every time the algorithm splits the list, it creates a new child process to sort the second half of the split list while the parent finishes sorting the first half. For a better depiction, see the diagram below:

![Merge Sort](images/mergesort.png)

This method will allow thread reuse while also ensuring that there is a maximal cover of threads for each part of the list. At the end of each sorting cycle, the parent will wait for the child thread to terminate and will merge the two parts of the sorted list back together.

### bubblesort.c

### quicksort.c

Quick sort of the list works in a way such that after every partition is created, a new child thread will be created that will take the second part of the patitioned list. After the list is split, the parent will work on their half while the child works on theirs. The list will continue splitting until either the list is sorted, or the maximum number of usable threads is reached. Once any section of the list is sorted, the parent will wait for the child. This will cascade until the entire list is completely sorted.

### main.c

Main is utilized to test our sorting algoirthms. The methodology for this is to time the functions at each parameter. The parameters we will be testing are as follows:

Number of threads: 1, 2, 4, 8, 16, 32, 64

Length of Array: 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000,
500000, 1000000, 2000000, 5000000, 10000000, 20000000, 50000000, 100000000, 200000000, and 500000000

Sorting Algorithms: Bubble, Quick, Merge

Looking at the different parameters, it can be calculated that there will be 504 different data points to look at, with each algorithm having 168 points of data.

The arrays will be generated using the function randomArray(), where randomArray() takes in a parameter for the size of the array, a lower bound and an upper bound.

##### Summary of Functions

`void mergesort(int arr[], int size, int num_threads)`

This function will mergesort the list using the function `mergesort_helper`. This function is a wrapper funciton based designed to sort the entire array.

`void *mergesort_helper(void *args)`

This function will be called by each child thread and will be responsible for splitting each half and then merging the two halves together using `merge`. The `mergesort_helper` function will see if it can instantiate a new thread, if it can it will add the thread to the array of threads and call `mergesort_helper` on the first part of the list while the child thread sorts the other.

`void merge(int arr[], int first, int second, int stop)`

The merge function merges the lists from first to second, and then from second to stop. The merge function assumes that both lists are already sorted, and goes through each part of the list comparing the least significant elements until it has completed merging the list. The resulting list should then be sorted.

`void swap(int list[], int index1, int index2)`

The swap function of the "quicksort.c" file can take an array "list[]", and two indexes; "index1", and "index2". This method will then modify the "list[]" variable in such a way that the element at "index1" swaps with the element at "index2" of the list.

`void partition(int arr[], int partitionIndex)`

The partition function of the "quicksort.c" file can take an array "arr[]" and a partition index. The list will then partition at the index, sending one of of the array to be sorted by the parent thread recursively, and the other half of the array to be sorted recursively by the child. This will continue until either the maximum number of the threads are reached, or a section of the list is sorted. The parent will wait for its child, and this will cascade until the list is completley sorted.

 `int quicksort_setup(int list[], int maxThreads)`

 This method of the "quicksort.c" file is used to ensure that the maximum number of threads are not in use.

`void randomArray(int lowerBound, int upperBound, int arraySize)`

This function is utilized in the file "main.c". The purpose of this method is to generate a random array. The function utilizes the system time to create a psudo-random number that will be added into an array and later sorted for the purpose of testing. There is additional functionallity in the upperBound and lowerBound arguments, but for clarity in our main method we used fixed values here.

`void main()`

This function is utilized in the file "main.c". The purpose of this method is to produce a csv file that will produce an output that is explained further later in the report. The function utilizes the system time in order to time how long it takes each sorting algorithm at different parameters to fully sort its array. Additionally, the method utilizes the `randomArray` function in order to produce psudo-random arrays.

##### Summary of Data Types

Since the function operates separately on different parts of the array, semaphores are unnecessary. Instead, we will be using an array of pthread tid's and an array of pthread attribute structs to

##### Sample Output

The main method will output a csv file that can then be plotted. The csv file will be in the following format:

`threads,elements,merge_time,quick_time,bubble_time`

Some artificially generated output (NOT ACCURATE) can be seen below:

```
...
16,50000,20.422,32.542,85.279
16,100000,40.683,64.114,164.983
...
32,100,20.478,20.824,15.548
32,200,21.643,21.743,15.933
...
```
## Work Distribution

#### Noah Houpt

So far on the project I have implemented the bubblesort.c algorithm, the mergesort.c algorithm, and the swap method of quicksort.c. Additionally I have wrote the randomArray() method of the main.c file, and commented on the main.c file. Between this submission and the submission for the final project, I plan on completing the mergesort.c algorithm as well as data analysis of the main.c file's output.

#### Guy Marino
