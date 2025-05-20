
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
		// ::operator new �� �ϸ� ���������� new�� ȣ���Ѵ�.
		// ������ ȣ�� ���� �����ϰ� �޸𸮸� �Ҵ��ϴ� ����̴�.
		mMemory = (T*)(::operator new(PoolSize * sizeof(T)));

		// C��� ��Ÿ���� �޸� �������.
		//mMemory = (T*)malloc(PoolSize * sizeof(T));

		// ���ÿ� �ε��� ���� �ּҸ� ��Ƶд�.
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
		// ���̻� �Ҵ��� �� �ִ� ������ ���� ��� ����ó���� ���ش�.
		assert(!mAllocMemory.empty() && "Memory Pool Is Empty");

		// top�� �̿��ؼ� �������� �߰��� �����͸� ���´�.
		T* Ptr = mAllocMemory.top();

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

	void DeAlloc(T* Ptr)
	{
		// �޸𸮸� Ǯ�� ��ȯ�� �� �Ҹ��ڸ� ȣ���ϰ� ���� ���
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
		printf("CGoblin ������\n");
	}

	virtual ~CGoblin()
	{
		printf("CGoblin �Ҹ���\n");
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
		printf("COrc ������\n");
	}

	virtual ~COrc()
	{
		printf("COrc �Ҹ���\n");
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
