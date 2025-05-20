#include <iostream>

class CSingleton
{
private:
	CSingleton()
	{

	}
	~CSingleton()
	{

	}

private:
	static CSingleton* mInst;
	//static CSingleton mInst1;

public:
	static CSingleton* GetInst()
	{
		if (mInst == nullptr)
			mInst = new CSingleton;

		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};

CSingleton* CSingleton::mInst = nullptr;

int main()
{
	// ���������� �˾Ƴ����� ���� -> ������Ŭ������ ���� �� ���� �̱�������(static �̿�)���� ������
// CSingleton single;

	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());

	CSingleton::DestroyInst();

	return 0;
}