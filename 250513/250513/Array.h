#pragma once

#include <assert.h>

template <typename T>
class CArray
{
public:
	CArray()
	{
		mArray = new T[mCapacity];
	}

	~CArray()
	{
		delete[] mArray;
	}

private:
	T* mArray = nullptr;
	int	mSize = 0;
	int	mCapacity = 2;

public:
	void push_back(const T& Data)
	{
		// �迭�� �� á���� Ȯ���Ѵ�.
		if (mSize == mCapacity)
		{
			// ���ο� ������ ���� ������ 2�� ũ��� �����Ѵ�.
			mCapacity *= 2;

			T* Array = new T[mCapacity];

			// ���ο� ������ ���� �迭�� ������ �����Ѵ�.
			memcpy(Array, mArray, sizeof(T) * mSize);

			// ���� �迭�� �����Ѵ�.
			delete[]	mArray;

			// ���ο� �迭�� �ּҸ� ��� �����Ϳ� �־��ش�.
			mArray = Array;
		}

		mArray[mSize] = Data;
		++mSize;
	}

	// �������� �߰��� �����͸� �����Ѵ�.
	void pop_back()
	{
		// ���ڷ� ������ �ְ� ������ ��� ���α׷��� �����Ų��.
		// assert�� ����� ����϶��� �����Ѵ�.
		assert(mSize > 0);

		--mSize;
	}

	int size()	const
	{
		return mSize;
	}

	int capacity()	const
	{
		return mCapacity;
	}

	bool empty()	const
	{
		return mSize == 0;
	}

	void clear()
	{
		mSize = 0;
	}

	// ���ڷ� ���� ���� ã�Ƽ� �����Ѵ�.
	void erase(const T& Data)
	{
		// ������ ���� ���� 1ĭ�� ������ �̵������ش�.
		for (int i = 0; i < mSize; ++i)
		{
			if (mArray[i] == Data)
			{
				eraseIndex(i);
				break;
			}
		}
	}

	// ���ڷ� ���� �ε����� �����Ѵ�.
	void eraseIndex(int Index)
	{
		assert(0 <= Index && Index < mSize);

		for (int i = Index; i < mSize - 1; ++i)
		{
			mArray[i] = mArray[i + 1];
		}

		--mSize;
	}

	void eraseIndex1(int Index)
	{
		assert(0 <= Index && Index < mSize);

		// �������� �߰��� �����͸� ���� �ε����� �����ϰ�
		// �߰��� ���� �ٿ��ش�.
		mArray[Index] = mArray[mSize - 1];

		--mSize;
	}

	T& operator [] (int Index)
	{
		assert(0 <= Index && Index < mSize);

		return mArray[Index];
	}

	const T& operator [] (int Index)	const
	{
		assert(0 <= Index && Index < mSize);

		return mArray[Index];
	}
};

