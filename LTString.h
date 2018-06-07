class LString
{
public:
	LString(wchar_t* s, int l, bool own = false)
	{
		str = s;
		length = l;
		owned = own;
	}
	~LString()
	{
		if (owned)
			delete[] str;
	}
	wchar_t *str;
	int length;
	bool owned;
};