
#include <iostream>
#include <stack>
#include <assert.h>
#include <crtdbg.h>

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
	static CShareMemoryPool<16, 200>	mShareMemoryPool;
};

CShareMemoryPool<16, 200> CMonster::mShareMemoryPool;

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

template <typename T>
class TSharedPtr
{
	class CRef
	{
	public:
		CRef()
		{
		}

		~CRef()
		{
			if (mPtr)
				delete mPtr;
		}

	public:
		T* mPtr = nullptr;
		int	mRefCount = 0;
	};

public:
	TSharedPtr()
	{
		mRef = new CRef;
		mRef->mPtr = new T;
		++mRef->mRefCount;
	}

	TSharedPtr(const T& Ptr)
	{
		mRef = new CRef;
		++mRef->mRefCount;

		mRef->mPtr = new T;
		*mRef->mPtr = Ptr;
	}

	TSharedPtr(T* Ptr)
	{
		mRef = new CRef;
		++mRef->mRefCount;

		mRef->mPtr = Ptr;
	}

	TSharedPtr(const TSharedPtr<T>& Ptr)
	{
		mRef = Ptr.mRef;

		if (mRef)
			++mRef->mRefCount;
	}

	TSharedPtr(const TSharedPtr<T>&& Ptr)
	{
		mRef = Ptr.mRef;

		Ptr.mRef = nullptr;
	}

	~TSharedPtr()
	{
		if (mRef)
		{
			--mRef->mRefCount;

			if (mRef->mRefCount == 0)
			{
				delete mRef;
			}
		}
	}

public:
	void operator = (const TSharedPtr<T>& Ptr)
	{
		mRef = Ptr.mRef;

		if (mRef)
			++mRef->mRefCount;
	}

	void operator = (T* Ptr)
	{
		if (mRef)
		{
			delete mRef->mPtr;
			delete mRef;
		}

		mRef = new CRef;
		++mRef->mRefCount;

		mRef->mPtr = Ptr;
	}

	void operator = (T Ptr)
	{
		if (mRef)
		{
			delete mRef->mPtr;
			delete mRef;
		}

		mRef = new CRef;

		mRef->mPtr = new T;

		*mRef->mPtr = Ptr;
		++mRef->mRefCount;
	}

	T* operator -> ()
	{
		return mRef->mPtr;
	}

	const T* operator -> ()	const
	{
		return mRef->mPtr;
	}

	T& operator * ()
	{
		return *(mRef->mPtr);
	}

	const T& operator * ()	const
	{
		return *(mRef->mPtr);
	}

	operator const T& ()	const
	{
		return *(mRef->mPtr);
	}

private:
	CRef* mRef = nullptr;

public:
	static const TSharedPtr<T>& make_shared(const T& Data)
	{
		return TSharedPtr<T>(Data);
	}
};

class CTest
{
public:
	CTest()
	{
	}

	~CTest()
	{
	}

public:
	int	mNum = 100;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1309);

	/*int* Number = new int;
	*Number = 500;
	std::shared_ptr<int>	SPtr(Number);
	std::shared_ptr<int>	SPtr2 = SPtr;

	std::shared_ptr<int>	SPtr1 = std::make_shared<int>(123);*/
	//TSharedPtr<int>::CRef	ref;

	int* Number1 = new int;

	TSharedPtr<int>	IntPtr;
	TSharedPtr<int>	IntPtr1 = IntPtr;
	TSharedPtr<int>	IntPtr2(Number1);

	*IntPtr = 500;

	int	Number = IntPtr;

	*IntPtr2 = 300;

	printf("%d\n", *IntPtr);
	printf("%d\n", *IntPtr1);
	printf("%d\n", *IntPtr2);

	TSharedPtr<CMonster>	Monster1 = new CGoblin;

	CTest* Test3 = new CTest;
	TSharedPtr<CTest>	Test1(Test3);
	TSharedPtr<CTest>	Test2 = Test1;

	Test1->mNum = 500;
	Test2->mNum = 800;

	printf("%d\n", Test3->mNum);

	return 0;
}