/**
 * Sorted array data structure, allow insertion and deletion of elements in sorted manner using binary search.
 * This template consists of two generic type parameter:
 *  _ElementType : type of the elements in the array
 *  _IndexType : type of the index/size of the array
 * The second parameter _IndexType allows for more efficient storage. For instance, if the array is not so large,
 * one can use `short` or `unsigned char` instead of `int`.
 * 
 * This data structure is the base to implement map and tree.
 */

#ifndef _LVITACPP_DATA_STRUCTURE_LT_SORTED_ARRAY
#define _LVITACPP_DATA_STRUCTURE_LT_SORTED_ARRAY

#include "LTArray.h"

/// Auto-expand sorted array
template <typename _ElementType, typename _IndexType>
class LTSortedArray : public LTArray<_ElementType, _IndexType>
{
public:
	LTSortedArray(_IndexType initial_size) : LTArray<_ElementType, _IndexType>(initial_size)
	{
	}

	template <typename T>
	inline int Find(
		// Element to look for
		T e,
		// The first argument will always be the `element` we are looking for whereas the second argument is an element of the array
		int (*compare_element)(T, _ElementType),
		// Output parameter; equal 0 if element can be found in which case the return value is its position in the array
		int &c
	)
	{
		int l = 0;
		int h = this->num_elements;
		while (l < h)
		{
			int m = (l + h) / 2;
			c = compare_element(e, this->elements[m]);
			if (c == 0)
			{
				return m;
			}
			else if (c < 0)
			{
				h = m;
			}
			else
			{
				l = m + 1;
			}
		}

		return l;
	}

	// Return the position of the inserted element
	// Check if elements[return] == nullptr to know if it is there or not
	// Alternatively, check if c == 0
	template <typename T>
	int Insert(
		T e,
		int (*compare_element)(T , _ElementType),
		int &c
	)
	{
		int l = Find(e, compare_element, c);
		if (c == 0)
			return l;

		// l == h & c != 0, & should insert at l
		if (this->num_elements == this->size)
		{
			this->Resize(this->size + 1);
		}

		// Shift the elements l .. end
		for (int i = this->num_elements - 1; i >= l; i--)
			this->elements[i + 1] = this->elements[i];
		this->elements[l] = nullptr;
		this->num_elements++;

		return l;
	}

	// Remove an element
	template <typename T>
	int Remove(
		T e,
		int (*compare_element)(T , _ElementType),
		int &c
	)
	{
		int l = Find(e, compare_element, c);

		// Element not found, nothing to do
		if (c != 0)
			return -1;

		// Else, shift the elements
		for (int i = l + 1; i < this->num_elements; i++)
			this->elements[i - 1] = this->elements[i];
		this->num_elements--;

		return l;
	}
};

#endif