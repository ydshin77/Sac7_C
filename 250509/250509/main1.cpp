#include <iostream>

class CStatic
{
public:
	CStatic()
	{

	}
	~CStatic()
	{

	}

private:
	// �Ϲ� ��������� �����ϴ� ��ü���� �޸𸮸� �Ҵ���
	int			mNumber = 0;

public:
	// �� Ŭ������ �̿��ؼ� ������ ��� ��ü�� �����ϴ� �޸���
	// static ��������� Ŭ���� �ܺο� ����κ��� �ʿ���
	static int	mNumberStatic;

public:
	void SetNumber(int Number)
	{
		mNumber = Number;
	}

	// ����Լ� �ڿ� const�� �ٿ��ְ� �Ǹ� �� �Լ������� Ŭ���� ��������� ���� ������ �� ����
	// const ��ü�� ȣ���� �� �ִ� �Լ��� ��
	// const ��ü�� �Ϲ� �Լ��� ȣ���� �� ����
	int GetNumber() const
	{
		return mNumber;
	}

public:
	static void OutputStatic()
	{
		// static ����Լ����� this�� ����. this�� �Ϲ��Լ��� ����� ���� �����
		// printf("Number = %d\n", mNumber);
		// static ����� �ٷ� ���� ����
		printf("NumberStatic = %d\n", mNumberStatic);
	}

	static void OutputObject(CStatic* Obj)
	{
		printf("Number = %d\n", Obj->mNumber);
	}
};

// Ŭ���� ������� ����
// ����Ÿ�� Ŭ������::������; ���� ������
int CStatic::mNumberStatic;

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
	CStatic Static1, Static3;
	const CStatic Static2;

	Static1.SetNumber(100);
	Static1.GetNumber();

	Static2.GetNumber();
	//Static2.SetNumber(200);

	Static1.mNumberStatic = 200;
	Static3.mNumberStatic = 300;
	CStatic::mNumberStatic = 500;

	// �����ϴ� �޸𸮱� ������ ������ ���� ��µ� -> static ��������� Ư¡
	printf("NumberStatic = %d\n", Static1.mNumberStatic);
	printf("NumberStatic = %d\n", Static3.mNumberStatic);
	
	Static1.OutputStatic();
	Static3.OutputStatic();
	CStatic::OutputStatic();
	
	CStatic::OutputObject(&Static1);
	CStatic::OutputObject(&Static3);

	// ���������� �˾Ƴ����� ���� -> ������Ŭ������ ���� �� ���� �̱�������(static �̿�)���� ������
	// CSingleton single;

	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());

	CSingleton::DestroyInst();

	return 0;
}