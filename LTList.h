#ifndef _LVITACPP_DATA_STRUCTURE_LTLIST
#define _LVITACPP_DATA_STRUCTURE_LTLIST

/// Linked list and stack
template <typename _ElementType>
class LTList
{
public:
	LTList(_ElementType d)
	{
		data = d;
		next = nullptr;
	}

	_ElementType data;
	LTList<_ElementType> *next;
};

// Push a new item to the stack, the `data` field will point to item
template <typename _ElementType>
static LTList<_ElementType> *Push(
	LTList<_ElementType> *top,
	_ElementType &item
)
{
	auto new_top = new LTList<_ElementType>(item);
	new_top->next = top;

	return new_top;
}

#endif