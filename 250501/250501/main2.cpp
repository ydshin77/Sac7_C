
#include <iostream>

/*
�Լ������� : �Լ��� �ڵ念���� ����
�Լ��ּҴ� �ڵ� ������ ����� �޸� �ּҸ� �ǹ�
�Լ������ʹ� �̷� �Լ� �ּҸ� ������ �� �ִ� ���� Ÿ��
�Լ�Ÿ���� ��ȯŸ��, ���ڿ� ������ ����
��ȯŸ���̳� ���ڰ� �ٸ��� �ٸ� Ÿ������ �ν���
*/
int Sum(int Num1, int Num2)
{
	return Num1 + Num2;
}

int Minus(int Num1, int Num2)
{
	return Num1 - Num2;
}

void TestOutput()
{
	printf("TestOutput Function\n");
}
void TestOutput1()
{
	printf("TestOutput1 Function\n");
}

void OutputNumber(int Num1)
{
	printf("Num1 = %d\n", Num1);
}

int main()
{
	/*
	�Լ������� ������
	��ȯŸ�� (*�����ͺ�����)(����Ÿ�Ե�); �� ���·� ������

	�Լ� �̸��� �Լ� �ּ���
	*/
	int (*Func1)(int, int) = nullptr;
	void (*Func2)() = nullptr;
	void (*Func3)(int) = nullptr;
	// �Լ� �����͵� �迭 ������ ����
	int (*Func1Array[10])(int, int) = {};

	Func1 = Sum;
	Func1 = Minus;

	Func1Array[0] = Sum;
	Func1Array[1] = Minus;

	for (int i = 0; i < 2; ++i)
	{
		// ���α׷��� ���� ��ư�� > Ŀ���� �ø��� Ŭ���ϴ� ������ ����
		// ���� �ٸ� ��ɵ��� �Լ� �����͸� ��� -> �ݹ�
		printf("Func1 Result = %d\n",Func1Array[i](10, 20));
	}

	// �Լ��� ȣ���� �Լ��ּ�(���� ����)�� ���·� ȣ��ȴٴ� ��
	// printf("Func1 Result = %d\n", Func1(10, 20));

	printf("Size = %d\n", sizeof(Func1));
	// �Լ������� ���� �̸��� ���� Ÿ���� �ȴ�.
	printf("Size = %d\n", sizeof(int(*)(int, int)));

	printf("Addr = %p\n", Sum);
	printf("Addr = %p\n", Minus);
	printf("Addr = %p\n", TestOutput);
	printf("Addr = %p\n", TestOutput1);
	printf("Addr = %p\n", OutputNumber);

	return 0;
}