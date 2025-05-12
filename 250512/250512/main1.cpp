
#include <iostream>

/*
�������� ���� ����� ����

operator : ������ ������ ����̴�.
����ü�� Ŭ�������� Ȱ���� �� ������ ���ϴ� �����ڸ� �������Ͽ�
����ü�� Ŭ������ �����ڸ� �̿��� �� �ְ� ���ش�.

��ȯŸ�� operator ������ (�����ʿ� ����� ��)
{
}

10 + 20 �� ��� �����ʿ� ����� ���� 20�̴�.
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
		printf("����\n");
	}

	~COperator()
	{
	}

private:
	int		mNumber = 100;

public:
	void operator = (int Num)
	{
		printf("����\n");
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

	// ++�� ���ʿ� ���� ��������.
	void operator ++ ()
	{
		++mNumber;
	}

	// ++�� �����ʿ� ���� ��������.
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
	// intŸ���� ���ڷ� ������ �ִ� �����ڰ� ȣ��ȴ�.
	COperator		oper = 30;

	// ���� �����ڰ� ȣ��ȴ�.
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

	// -> �����ڸ� ȣ���Ͽ� COperator* �� ��ȯ�ϱ� ������
	// mPointer-> �� �ȴ�.
	pt->Output();

	const CPointer	cpt = &oper;

	cpt->OutputConst();

	++oper;

	oper++;

	CArrayTemplate<int>		IntArr;
	CArrayTemplate<float>	FloatArr;

	return 0;
}

// �ڷᱸ���� �⺻ : ���� �迭, ����ũ�� �迭 -> �̰� �˾ƾ� ���� �͵� ���� ����