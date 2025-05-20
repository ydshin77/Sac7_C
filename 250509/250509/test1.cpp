#include <iostream>

class CSingleton
{
private:
	// �����ڿ� �Ҹ��ڸ� private���� ����
	// �ܺο��� new, delete, ��ü ������ ���ϰ� �ϱ� ���ؼ�
	CSingleton() {}
	~CSingleton() {}

private:
	// Ŭ������ �� �ϳ��� �����ϴ� �ν��Ͻ��� ����ų ������
	// ���� ����̱� ������ Ŭ���� ��ü���� ������ -> �ܺ� ���� �ʼ�
	static CSingleton* mInst;

public:
	// ���� ������(mInst)�� nullptr�̸� new�� �ϳ��� ����
	// �̹� �����ϸ� �װ� ��ȯ��
	static CSingleton* GetInst()
	{
		if (mInst == nullptr)
			// ���� CSingleton ��ü�� �����ϰ� �� �ּҸ� mInst�� ��ȯ
			mInst = new CSingleton;

		return mInst;
	}

	// ���� �Ҵ��� �ν��Ͻ�(mInst) ����
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
	// GetInst()�� ���� �� ȣ���ص� ���� ��°� ��ȯ
	// -> ��ü�� �� �� ���� �����ƴٴ� ��
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());

	// ���α׷� ���� �� ���� �Ҵ��� �޸� ���� (�޸� �� ����)
	CSingleton::DestroyInst();

	// ��� : 1
	printf("%d", sizeof(CSingleton));

	return 0;
}