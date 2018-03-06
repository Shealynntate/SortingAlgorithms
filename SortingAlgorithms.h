#pragma once

#include "HelperFunctions.h"

// Comparison Model Sorting
// ---------------------------------------------
// ---------------------------------------------
//   All input items are black boxes (ADT - abstract data types)
//   Only operations allowed are comparisons
//   Time Cost = number of comparisons
//   Optimal Sorting: Ω(nlogn)
//   Optimal Search: Ω(logn)


// Selection Sort
// ---------------------------------------------
//
//  - Simplest implementation
//  - Time Complexity : O(n^2)
//  - Space Complexity : O(1) - in-place
//
//  Sudo Code:
//
//  for each index i:
//    Find the smallest item in the unsorted part of array
//    Place at location i
//
template<typename T>
void SelectionSort(std::vector<T>& items)
{
	for (int i = 0; i < items.size(); ++i)
	{
		int j = findMin(items, i, items.size() - 1);
		swap(items[i], items[j]);
	}
}

template<typename T>
void SelectionSort(T items[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		int j = findMin(items, i, size - 1);
		swap(items[i], items[j]);
	}
}

// Insertion Sort
// ---------------------------------------------
//
//  - Bad, but in practice does better than Selection and Bubble sort
//  - Time Complexity: O(n^2)
//  - Space Complexity: O(1) - in-place
//
//  Sudo Code:
//
//  for each index i:
//    Walk down the sorted portion of array until [i] < sorted value
//    While walking, move sorted elements up one index to make room
//
template<typename T>
void InsertionSort(T items[], int size)
{
	for (int i = 1; i < size; ++i)
	{
		T value = items[i];
		int dest = i;

		// Move down sorted part of array until we find a value that's <= next
		while (dest > 0 && value < items[dest - 1])
		{
			items[dest] = items[dest - 1];
			dest--;
		}

		items[dest] = value;
	}
}

template<typename T>
void InsertionSort(std::vector<T>& items)
{
	for (int i = 1; i < items.size(); ++i)
	{
		T value = items[i];
		int dest = i;

		while (dest > 0 && value < items[dest - 1])
		{
			items[dest] = items[dest - 1];
			dest--;
		}

		items[dest] = value;
	}
}

// Bubble Sort
// ---------------------------------------------
//
//  - Very inefficient
//  - Time Complexity: O(n^2)
//  - Space Complexity: O(1) - in-place
//
//  Sudo Code:
//
//  Loop over array:
//    if value at i > value at i + 1
//      swap values
//  Execute above loop n times
//
//  - causes largest value to 'bubble' up to last spot in array 
//  - next loop causes second largest to 'bubble' up, and so on
//
template<typename T>
void BubbleSort(T items[], int size)
{
	for (int i = size - 1; i >= 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (items[j] > items[j + 1])
				swap(items[j], items[j + 1]);
		}
	}
}

template<typename T>
void BubbleSort(std::vector<T>& items)
{
	for (int i = items.size() - 1; i >= 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (items[j] > items[j + 1])
				swap(items[j], items[j + 1]);
		}
	}
}

// Merge Sort
// ---------------------------------------------
//
//  - Maximally efficient in time but not in space
//  - Time Complexity: O(nlogn) - best you can do
//  - Space Complexity: O(n) - not great for large inputs
//  - Divide and Conquer strategy
//
//  Sudo Code:
//
//  Create two smaller arrays and copy lower and upper half of array into each
//  Call MergeHelper with the two smaller arrays
//  Continue recursing until base case: array of size 1
//  When unwinding recursion, merge the two sorted array halves together 
//    Loop over destination array and continue to choose smallest value from
//    both array halves to add into dest next.
//
template<typename T>
void Merge(T left[], int size_left, T right[], int size_right, T result[], int size)
{
	int index_left = 0;
	int index_right = 0;
	for (int i = 0; i < size; ++i)
	{
		// Only items in right array remain
		if (index_left == size_left)
		{
			result[i] = right[index_right];
			index_right++;
		}
		// Only items in left array remain
		else if (index_right == size_right)
		{
			result[i] = left[index_left];
			index_left++;
		}
		// Both arrays have items, compare to find smallest
		else
		{
			if (right[index_right] < left[index_left])
			{
				result[i] = right[index_right];
				index_right++;
			}
			else
			{
				result[i] = left[index_left];
				index_left++;
			}
		}
	}
}

