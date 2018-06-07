#ifndef _LVITACPP_DATA_STRUCTURE_LTPAIR
#define _LVITACPP_DATA_STRUCTURE_LTPAIR

/// Pair of objects, to facilitate implementation of Map<> using sorted array
template <typename _FirstType, typename _SecondType>
class LTPair
{
public:
	LTPair() { }
	LTPair(_FirstType fst, _SecondType sec)
	{
		first = fst;
		second = sec;
	}
	_FirstType first;
	_SecondType second;
};

#endif
