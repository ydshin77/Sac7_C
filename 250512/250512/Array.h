#pragma once

// 경고를 만들어주는 기능 (디버깅할 때 자주 활용)
#include <assert.h>

// 어떤 타입이든 지정할 수 있는 클래스
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
	// 자동으로 공간이 늘어나는 배열
	// T Data를 하면 1024바이트를 두 번 복사함
	// T&면 값을 변경할 수 있기 때문에 const가 있어야 함
	void push_back(const T& Data)
	{
		// 배열이 꽉 찼는지 확인
		if (mSize == mCapacity)
		{
			// 새로운 공간을 기존 공간의 2배 크기로 생성
			mCapacity *= 2;

			T* Array = new T[mCapacity];

			// 새로운 공간에 기존 배열의 내용을 복사
			memcpy(Array, mArray, sizeof(T) * mSize);

			// 기존 배열을 제거
			delete[] mArray;

			// 새로운 배열의 주소를 멤버 포인터에 넣어줌
			mArray = Array;
		}

		mArray[mSize] = Data;
		++mSize;

	}

	// 마지막에 추가된 데이터를 제거
	void pop_back()
	{
		// 인자로 조건을 주고 거짓일 경우 프로그램을 강제로 종료시킴
		// assert는 디버그 모드일 때만 동작함
		assert(mSize > 0);

		--mSize;
	}

	int size() const
	{
		return mSize;
	}

	// 배열은 앞의 인덱스를 지우거나 덮어쓰고 하는 기능을 지원하지 않음 (계속 반복 돌아야 돼서)
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

	// 인자로 들어온 값을 찾아서 제거
	void erase(const T& Data)
	{
		// 제거할 뒤의 값을 1칸씩 앞으로 이동시켜줌
		for (int i = 0; i < mSize; ++i)
		{
			if (mArray[i] == Data)
			{
				eraseIndex(i);
				break;
			}
		}

	}

	// 인자로 들어온 인덱스 제거
	void eraseIndex(int Index)
	{
		assert(0 <= Index && Index < mSize);

		for (int i = Index; i < mSize - 1; ++i)
		{
			mArray[i] = mArray[i + 1];
		}
	}

	// 인자로 들어온 인덱스 제거
	void eraseIndex1(int Index)
	{
		assert(0 <= Index && Index < mSize);

		// 마지막에 추가된 데이터를 현재 인덱스에 대입하고 추가된 수를 줄여줌
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

