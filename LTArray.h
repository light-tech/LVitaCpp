#ifndef _LVITACPP_DATA_STRUCTURE_LTARRAY
#define _LVITACPP_DATA_STRUCTURE_LTARRAY

#include "LCommon.h"

/// Auto-expand array
/// _ElementType: type of array elements
/// _IndexType: type of array index depending on how big the array is expected in application
/// must be an arithmetic type (for example, short/int/char/wchar_t/...)
template <typename _ElementType, typename _IndexType>
class LTArray
{
public:
	LTArray(_IndexType initial_size)
	{
		Init(initial_size);
	}

	inline void Init(_IndexType initial_size)
	{
		elements = nullptr;
		num_elements = 0;
		if (initial_size > 0)
			Resize(initial_size);
		else
			size = 0;
	}

	inline void Resize(_IndexType new_size)
	{
		elements = (_ElementType*)realloc(elements, new_size * sizeof(_ElementType));
		size = new_size;
	}

	inline void Clear(void (*free_element)(_ElementType) = nullptr)
	{
		if (free_element != nullptr)
		{
			for(_IndexType i = 0; i < num_elements; i++)
				free_element(elements[i]);
		}
		num_elements = 0;
	}

	template <typename _State>
	inline void ForEach(void (*action_on_element)(_ElementType, _State &state), _State &state)
	{
		for(_IndexType i = 0; i < num_elements; i++)
			action_on_element(elements[i], state);
	}

	void Print(
		void (*print_element)(_ElementType),
		void (*print_separator)()
	)
	{
		if (num_elements > 0)
			print_element(elements[0]);

		for (_IndexType i = 1; i < num_elements; i++)
		{
			print_separator();
			print_element(elements[i]);
		}
	}

	inline void Append(const _ElementType &e)
	{
		if (num_elements == size)
			Resize(size + 1);
		elements[num_elements] = e;
		num_elements++;
	}

	inline void Push(const _ElementType &e)
	{
		Append(e);
	}

	inline void Pop()
	{
		if (num_elements > 0)
			num_elements--;
	}

	inline int Count()
	{
		return this->num_elements;
	}

	inline _IndexType Size()
	{
		return this->size;
	}

	inline _ElementType &operator[](_IndexType index)
	{
		return this->elements[index];
	}

	inline void InsertAt(_IndexType index, const _ElementType &e)
	{
		if (this->num_elements == size)
			Resize((size << 1) + 1);
		for(_IndexType i = this->num_elements - 1; i >= index; i--)
			this->elements[i + 1] = this->elements[i];
		this->elements[index] = e;
		this->num_elements++;
	}

	inline void Erase(
		_IndexType from,
		_IndexType to,
		void (*free_element)(_ElementType) = nullptr
	)
	{
		// assert(from <= to && to <= num_elements);
		if (free_element != nullptr)
		{
			for(_IndexType i = from; i < to; i++)
			{
				free_element(this->elements[i]);
			}
		}

		// Number of elements to move [to..num_elements)
		auto num_move = num_elements - to;
		for(_IndexType i = 0; i < num_move; i++)
		{
			this->elements[from + i] = this->elements[to + i];
		}
		this->num_elements -= (to - from);
	}

	_ElementType *elements;

protected:
	_IndexType num_elements;
	_IndexType size;
};

#endif