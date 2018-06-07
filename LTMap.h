/**
 * Map data structure template
 *
 * A map (also called `associated list`, `table`, ...) is a common data structure to provide key->value look up service.
 * The main interface consists of
 *  - Put(key, value) : associate a value to a key
 *  - Lookup(key) : find the value associated to a key
 *
 * I implement this data structure using sorted array of key-value pairs.
 *
 * This data structure is used in LawTeX to store SVG text -> SVG document, color string to color brushes,
 * file path -> document, etc.
 */

#ifndef _LVITACPP_DATA_STRUCTURE_LTMAP
#define _LVITACPP_DATA_STRUCTURE_LTMAP

#include "LTPair.h"
#include "LTSortedArray.h"

template <typename _KeyType, typename _ValueType>
inline int default_compare_key_pair(_KeyType e, LTPair<_KeyType, _ValueType> *p)
{
	return e - p->first;
}

/// Map data structure
/// I implement using a sorted array of LPair[first = key; second = value]
template <typename _KeyType, typename _ValueType>
class LTMap : public LTSortedArray<LTPair<_KeyType, _ValueType>*, unsigned int>
{
public:
	LTMap() : LTSortedArray<LTPair<_KeyType, _ValueType>*, unsigned int>(5)
	{
	}

	// Set the key->value binding; return the old value (if any)
	void Put(
		_KeyType key,
		_ValueType value,
		int (*compare_keys)(_KeyType, LTPair<_KeyType, _ValueType>*) = default_compare_key_pair
	)
	{
		int c = -1;
		int p = this->Insert(key, compare_keys, c);
		if (c != 0)
		{
			this->elements[p] = (LTPair<_KeyType, _ValueType>*)realloc(nullptr, sizeof(LTPair<_KeyType, _ValueType>));
			this->elements[p]->first = key;
		}
		this->elements[p]->second = value;
	}

	void Remove(
		_KeyType key,
		int(*compare_keys)(_KeyType, LTPair<_KeyType, _ValueType>*) = default_compare_key_pair
	)
	{
		int c;
		this->Remove(key, compare_keys, c);
	}

	// Look up the current binding for key; return nullptr if there is no binding
	_ValueType Lookup(
		_KeyType key,
		_ValueType not_found,
		int (*compare_keys)(_KeyType, LTPair<_KeyType, _ValueType>*) = default_compare_key_pair
	)
	{
		int c = -1;
		int p = this->Find(key, compare_keys, c);
		if (c == 0)
			return this->elements[p]->second;
		else
			return not_found;
	}

	void Clear(
		void (*free_key)(_KeyType),
		void (*free_value)(_ValueType)
	)
	{
		for (int i = 0; i < this->num_elements; i++)
		{
			auto p = this->elements[i];
			if (free_key != nullptr)
				free_key(p->first);
			free_value(p->second);
			delete p;
			this->elements[i] = nullptr;
		}
		this->num_elements = 0;
	}
};

#endif