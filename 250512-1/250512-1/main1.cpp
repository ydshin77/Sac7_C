#include <iostream>

template <typename T>
class CArrayTemplate
{
public:
	CArrayTemplate()
	{
		mArray = new T[mCapacity];
	}

	~CArrayTemplate()
	{
		delete[] mArray;
	}

private:
	T* mArray = nullptr;
	int mSize = 0;
	int mCapacity = 2;

public:
	T& operator [] (int Index)
	{
		return mArray[Index];
	}

	const T& operator [] (int Index) const
	{
		return mArray[Index];
	}

};

int main()
{
	CArrayTemplate<int>		IntArr;
	CArrayTemplate<float>	FloatArr;

	return 0;
}