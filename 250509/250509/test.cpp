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
	// 디자인패턴 알아놓으면 좋음 -> 관리자클래스를 만들 땐 보통 싱글톤패턴(static 이용)으로 제작함
// CSingleton single;

	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());

	CSingleton::DestroyInst();

	return 0;
}