template<typename T>
void MergeSort(T items[], int size)
{
	if (size <= 1)
		return;

	int size_left = round(size / 2.0f);
	int size_right = size / 2;
	T* left = new T[size_left];
	T* right = new T[size_right];

	// Fill in the sub arrays
	for (int i = 0; i < size_left; ++i)
		left[i] = items[i];

	for (int j = 0; j < size_right; ++j)
		right[j] = items[size_left + j];

	MergeSort(left, size_left);
	MergeSort(right, size_right);
	Merge(left, size_left, right, size_right, items, size);

	// Clean up memory allocated
	delete[] left;
	delete[] right;
}

// Quick Sort
// ---------------------------------------------
//
//  - Great algorithm, often used as library standard for sorts.
//  - Time Complexity: O(n^2) - worst case (very rare)
//                     O(nlogn) - average case (very likely)
//  - Space Complexity: O(1) - in-place
//	- Divide and Conquer paradigm
//	- Recursive
//  - Not stable sorting
//
//	- Time explained: 
//      Best/Average Case: occurs when we have *balanced partitioning*,
//		meaning the pivot divides the array into two equal sized sub-arrays.
//		Then the depth of recursion is log(n) - optimal depth.
//		The work we do for each sub-array is (n / depth) and we have depth sub-arrays, which sums to n.
//		So (n) amount of work at each level for log(n) levels is O(nlogn).
//
//		Worst Case: If our pivot doesn't split the sub-arrays evenly and instead creates one sub-array
//		only -1 shorter than the parent. Then the tree will have (n) levels, with (n) amount of work
//		at each level. So our time becomes O(n^2)
//
template<typename T>
void QuickSortHelper(T* items, int start, int end)
{
	if (start >= end)
		return;

	// Pivot chosen to be rightmost element
	T pivot_value = items[end];
	int pivot_index = start;

	// Move values smaller than pivot to left
	for (int i = start; i < end; ++i)
	{
		// Item out of place - move to left of pivot_index
		if (items[i] < pivot_value)
		{
			swap(items[i], items[pivot_index]);
			pivot_index++;
		}
	}
	swap(items[end], items[pivot_index]);

	QuickSortHelper(items, start, pivot_index - 1);
	QuickSortHelper(items, pivot_index + 1, end);
}

template<typename T>
void QuickSort(T* items, int size)
{
	QuickSortHelper(items, 0, size - 1);
}

// RAM Model Sorting
// ---------------------------------------------
// ---------------------------------------------
// Random Access Machine
//   - Memory is a large array
//   - Can access any location in constant time
//   - Can do a lot more than comparisons in constant time
// Assumptions: 
//   - Keys we are sorting are integers
//   - Non-negative values between [0, k]
//     technically can be negative, but more complicated
//   - Each key fits into a machine word
// Can sort in linear time, for k = n^O(1) - polynomial in n


// Counting Sort
// ---------------------------------------------
//  - Mediocre
//  - Walk through elements and count all the items.
//  - Sudo Code:
//      L = array of k empty lists   // one slot for each potential key value
//      for j in range(n):           // loop over items to be sorted
//        L[key(A[j])].append(A[j])  // add item to list at index key in L 
//      output = []              
//      for i in range(k):           // loop over elements of L
//        output.extend(L[i])        // append items at each index to the output
//   - Time Complexity: O(n + k)

template<typename V>
void CountingSort(std::pair<int, V>* items, int size, int maxValue)
{
	// Each bucket holds a vector to allow duplicate keys
	auto L = new std::vector<std::pair<int, V>>[maxValue + 1];

	// Add items to L based on key
	for (int i = 0; i < size; ++i)
	{
		int key = items[i].first;
		L[key].push_back(items[i]);
	}

	int index = 0;
	for (int i = 0; i < maxValue; ++i)
	{
		int num = L[i].size();
		while (num > 0)
		{
			int size = L[i].size();
			items[index] = L[i][size - num];
			num--;
			index++;
		}
	}

	delete[] L;
}

// Radix Sort
// ---------------------------------------------
//  - Uses Counting Sort as a sub-routine
//  - Imagine each integer as base b
//  - Know that the number of digits in key is: d = log_b(k) + 1
//  - Sudo Code:
//      Sort integers by least significant digit  // using counting sort
//      ...                                       // runs d times
//      Sort integers by most significant digit   
//
//  - Analysis: Each sort takes O(n + b)
//    Total time: O(n + b) * d = O(n + b) * log_b(k)
//                minimized when b = Theta(n)
//                O(nlog_n(k))
//                when k is polynomial in n, it's linear

template<typename V>
void RadixSort(std::pair<int, V>* items, int size, int maxValue)
{

}
