
#include <iostream>
#include <stack>
#include <assert.h>
#include <crtdbg.h>

template <typename T, int PoolSize = 1024>
class CMemoryPool
{
public:
	CMemoryPool()
	{
		// ::operator new 를 하면 전역연산자 new를 호출한다.
		// 생성자 호출 없이 순수하게 메모리만 할당하는 방식이다.
		mMemory = (T*)(::operator new(PoolSize * sizeof(T)));

		// C언어 스타일의 메모리 생성방식.
		//mMemory = (T*)malloc(PoolSize * sizeof(T));

		// 스택에 인덱스 시작 주소를 담아둔다.
		for (int i = 0; i < PoolSize; ++i)
		{
			mAllocMemory.push(mMemory + i);
		}
	}

	~CMemoryPool()
	{
		::operator delete(mMemory);

		//free(mMemory);
	}

public:
	T* Alloc()
	{
		// 더이상 할당할 수 있는 공간이 없을 경우 예외처리를 해준다.
		assert(!mAllocMemory.empty() && "Memory Pool Is Empty");

		// top을 이용해서 마지막에 추가된 데이터를 얻어온다.
		T* Ptr = mAllocMemory.top();

		// 마지막에 추가된 데이터를 제거한다.
		mAllocMemory.pop();

		// placement new
		// 1. 메모리 할당
		// 2. 객체 생성자 호출
		// 이미 할당된 주소에 객체를 생성할 때 사용한다.
		// 새로 메모리를 할당하는 방식이 아니다.
		//::new (Ptr) T;

		return Ptr;
	}

	void DeAlloc(T* Ptr)
	{
		// 메모리를 풀에 반환할 때 소멸자를 호출하고 싶을 경우
		//Ptr->~T();

		mAllocMemory.push(Ptr);
	}

private:
	T* mMemory = nullptr;
	std::stack<T*>	mAllocMemory;
};

template <int BlockSize, int BlockCount>
class CShareMemoryPool
{
public:
	CShareMemoryPool()
	{
		mMemory = (unsigned char*)(::operator new(BlockSize * BlockCount));

		for (int i = 0; i < BlockCount; ++i)
		{
			mAllocMemory.push(mMemory + (i * BlockSize));
		}

		// ::operator new 를 하면 전역연산자 new를 호출한다.
		// 생성자 호출 없이 순수하게 메모리만 할당하는 방식이다.
		//mMemory = (T*)(::operator new(PoolSize * sizeof(T)));

		//// C언어 스타일의 메모리 생성방식.
		////mMemory = (T*)malloc(PoolSize * sizeof(T));

		//// 스택에 인덱스 시작 주소를 담아둔다.
		//for (int i = 0; i < PoolSize; ++i)
		//{
		//	mAllocMemory.push(mMemory + i);
		//}
	}

	~CShareMemoryPool()
	{
		::operator delete(mMemory);

		//free(mMemory);
	}

public:
	template <typename T>
	T* Alloc()
	{
		assert(sizeof(T) <= BlockSize);

		// 더이상 할당할 수 있는 공간이 없을 경우 예외처리를 해준다.
		assert(!mAllocMemory.empty() && "Memory Pool Is Empty");

		// top을 이용해서 마지막에 추가된 데이터를 얻어온다.
		T* Ptr = (T*)mAllocMemory.top();

		// 마지막에 추가된 데이터를 제거한다.
		mAllocMemory.pop();

		// placement new
		// 1. 메모리 할당
		// 2. 객체 생성자 호출
		// 이미 할당된 주소에 객체를 생성할 때 사용한다.
		// 새로 메모리를 할당하는 방식이 아니다.
		//::new (Ptr) T;

		return Ptr;
	}

	void DeAlloc(void* Ptr)
	{
		// 메모리를 풀에 반환할 때 소멸자를 호출하고 싶을 경우
		//Ptr->~T();

		mAllocMemory.push((unsigned char*)Ptr);
	}

private:
	unsigned char* mMemory = nullptr;
	std::stack<unsigned char*>	mAllocMemory;
};

class CMonster
{
public:
	CMonster()
	{
		printf("CMonster 생성자\n");
	}

	virtual ~CMonster()
	{
		printf("CMonster 소멸자\n");
	}

protected:
	static int		mMaxSize;

public:
	template <typename T>
	static void ComputeMaxSize()
	{
		size_t	Size = sizeof(T);
		if (Size > mMaxSize)
			mMaxSize = (int)Size;
	}

protected:
	static CShareMemoryPool<16, 200>	mShareMemoryPool;
};

class CGoblin :
	public CMonster
{
public:
	CGoblin()
	{
		printf("CGoblin 생성자\n");
	}

	virtual ~CGoblin()
	{
		printf("CGoblin 소멸자\n");
	}

private:
	static CMemoryPool<CGoblin>	mGoblinPool;

public:
	static void* operator new (size_t Size)
	{
		return mShareMemoryPool.Alloc<CGoblin>();
	}

	static void operator delete (void* Ptr)
	{
		mShareMemoryPool.DeAlloc(Ptr);
	}
};

class COrc :
	public CMonster
{
public:
	COrc()
	{
		printf("COrc 생성자\n");
	}

	virtual ~COrc()
	{
		printf("COrc 소멸자\n");
	}

public:
	int		mNumber = 100;

private:
	static CMemoryPool<COrc>	mOrcPool;

public:
	static void* operator new (size_t Size)
	{
		return mShareMemoryPool.Alloc<COrc>();
	}

	static void operator delete (void* Ptr)
	{
		mShareMemoryPool.DeAlloc(Ptr);
	}
};

CMemoryPool<CGoblin> CGoblin::mGoblinPool;
CMemoryPool<COrc> COrc::mOrcPool;
CShareMemoryPool<16, 200> CMonster::mShareMemoryPool;

int CMonster::mMaxSize = 0;


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1309);

	//int* Test = new int;

	CMonster::ComputeMaxSize<CGoblin>();
	CMonster::ComputeMaxSize<COrc>();

	printf("Goblin Size : %d\n", sizeof(CGoblin));
	printf("Orc Size : %d\n", sizeof(COrc));

	CMonster* Monster[10] = {};

	Monster[0] = new CGoblin;
	Monster[1] = new COrc;


	delete Monster[0];
	delete Monster[1];

	return 0;
}
