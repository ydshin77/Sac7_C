
#include <iostream>

void ChangeNumber(int Number)
{
	Number = 500;
}

void ChangeNumber(int* NumberAddr)
{
	*NumberAddr = 500;
}

struct FPlayerInfo
{
	char Name[32] = {};
	int	Attack = 0;
	}

void main()
{
	/*
	������ :
	�޸� �ּҸ� �����ϱ� ���� ���� Ÿ�� (OS�� �޸� �ּ� �Ҵ� �� ����)
	�ּҸ� ���� �޸𸮿� ������ �� �ִ� ��� -> �߸� �� ��쿣 ������ ���α׷� ����
	��� ���� Ÿ���� ������ Ÿ�� ������ ������ �� ����

	������ �̷е��� ��� �� �ϱ�

	�޸� �ּҸ� ���� �ִ� ����,
	�Ϲ� ������ ã�ư��� ���� �ּҸ� ������ �ִ� Ÿ��

	����Ÿ��* �����ͺ����̸�;

	���� ���·� ������ ������ ������

	������ Ÿ���� �޸� ũ��� x64�� �� 8����Ʈ, x86�� �� 4����Ʈ

	������ :
	������ ������ ������ �ִ� �޸� �ּҿ� �����Ͽ�
	�ش� �ּҿ� �ִ� ���� �����ϰų� ����� �� �ְ� ����
	*�����ͺ����� = 100;
	
	���� ���� �����ͺ����� �տ� *�� �ٿ� �������� ��

	���� Ÿ�Կ� ������ �޾� �ش� Ÿ�� ������ �޸� �ּҸ� ������ �� �ְ� ��
	��, void�� Ÿ���� ���ٴ� �ǹ��ε�, �Ϲ� void Ÿ�� ������ ������ �Ұ���������
	void* Ÿ�� ������ ������ �����Ͽ� ��� ���� Ÿ���� �޸� �ּҸ� ������ �� ����
	��, void*�� �������� �Ұ�����
	*/

	// ������ �����ߴٴ� �� �޸� ��򰡿� ������ �Ǿ��ִٴ� ��
	float Number1 = 3.14f;
	int Number = 100;

	// ������ �ʱ�ȭ�� ���ϸ� �����Ⱚ�� ������� > ��·�� ���� �ִ� �Ŵϱ� ��ǻ�ʹ� �� ���� ������ => ���� �߻�, ���α׷� ����
	// �ʱ�ȭ �� �� nullptr�̳� 0 ���� ��
	// 0 > �����ϴ°Ծ��� / 0�� �ƴ� �ٸ� �� > �����ϴ°��ִ�
	int* Address = nullptr;

	// nullptr�� �� �����ϸ� ����
	//*Address = 200;
	
	Address = &Number;
	// float Ÿ�� ������ �ּҸ� int* Ÿ�Կ� �������ֱ� ������ ������ �߻�
	// Address = &Number1;
	// �Ʒ��� ���� ����ȯ�� �ϸ� ������
	// Address = (int*)&Number1;

	// Address�� Number ������ �޸� �ּҸ� ������ �ֱ� ������
	// �� �ּҿ� �����Ͽ� ���� 1234�� ������
	// ��, Number ������ ���� 1234�� ����� ��
	*Address = 1234;

	// �Լ����� ������ ���� �ٲ� �� �ֱ� ������ ������ ��� ���� ��
	ChangeNumber(Number);
	ChangeNumber(&Number);


	bool Test1 = true;
	bool* Address1 = &Test1;
	
	void* VoidAddress = &Number;
	VoidAddress = &Number1;
	VoidAddress = &Test1;

	//*VoidAddress = true;
	// �Ʒ��� void*�� �ӽ÷� bool*�� ��ȯ���� �νĽ����ֱ� ������ �������� ����
	*((bool*)VoidAddress) = true;

	printf("Number = %d\n", Number);

	// ���� �տ� & �� �ٿ��ָ� �ش� ������ �޸� �ּҸ� �ǹ�
	// �޸� �ּҴ� 16������ ǥ���� ��
	// %x : 16���� ��� / %8x : 16���� 8�ڸ� ���
	// %p : �޸� �ּ� ���
	printf("&Number = %p\n", &Number);
	printf("Address = %p\n", Address);
	printf("Address1 = %p\n", Address1);
	printf("*Address = %d\n", *Address);
	
	/*
	�����Ϳ� �迭�� ����
	�迭 �̸��� �迭�� ���� �޸� �ּҸ� �ǹ��� = �迭 �̸��� ������ ������
	*/
	int Array[100] = {};

	printf("%p\n", Array);

	// �迭 �̸��� �迭�� ���� �޸� �ּ��̱� ������
	// ������ ������ �ش� �迭�� ���� �޸� �ּҸ� ������ ���� ����
	int* ArrayAddress = Array;

	// �迭�̸�[�ε���] �� �����ϴ� ���� �迭�����ּ�[�ε���]�� ����
	Array[3] = 500;

	// �����ͺ����� �迭�� ���� �޸� �ּҸ� ������ �ֱ� ������
	// �ε����� �̿��Ͽ� �迭�� ������ �� ����
	ArrayAddress[3] = 1111;

	// ������ �����͸� �̿��Ͽ� ���� �ѱ�(ex. �Լ�)
	printf("Array[3] = %d\n", Array[3]);

	/*
	������ ���� : +, -, ++, -- 4������ ������
	������ ������ �Ϲ����� ����� �ٸ��� �����
	1�� ���ϸ� �ܼ��ϰ� �޸� �ּҿ� 1�� ���ϴ� ���� �ƴ�,
	�����ͺ��� Ÿ���� �޸� ũ�⸸ŭ�� �����ְ� ��
	2�� ���ϸ� 2 * Ÿ��ũ�� ��ŭ�� �ּҿ� �����ְ� ��
	*/

	printf("Array = %p\n", Array);
	printf("&Array[0] = %p\n", &Array[0]);
	printf("ArrayAddress = %p\n", ArrayAddress);
	printf("ArrayAddress + 1 = %p\n", ArrayAddress + 1);
	printf("ArrayAddress + 3 = %p\n", ArrayAddress + 3);
	printf("&Array[3] = %p\n", &Array[3]);

	printf("*(ArrayAddress + 3) = %d\n", *(ArrayAddress + 3));
	// ������(*)�� ��������, ��ȣ�� ������ ������ ó����, ������ �켱���������� ��ȣ �Ű��ߵ�
	printf("*ArrayAddress + 3 = %d\n", *ArrayAddress + 3);
	// �������� ���� �� ��, ArradAddress�� 0�� ������, �׷��� 3�� ������ ��
	printf("Array[3] = %d\n", Array[3]);

	printf("%p\n", ArrayAddress);

	// ������ ���ʿ� �ֳ�, �����ʿ� �ֳĿ� ���� �켱������ �ٸ�
	*ArrayAddress++ = 500;
	//*++ArrayAddress = 500;

	printf("Array[0] = %d\n", Array[0]);
	printf("Array[1] = %d\n", Array[1]);

	printf("%p\n", ArrayAddress);

	/*
	printf("%p\n", ArrayAddress);
	printf("++ %p\n", ++ArrayAddress);
	// �ּ� ��� ���� -> �� �Ŀ� ����
	printf("++ %p\n", ArrayAddress++);
	printf("%p\n", ArrayAddress);
	*/

	double Test2 = 0.13;
	double* Test2Addr = &Test2;
	printf("Test2Addr = %p\n", Test2Addr);
	printf("Test2Addr + 1 = %p\n", Test2Addr + 1);

	/*
	������ ������ const Ű���带 �̿��Ͽ� ����� ���� �� ����
	const int* Addr; �����ϴ� �޸� �ּҴ� ������ ���������� �������� �Ͽ� ���� �ٲٴ� ���� �Ұ����� -> �����ϴ� ����� �� ���� �Ұ�, ���� ��� ������ ����
	int* const Addr; ó�� ����� ���ÿ� �޸� �ּ��� ���Ը� �����ϰ�, �� ���Ŀ��� �ٸ� �޸� �ּҸ� ������ �� ���� -> �� ���� ����, ��� ���� �Ұ�
	const int* const Addr; -> �����ϴ� ��� ������ �� ����, �����ϴ� ����� ���� ������ �� ����
	�Լ� ���ڷ� �ѱ� �� const ������ ���� ���� ��� -> ���۾��Ҷ������̿�
	const reference�� ���� const point�� ���� ���� -> ���� �ʼ�
	*/
	const int* cAddr = &Number;

	int Number22 = 300;

	cAddr = &Number22;

	Number = *cAddr;

	// L��� : ���� ���, ���� ���ԵǴ�), R��� : ������ ��, ���� ����Ǵ�
	// *cAddr = 2222;

	int* const Addrc = &Number;

	//Addrc = &Number22;

	FPlayerInfo Player;
	FPlayerInfo* PlayerAddr = &Player;

	// �Ϲ� ������ ������ . ��� ����
	Player.Attack = 500;
	// �޸� ������ ������ . ��� �Ұ� (�����ڶ�..?)
	//*PlayerAddr.Attack = 600;
	(*PlayerAddr).Attack = 600;

	// ���� ���� ������., ȭ��ǥ ������(->) -> ������ ������ ������ �ִ� �ּҰ� �����Ͽ�
	// ��������� ����� �� �ְ� ����
	PlayerAddr->Attack = 600;

}