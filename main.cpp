// Zachary Wileman
// Algorithms Course Project
// Comparing run-times of different sorting algorithms

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
using namespace std;

// Used for creating array of random values
void generateRandomArray(long array[], const long &numValues)
{
	for (long i = 0; i < numValues; i++)
	{
		array[i] = (rand()%32000)+1;
	}

	//cout << "Original Array" << endl;
	//for (long i = 0; i < numValues; i++)
	//	cout << array[i] << endl;

	//cout << endl << endl;
}

// Used by merge sort to merge arrays
void merge(long array[], long start, long midPoint, long end)
{
	long LS = start, RS = midPoint+1;
	long currentIndex = 0;
	long *newArray = new long[end-start+1];
	bool LSDone = false, RSDone = false;

	while (currentIndex != (end-start+1))
	{
		if (LSDone)
		{
			newArray[currentIndex] = array[RS];
			RS++;
		}
		
		else if (RSDone)
		{
			newArray[currentIndex] = array[LS];
			LS++;
		}
		
		else if (array[LS] <= array[RS])
		{
			newArray[currentIndex] = array[LS];
			LS++;

			if (LS == (midPoint+1))
				LSDone = true;
		}
		
		else //(array[RS] < array[LS])
		{
			newArray[currentIndex] = array[RS];
			RS++;

			if (RS == (end+1))
				RSDone = true;
		}

		currentIndex++;
	}

	int j = 0;
	for (long i = start; i < (end+1); i++)
	{
		array[i] = newArray[j];
		j++;
	}

	delete []newArray;
}

// Sorts array via Merge Sort
void mergeSort(long array[], long start, long end)
{
	long midPoint;

	if (start < end)
	{
		midPoint = (start + end)/2;
		mergeSort(array, start, midPoint);
		mergeSort(array, midPoint+1, end);
		merge(array, start, midPoint, end);
	}
}

// Sorts array via Quick Sort
void quickSort(long array[], long start, long end)
{
	long pivot;
	long i, j;
	long temp;

	if (start < end)
	{
		pivot = array[end];
		i = start-1;
		j = start;

		while (j != end)
		{
			if (array[j] <= pivot)
			{
				i++;
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}

		array[end] = array[i+1];
		array[i+1] = pivot;

		quickSort(array, start, i);
		quickSort(array, i+2, end);
	}
}

// Sorts array via Bubble Sort
void bubbleSort(long array[], long start, long end)
{
	long temp;

	for (long i = (end+1); i > start; i--)
	{
		for (long j = start; j < (i-1); j++)
		{
			if (array[j] > array[j+1])
			{
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

// Sorts array via Selection Sort
void selectionSort(long array[], long start, long end)
{
	long temp;

	for (long i = start; i < (end+1); i++)
	{
		for (long j = (i+1); j < (end+1); j++)
		{
			if (array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}


// Sorts array via Insertion Sort
void insertionSort(long array[], long start, long end)
{
	long temp;

	for (long i = start+1; i < (end+1); i++)
	{
		if (array[i] < array[i-1])
		{
			for (long j = i; j > start; j--)
			{
				if (array[j] < array[j-1])
				{
					temp = array[j];
					array[j] = array[j-1];
					array[j-1] = temp;
				}

				else
					break;
			}
		}
	}
}

// Used for creating an array of function calls
typedef void (*sortingAlgorithms) (long array[], long start, long end);

int main()
{
	// Initialize Random seed
	srand(time(NULL));

	clock_t t; // Used for timing algorithms
	const long arraySize = 1000000; // This is where you change the size of the array
	long *values = new long [arraySize];
	long *copyValues = new long [arraySize];
	generateRandomArray(values, arraySize);
	int numAlg = 5;
	
	// Create array of function calls
	sortingAlgorithms function[] = {mergeSort, quickSort, bubbleSort, selectionSort, insertionSort};
	
	// Run Sorting Algorithms
	for (int i = 0; i < numAlg; i++)
	{
		// Creates a copy of the randomly generated array to test the current sorting algorithm with
		for (long j = 0; j < arraySize; j++)
			copyValues[j] = values[j];

		// Times each sorting algorithm
		t = clock();
		function[i](copyValues, 0, arraySize-1);
		t = clock() - t;

		switch(i)
		{
			case 0:
				cout << "Merge Sort took ";
				break;
			case 1:
				cout << "Quick Sort took ";
				break;
			case 2:
				cout << "Bubble Sort took ";
				break;
			case 3:
				cout << "Selection Sort took ";
				break;
			case 4:
				cout << "Insertion Sort took ";
				break;
		}
	
		// Outputs the number of seconds each sorting algorithm took to sort the array
		cout << t << " ticks (" << setprecision(10) << (float(t)/ (CLOCKS_PER_SEC)) << " seconds)" << endl;
	}
	
	// Dealocates memory used for the arrays
	delete []values;
	delete []copyValues;
	
	return 0;
}
