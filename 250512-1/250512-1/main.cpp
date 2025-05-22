#include <iostream>

int main()
{
	auto Num = 10;
	auto Num1 = 3.14f;

	auto func1 = []()
		{
			printf("Func1 ����\n");
		};

	func1();

	auto func2 = [](int Num)
		{
			printf("Func2 ���� : %d\n", Num);
		};

	func2(20);

	// ��ȯ Ÿ���� ������ �� ȭ��ǥ(->) ���
	auto func3 = [](int Num1, int Num2) -> int
		{
			return Num1 + Num2;
		};

	printf("Func3 = %d\n", func3(30, 40));

	auto Num3 = 10, Num4 = 20;

	// �ܺ� ���� ĸ�� ��� -> ���ڸ� �ȳ־ Num3, Num4�� ó�� 44 49
	auto func4 = [Num3, Num4]()
		{
			return Num3 + Num4;
		};

	printf("Func4 = %d\n", func4());

	return 0;
}