// Name: Kevin Huynh
// Filename: main.cpp
// Description: Shows off the different sort functions and calculates the time it takes
// to execute each

#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void selectionSort(int array[], int size) {			// Taken from zybooks Comp 53: 13.5
	int indexSmallest, temp;
	for (int i = 0; i < size; i++) {
		indexSmallest = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j] < array[indexSmallest]) {
				indexSmallest = j;
			}
		}
		temp = array[i];
		array[i] = array[indexSmallest];
		array[indexSmallest] = temp;
	}
}

void insertionSort(int array[], int size) {			// Taken from zybooks Comp 53: 13.6
	int j, temp;
	for (int i = 1; i < size; i++) {
		j = i;
		while (j > 0 && array[j] < array[j - 1]) {
			temp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = temp;
			j--;
		}
	}
}

void bubbleSort(int array[], int size) {	// Moves the larger numbers towards the end while slowly pushing up the smaller numbers towards the front
	int temp;					// Defines temp variable
	for (int i = 0; i < size; i++) {		// First for-loop
		for (int j = 0; j < size; j++) {	// Second for-loop
			if (array[j] > array[j + 1]) {	// Checks if the number at the current index is greater than the next one
				temp = array[j];			// Stores the number at the current index in temp
				array[j] = array[j + 1];	// Sets the number at the next index in the current index
				array[j + 1] = temp;		// Moves the number in temp to the next index
			}
		}
	}
}

void merge(int array[], int i, int j, int k) {		// Taken from zybooks Comp 53: 13.7
	int mergedSize = k - i + 1;
	int mergePos = 0;
	int leftPos = 0;
	int rightPos = 0;
	int* mergedNumbers = new int[mergedSize];

	leftPos = i;
	rightPos = j + 1;

	while (leftPos <= j && rightPos <= k) {
		if (array[leftPos] < array[rightPos]) {
			mergedNumbers[mergePos] = array[leftPos];
			leftPos++;
		}
		else {
			mergedNumbers[mergePos] = array[rightPos];
			rightPos++;
		}
		mergePos++;
	}

	while (leftPos <= j) {
		mergedNumbers[mergePos] = array[leftPos];
		leftPos++;
		mergePos++;
	}

	while (rightPos <= k) {
		mergedNumbers[mergePos] = array[rightPos];
		rightPos++;
		mergePos++;
	}

	for (mergePos = 0; mergePos < mergedSize; mergePos++) {
		array[i + mergePos] = mergedNumbers[mergePos];
	}
}

void mergeSort(int array[], int i, int k) {		// Taken from zybooks Comp 53: 13.7
	int j = 0;

	if (i < k) {
		j = (i + k) / 2;

		mergeSort(array, i, j);
		mergeSort(array, j + 1, k);

		merge(array, i, j, k);
	}
}

int partition(int array[], int i, int k) {		// Taken from zybooks Comp 53: 13.8
	int l = 0;
	int h = 0;
	int midpoint = 0;
	int pivot = 0;
	int temp = 0;
	bool done = false;

	midpoint = i + (k - i) / 2;
	pivot = array[midpoint];

	l = i;
	h = k;

	while (!done) {
		while (array[l] < pivot) {
			l++;
		}

		while (pivot < array[h]) {
			h--;
		}
		
		if (l >= h) {
			done = true;
		}
		else {
			temp = array[l];
			array[l] = array[h];
			array[h] = temp;
			l++;
			h--;
		}
	}
	return h;
}

void quickSort(int array[], int i, int k) {		// Taken from zybooks Comp 53: 13.8
	int j = 0;

	if (i >= k) {
		return;
	}

	j = partition(array, i, k);

	quickSort(array, i, j);
	quickSort(array, j + 1, k);

	return;
}

void autoFill(int array[], int size) {		// Fills the array
	int y = 0;
	for (int x = 0; x < size; x++) {
		array[x] = rand() % (size * 2);		// Fills with random numbers between 0 - ((size * 2) - 1)
		y++;
	}
}

