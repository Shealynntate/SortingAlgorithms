#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

// Print Array & Vector
// ---------------------------------------------
template<typename T>
void print_array(T* input, int size)
{
	std::cout << "[ ";
	for (int i = 0; i < size; ++i)
	{
		std::cout << input[i];
		if (i < size - 1)
			std::cout << ", ";
	}

	std::cout << " ]" << std::endl;
}

template<typename T>
void print_vector(std::vector<T> input)
{
	std::cout << "[ ";
	for (int i = 0; i < input.size(); ++i)
	{
		std::cout << input[i];
		if (i < input.size() - 1)
			std::cout << ", ";
	}

	std::cout << " ]" << std::endl;
}

// Find Max
// ---------------------------------------------
template<typename T>
int findMax(T items[], int start, int end)
{
	int max_index = start;
	T max_value = items[start];

	for (int j = start; j <= end; ++j)
	{
		if (items[j] > max_value)
		{
			max_index = j;
			max_value = items[j];
		}
	}

	return max_index;
}

template<typename T>
int findMax(std::vector<T> items, int start, int end)
{
	int max_index = start;
	T max_value = items[start];

	for (int j = start; j <= end; ++j)
	{
		if (items[j] > max_value)
		{
			max_index = j;
			max_value = items[j];
		}
	}

	return max_index;
}

// Find Min
// ---------------------------------------------
template<typename T>
int findMin(T items[], int start, int end)
{
	int min_index = start;
	T min_value = items[start];

	for (int i = start; i <= end; ++i)
	{
		if (items[i] < min_value)
		{
			min_index = i;
			min_value = items[i];
		}
	}

	return min_index;
}

template<typename T>
int findMin(std::vector<T> items, int start, int end)
{
	int min_value = items[start];
	int min_index = start;
	for (int i = start; i <= end; ++i)
	{
		if (items[i] < min_value)
		{
			min_value = items[i];
			min_index = i;
		}
	}

	return min_index;
}

// Swap
// ---------------------------------------------
template<typename T>
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// Find Max Key
// ---------------------------------------------
template<typename V>
int FindMaxKey(const std::pair<int, V>* items, int size)
{
	int max = items[0].first;

	for (int i = 0; i < size; ++i)
	{
		int key = items[i].first;
		if (key > max)
			max = key;
	}

	return max;
}
