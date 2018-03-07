# Sorting Algorithms
This repo contains templated implementations of common sorting algorithms. 
<br>
All sorted types are of generic type T, except for Counting and Radix sort, where the keys
are assumed to be integers.
<br>
Below is a brief description of each sorting algorithm, it's pros and cons, and its time and space complexity.

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
2. All the integers fits into a Word size on our machine (typically 32 or 64 bits)<br>
In this model we're taking advantage of the fact that we can do more simple arithmetic operations (e.g. addition) than comparisons in the same amount of time.

### Notes on Algorithm Properties
- Stable : An algorithm is stable if two elements with the same key remain in the same relative order after being sorted.<br>
e.g. In my original, unsorted array, element A comes before element B, and both have a key of 2 for sorting. Then my algorithm is stable if in the final, sorted array, A is still before B.
- In-place : An algorithm is in-place if it uses O(1) space for sorting.<br>
So aside from a few temporary variables, the amount of space used is negligible and independent of the size of the array to be sorted.

*Algorithm breakdowns coming soon...*