bool is_Sorted(int array[], int size) {
	for (int x = 0; x < size - 1; x++) {	// Checks the entire array
		if (array[x] > array[x + 1]) {		// Checks if the number at the current index is greater than the next one
			return false;
		}
	}
	return true;
}

int main() {
	int start, stop, selectionT = 0, insertionT = 0, bubbleT = 0, mergeT, quickT;		// Initializes multiple variables to store time
	int SIZE = 20000;					// Sets the size of the array
	int *ptr = new int[SIZE + 1];		// Creates a dynamically allocated array

	autoFill(ptr, SIZE);				// Fills the array with random numbers

	start = clock();
	selectionSort(ptr, SIZE);			// Sorts the array using the selection method
	stop = clock();
	selectionT = stop - start;			// Stores the time for selectionSort
	cout << selectionT << " milliseconds." << endl;
	if (is_Sorted(ptr, SIZE)) {			// Checks if the array is actually sorted
		cout << "True" << endl;
	}
	else {
		cout << "Error" << endl;
	}

	autoFill(ptr, SIZE);				// Fills the array with random numbers again

	start = clock();
	insertionSort(ptr, SIZE);			// Sorts the array using the insertion method
	stop = clock();
	insertionT = stop - start;			// Stores the time for insertionSort
	cout << insertionT << " milliseconds." << endl;
	if (is_Sorted(ptr, SIZE)) {
		cout << "True" << endl;
	}
	else {
		cout << "Error" << endl;
	}

	autoFill(ptr, SIZE);				// Fills again

	start = clock();
	bubbleSort(ptr, SIZE);				// Sorts the array using the bubble method
	stop = clock();
	bubbleT = stop - start;				// Stores the time for bubbleSort
	cout << bubbleT << " milliseconds." << endl;
	if (is_Sorted(ptr, SIZE)) {
		cout << "True" << endl;
	}
	else {
		cout << "Error" << endl;
	}

	autoFill(ptr, SIZE);				// Fills again

	start = clock();
	mergeSort(ptr, 0, SIZE);			// Sorts the array using the merge method
	stop = clock();
	mergeT = stop - start;				// Stores the time for mergeSort
	cout << mergeT << " milliseconds." << endl;
	if (is_Sorted(ptr, SIZE)) {
		cout << "True" << endl;
	}
	else {
		cout << "Error" << endl;
	}

	autoFill(ptr, SIZE);				// Fills again

	start = clock();
	quickSort(ptr, 0, SIZE);			// Sorts the array using the quick method
	stop = clock();
	quickT = stop - start;				// Stores the time for quickSort
	cout << quickT << " milliseconds." << endl;
	if (is_Sorted(ptr, SIZE)) {
		cout << "True" << endl;
	}
	else {
		cout << "Error" << endl;
	}

	cout << "Finished all sorting methods." << endl;	// Prints a confirmation that all sorting methods have executed

	ofstream file("Results.txt");			// Creates a new text file
	if (file.is_open()) {				// Confirms that the file is open before writing to it
		file << "Selection Sort: " << SIZE << " elements took " << selectionT << " milliseconds." << endl;	// Writes this to the file
		file << "Insertion Sort: " << SIZE << " elements took " << insertionT << " milliseconds." << endl;
		file << "Bubble Sort: " << SIZE << " elements took " << bubbleT << " milliseconds." << endl;
		file << "Merge Sort: " << SIZE << " elements took " << mergeT << " milliseconds." << endl;
		file << "Quick Sort: " << SIZE << " elements took " << quickT << " milliseconds." << endl;
		file.close();				// Closes the file
	}
	else {
		cout << "Error, could not open file." << endl;		// In case the file didn't open, prints this
	}

	cout << "Merge: " << mergeT << endl;
	cout << "Quick: " << quickT << endl;

	delete[] ptr;				// Deletes the dynamically allocated array

	system("pause");
}