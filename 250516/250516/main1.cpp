
#include <iostream>
#include <stack>
#include <assert.h>

/*
자료구조 스택 : 후입선출의 자료구조이다.
나중에 추가한 데이터가 먼저 나오는 방식이다.

자료구조 큐 : 선입선출의 자료구조이다.
먼저 추가한 데이터가 먼저 나오는 방식이다.
*/

// 비타입 템플릿 인자 : 가변타입이 아닌 고정된 타입으로 템플릿 인자를
// 만들어주는 방식이다. 상수로 인식된다.
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

class CMonster
{
public:
	CMonster()
	{
		printf("CMonster 생성자\n");
	}

	~CMonster()
	{
		printf("CMonster 소멸자\n");
	}

public:
	char	mName[32] = {};

private:
	static CMemoryPool<CMonster>	mMonsterPool;

public:
	static void* operator new (size_t Size)
	{
		return mMonsterPool.Alloc();
	}

	static void operator delete (void* Ptr)
	{
		mMonsterPool.DeAlloc((CMonster*)Ptr);
	}
};

CMemoryPool<CMonster> CMonster::mMonsterPool;

int main()
{
	//CMemoryPool<CMonster>	MonsterPool;

	//CMonster* Monster1 = MonsterPool.Alloc();
	// placement new 를 이용하여 생성자가 호출될 수 있도록 한다.
	//new (Monster1) CMonster;

	//MonsterPool.DeAlloc(Monster1);
	CMonster* Monster2 = new CMonster;


	delete Monster2;

	return 0;
}
