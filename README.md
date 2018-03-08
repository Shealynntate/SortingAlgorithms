# Sorting Algorithms
This repo contains templated implementations of common sorting algorithms. 
<br>
All sorted types are of generic type T, except for Counting and Radix sort, where the keys
are assumed to be integers.
<br>
Below is a brief description of each sorting algorithm, its pros and cons, and time and space complexity.

First, it's useful to note that there are multiple analysis models for searching and sorting algorithms.
The model you work within will determine certain constraints and best/worst case performance. 
Here are the two models used for these algorithms.

## The Comparison Model
*Used for : Selection, Bubble, Insertion, Merge, Quick, and Heap Sort*

In this model we consider all the items we're sorting to be "black boxes". That is, we don't know anything about them other than they support comparisons (&gt;, &lt;, ==, etc). In analyzing these algorithms, we count up the number of comparisons needed as our time complexity and consider any other operations, like addition or swaping, to take no clock cycles at all.
Even with these super conservative estimates for algorithmic time complexity, we can still prove two important things:
1. Searching for an item has a lower bound of Ω(logn)
2. Sorting items has a lower bound of Ω(nlogn)

If an algorithm takes O(logn) for searching or O(nlogn) for sorting, we know it's as good as it can be (in this model).

## Random Access Machine (RAM) Model
*Used for: Counting and Radix sort*

Here we make a few different assumptions about our data to be searched/sorted.
1. We're sorting/searching non-negative integers<br>
That may sound restrictive, but we can always use integer keys associated with any data value we like.
2. All the integers fit into a Word size on our machine (typically 32 or 64 bits)<br>
In this model we're taking advantage of the fact that we can do more simple arithmetic operations (e.g. addition) than comparisons in the same amount of time.

### Notes on Algorithm Properties
- Stable : An algorithm is stable if two elements with the same key remain in the same relative order after being sorted.<br>
e.g. In my original, unsorted array, element A comes before element B, and both have a key of 2 for sorting. Then my algorithm is stable if in the final, sorted array, A is still before B.
- In-place : An algorithm is in-place if it uses O(1) space for sorting.<br>
So aside from a few temporary variables, the amount of space used is negligible and independent of the size of the array to be sorted.
- Divide and Conquer : An algorithmic paradigm that provides a general approach to solving a problem, like Greedy Algorithms or Dynamic Programming. Here the approach is to divide the problem in to self-similar sub problems and recursively solve those.

---

## Selection Sort
*Straightfoward, but bad algorithm. Repeatedly find the smallest element.*
  - Time Complexity: O(n<sup>2</sup>)<br>
  - Space Complexity: O(1)
  - In-place
#### Walkthrough:
*Not in-place version*
- create a second array the same size as the original
- loop over the original and find the smallest element, e
- add e to the first spot in the new array
- set e in the original array to some MAX_VALUE, so that it's ignored from now on
- repeat with all the elements in the original array
- can then copy the values of the new array back into the original

*In-place version*
- when you find the smallest element e, swap it with the first element in the array
- now all sorting takes place in the original array with some temp storage

## Bubble Sort
*Worse than Selection Sort. Repeatedly 'bubble up' largest value to end of array.*
  - Time Complexity: O(n<sup>2</sup>)
  - Space Complexity: O(1)
  - In-place
  - Stable
#### Walkthrough:
- takes multiple passes through the array
- each pass compare the element at index i to the one at i + 1
- if the element at i is larger, swap them and move to the next one
- after one pass, the largest element will have "bubbled up" to the end of the array
- next pass the second largest element will be in the correct spot
- once we reach the spot in the array that's already been sorted, we can stop that pass
- after n - 1 passes, the array is guaranteed to be sorted

Improvements
- don't need to run inner loop until n - 1 each time
  - can stop at n - i since the rightmost i elements are sorted into place
- as soon as we have a pass with no swaps, can break out early
  - this makes the best case linear time since we loop once over an already sorted array
  - but complexity is still O(n<sup>2</sup>)

## Insertion Sort
*Bad, but less work than Selection and Bubble.<br>
Partition array into sorted and unsorted. Move items into sorted section one by one.*
  - Time Complexity: O(n<sup>2</sup>)
  - Space Complexity: O(1)
  - In-place
#### Walkthrough:
- treat the array as if it's in two parts
- the left part is sorted and the right part is unsorted
- initially only the first element is in the left part
- loop over the unsorted part and insert each element into the sorted part
- if an element is smaller than sorted elements, shift them to the right and insert the new element into the gap

