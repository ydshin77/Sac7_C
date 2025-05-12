#pragma once

// ��� ������ִ� ��� (������� �� ���� Ȱ��)
#include <assert.h>

// � Ÿ���̵� ������ �� �ִ� Ŭ����
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
	int mSize = 0;
	int mCapacity = 2;

public:
	// �ڵ����� ������ �þ�� �迭
	// T Data�� �ϸ� 1024����Ʈ�� �� �� ������
	// T&�� ���� ������ �� �ֱ� ������ const�� �־�� ��
	void push_back(const T& Data)
	{
		// �迭�� �� á���� Ȯ��
		if (mSize == mCapacity)
		{
			// ���ο� ������ ���� ������ 2�� ũ��� ����
			mCapacity *= 2;

			T* Array = new T[mCapacity];

			// ���ο� ������ ���� �迭�� ������ ����
			memcpy(Array, mArray, sizeof(T) * mSize);

			// ���� �迭�� ����
			delete[] mArray;

			// ���ο� �迭�� �ּҸ� ��� �����Ϳ� �־���
			mArray = Array;
		}

		mArray[mSize] = Data;
		++mSize;

	}

	// �������� �߰��� �����͸� ����
	void pop_back()
	{
		// ���ڷ� ������ �ְ� ������ ��� ���α׷��� ������ �����Ŵ
		// assert�� ����� ����� ���� ������
		assert(mSize > 0);

		--mSize;
	}

	int size() const
	{
		return mSize;
	}

	// �迭�� ���� �ε����� ����ų� ����� �ϴ� ����� �������� ���� (��� �ݺ� ���ƾ� �ż�)
	int capacity() const
	{
		return mCapacity;
	}

	bool empty() const
	{
		return mSize == 0;
	}

	void clear()
	{
		mSize = 0;
	}

	// ���ڷ� ���� ���� ã�Ƽ� ����
	void erase(const T& Data)
	{
		// ������ ���� ���� 1ĭ�� ������ �̵�������
		for (int i = 0; i < mSize; ++i)
		{
			if (mArray[i] == Data)
			{
				eraseIndex(i);
				break;
			}
		}

	}

	// ���ڷ� ���� �ε��� ����
	void eraseIndex(int Index)
	{
		assert(0 <= Index && Index < mSize);

		for (int i = Index; i < mSize - 1; ++i)
		{
			mArray[i] = mArray[i + 1];
		}
	}

	// ���ڷ� ���� �ε��� ����
	void eraseIndex1(int Index)
	{
		assert(0 <= Index && Index < mSize);

		// �������� �߰��� �����͸� ���� �ε����� �����ϰ� �߰��� ���� �ٿ���
		mArray[Index] = mArray[mSize - 1];

		--mSize;
	}

	T& operator [] (int Index)
	{
		assert(0 <= Index && Index < mSize);

		return mArray[Index];
	}

	const T& operator [] (int Index) const
	{
		assert(0 <= Index && Index < mSize);

		return mArray[Index];
	}

};

