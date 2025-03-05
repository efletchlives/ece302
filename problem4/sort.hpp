#ifndef _SORT_HPP
#define _SORT_HPP

#include "list.hpp"

template<typename T>
// used the quick sort lecture notes to help
void quick_sort(List<T>& list, int first, int last)
{
	// if first and last index are invalid, throw exception
	if(first < 0 || last < 0) {
		throw std::invalid_argument("invalid range since first/last is/are invalid positions");
	}
	if (first < last) { // if the first position is less than the last position

		int pivot = partition(list, first, last); // finds the pivot point
		quick_sort(list, first, pivot-1); // sorts the right side, adjusting for 1 indexing
		quick_sort(list, pivot + 1, last); // sorts the left side, adjusting for 1 indexing

	}
}

template <typename T>
int partition(List<T>& list, int first, int last) {
	// if first index is greater than last index, partitioning is not possible so exception is thrown
	if(first > last) {
		throw std::invalid_argument("invalid range since first index > last index");
	}
	T pivot = list.getEntry(last); // choose the last element as pivot
	int pos = first-1; // position to swap from

	for(int i=first;i<last;i++) { // loops through the entire list minus the pivot point
		if(list.getEntry(i) <= pivot) { // if current element is less than or equal to the position of the pivot point
			pos++; // increment position to swap

			// swap the first element with the current element
			list.moveEntry(i,pos);
		}
	}

	// place pivot in the correct position, so all elements before are <= pivot and all elements after are >= pivot
	list.moveEntry(last,pos+1);
	return pos+1; // returns the index of the pivot
}

#endif