## Merge Sort
*A fast, recursive algorithm that takes up a lot of space*
  - Time Complexity: O(nlogn)
  - Space Complexity: Θ(n)
  - Stable
  - Divide and Conquer
#### Walkthrough:
*MergeSort()*
- create two new arrays, each half the size of the original
- copy half of the elements into each
- call this function recursively on each half
- merge the two halves back together by calling Merge()

*Merge()*
- takes in two sub-arrays to be merged and a parent, destination array
- have a index counter for each sub array, starting at zero
- loop over parent array starting and index 0
- pick the smallest element between the two sub array values using their respective index counters
- add that element to the parent array
- increment that sub-array's counter and continue with the loop
- if one sub-array ends before the other, just add the remaining sub-array's element to the parent in order

*Additional Notes*
- MergeSort() will recurse down to the leaves (single element arrays) before calling Merge() 
- Merge() is where all the actual sorting takes place
  - stitches the sub-arrays back together again, smallest to largest
- Not in-place - we have to create new sub arrays each level of recursion
  - it would be Θ(nlogn) space without clearing sub-arrays at each return

## Quick Sort
*A fast and efficient algorithm used in many standard library sorts*
  - Time Complexity: 
    - O(nlogn) *average case (typical)*
    - O(n<sup>2</sup>) *worst case (very rare)*
  - Space Complexity: 
    - O(logn) *average case*
    - O(n) *worst case*
  - In-place
  - Not Stable
  - Divide and Conquer
#### Walkthrough:
- select one element at random - *the pivot*
- move all elements smaller than pivot to left of it
- move all elements greater than pivot to right of it
- break array into two sub-arrays using pivot as break
- recursively apply process on sub-arrays
- base case is single element sub-arrays 
#### Additional Notes:
- at each level of recursion we do linear (n) amount of work shifting elements around pivot
- so the efficiency of Quick Sort depends on the number of recursions 
- which directly depends on how good the *pivots* are
  - best case: each pivot perfectly divides its array into two equal sized sub-arrays
    - then the number of recursions is log(n) - fewest possible
    - total work done is then n * log(n)
  - worst case: each pivot divides array into sub-arrays of size 1 and n - 1
    - then the number of recursions is linear (n)
    - total work is then n * n
  - in practice, pivot selection is usually quite good

---

#### Notes for Analysis of Counting-based Sorts:
- sorting is done on integer keys
- k = size of key space
    - the number of possible keys
    - e.g. 2<sup>32</sup> - 1 for a 32 bit unsigned integer
    
## Counting Sort
*Fast(ish) and easy algorithm that takes up space.*
  - Time Complexity: O(n + k)
  - Space Complexity: O(n + k)
  - time and space efficiency both depend heavily on k
#### Walkthrough:
- create a large array, L, with a slot for every potential key
  - each slot holds a linked list of items to allow for duplicate keys
- loop over input array:
  - add each element to the slot in L where L[i] equals key
- loop over L array:
  - for each slot - add the items stored there into the output array
- the output array will be in sorted order

#### Additional Notes:
- Counting Sort is a fast and easy technique for sorting keys on a computer
- the big drawback is that you have to create a *very large* array for most key spaces
  - take up space
  - walking over all those empty slots when assembling the sorted array wastes time
- Radix Sort uses the Counting Sort algorithm, but divides up the key space into small, managable sizes
- called *Counting Sort* because in the case where you're just sorting integer keys without values attached
  - your array L can just keep a running count of each key as it loops over the input
  - rather than holding a linked-list of data values

## Radix Sort
*Linear(ish) time sorting using Counting Sort as a subroutine* 
- Time Complexity: O(nlog<sub>n</sub>(k)) 
#### Walkthrough:
- Sort integers by least significant digit of keys using Counting Sort
- *Repeat d times...*
- Sort integers by most significant digit of keys   

#### Analysis of Time Complexity:
- each Counting sub-sort takes O(n + b)
  - where b = key space for sub-sort
- have to run sub-sort d times
  - where d = log<sub>b</sub>(k)
  - meaning we're taking the total input keyspace k, dividing it into d chunks of smaller spaces b.
- giving a total time of O(n + b) * d
  - minimize this value when b = ϴ(n)
  - this makes d = log<sub>n</sub>(k)
- then we have O(n + n) * log<sub>n</sub>(k) = O(nlogn<sub>n</sub>(k))
- linear when k is polynomial in n

