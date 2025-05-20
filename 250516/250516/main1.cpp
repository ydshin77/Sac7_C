
#include <iostream>
#include <stack>
#include <assert.h>

/*
�ڷᱸ�� ���� : ���Լ����� �ڷᱸ���̴�.
���߿� �߰��� �����Ͱ� ���� ������ ����̴�.

�ڷᱸ�� ť : ���Լ����� �ڷᱸ���̴�.
���� �߰��� �����Ͱ� ���� ������ ����̴�.
*/

// ��Ÿ�� ���ø� ���� : ����Ÿ���� �ƴ� ������ Ÿ������ ���ø� ���ڸ�
// ������ִ� ����̴�. ����� �νĵȴ�.
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

class CMonster
{
public:
	CMonster()
	{
		printf("CMonster ������\n");
	}

	~CMonster()
	{
		printf("CMonster �Ҹ���\n");
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
	// placement new �� �̿��Ͽ� �����ڰ� ȣ��� �� �ֵ��� �Ѵ�.
	//new (Monster1) CMonster;

	//MonsterPool.DeAlloc(Monster1);
	CMonster* Monster2 = new CMonster;


	delete Monster2;

	return 0;
}
