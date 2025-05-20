
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

		// ::operator new �� �ϸ� ���������� new�� ȣ���Ѵ�.
		// ������ ȣ�� ���� �����ϰ� �޸𸮸� �Ҵ��ϴ� ����̴�.
		//mMemory = (T*)(::operator new(PoolSize * sizeof(T)));

		//// C��� ��Ÿ���� �޸� �������.
		////mMemory = (T*)malloc(PoolSize * sizeof(T));

		//// ���ÿ� �ε��� ���� �ּҸ� ��Ƶд�.
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

		// ���̻� �Ҵ��� �� �ִ� ������ ���� ��� ����ó���� ���ش�.
		assert(!mAllocMemory.empty() && "Memory Pool Is Empty");

		// top�� �̿��ؼ� �������� �߰��� �����͸� ���´�.
		T* Ptr = (T*)mAllocMemory.top();

		// �������� �߰��� �����͸� �����Ѵ�.
		mAllocMemory.pop();

		// placement new
		// 1. �޸� �Ҵ�
		// 2. ��ü ������ ȣ��
		// �̹� �Ҵ�� �ּҿ� ��ü�� ������ �� ����Ѵ�.
		// ���� �޸𸮸� �Ҵ��ϴ� ����� �ƴϴ�.
		//::new (Ptr) T;

		return Ptr;
	}

	void DeAlloc(void* Ptr)
	{
		// �޸𸮸� Ǯ�� ��ȯ�� �� �Ҹ��ڸ� ȣ���ϰ� ���� ���
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
		printf("CMonster ������\n");
	}

	virtual ~CMonster()
	{
		printf("CMonster �Ҹ���\n");
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
		printf("CGoblin ������\n");
	}

	virtual ~CGoblin()
	{
		printf("CGoblin �Ҹ���\n");
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
		printf("COrc ������\n");
	}

	virtual ~COrc()
	{
		printf("COrc �Ҹ���\n");
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