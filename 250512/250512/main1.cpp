
#include <iostream>

/*
면접에서 많이 물어보는 내용

operator : 연산자 재정의 기능이다.
구조체나 클래스에서 활용할 수 있으며 원하는 연산자를 재정의하여
구조체나 클래스에 연산자를 이용할 수 있게 해준다.

반환타입 operator 연산자 (오른쪽에 연산될 값)
{
}

10 + 20 일 경우 오른쪽에 연산될 값은 20이다.
*/

class COperator
{
public:
	COperator()
	{
	}

	COperator(int Num) :
		mNumber(Num)
	{
		printf("생성\n");
	}

	~COperator()
	{
	}

private:
	int		mNumber = 100;

public:
	void operator = (int Num)
	{
		printf("대입\n");
		mNumber = Num;
	}

	void operator = (float Num)
	{
		mNumber = Num;
	}

public:
	void Output()
	{
		printf("Number = %d\n", mNumber);
	}

	void OutputConst()	const
	{
		printf("Number = %d\n", mNumber);
	}

	COperator operator + (const COperator& oper)	const
	{
		COperator	result;
		result.mNumber = mNumber + oper.mNumber;

		return result;
	}

	COperator operator + (int Num)	const
	{
		COperator	result;
		result.mNumber = mNumber + Num;

		return result;
	}

	COperator Add(int Num)	const
	{
		COperator	result;
		result.mNumber = mNumber + Num;

		return result;
	}

	// ++이 왼쪽에 오는 전위연산.
	void operator ++ ()
	{
		++mNumber;
	}

	// ++이 오른쪽에 오는 후위연산.
	void operator ++ (int)
	{
		++mNumber;
	}
};

class CArray
{
public:
	CArray()
	{
	}

	~CArray()
	{
	}

private:
	int		mArray[10] = {};

public:
	int& operator [] (int Index)
	{
		return mArray[Index];
	}

	const int& operator [] (int Index)	const
	{
		return mArray[Index];
	}
};

class CPointer
{
public:
	CPointer()
	{
	}

	CPointer(COperator* pt) :
		mPointer(pt)
	{
	}

	~CPointer()
	{
	}

public:
	COperator* mPointer = nullptr;

public:
	COperator* operator -> ()
	{
		return mPointer;
	}

	const COperator* operator -> ()	const
	{
		return mPointer;
	}
};

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
	int	mSize = 0;
	int	mCapacity = 2;

public:
	T& operator [] (int Index)
	{
		return mArray[Index];
	}

	const T& operator [] (int Index)	const
	{
		return mArray[Index];
	}
};

int main()
{
	// int타입을 인자로 가지고 있는 생성자가 호출된다.
	COperator		oper = 30;

	// 대입 연산자가 호출된다.
	oper = 500;

	oper = 3.14f;

	oper.Output();

	COperator	oper1 = 40, result;

	result = oper + oper1;

	result.Output();

	result = oper + 200;

	result.Output();

	result = oper.Add(300);

	result.Output();

	CArray	Arr;

	Arr[0] = 30;

	const CArray	cArr;

	//cArr[0] = 50;
	int Num = cArr[0];

	CPointer	pt;
	pt.mPointer = &oper;

	// -> 연산자를 호출하여 COperator* 를 반환하기 때문에
	// mPointer-> 가 된다.
	pt->Output();

	const CPointer	cpt = &oper;

	cpt->OutputConst();

	++oper;

	oper++;

	CArrayTemplate<int>		IntArr;
	CArrayTemplate<float>	FloatArr;

	return 0;
}

// 자료구조의 기본 : 동적 배열, 더블링크드 배열 -> 이걸 알아야 다음 것도 이해 가능