#include <iostream>
#include <functional>

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

	// �� ĸ�� ���
	auto func4 = [Num3, Num4]()
		{
			return Num3 + Num4;
		};

	printf("Func4 = %d\n", func4());

	// ���� ĸ�� ���
	auto func5 = [&Num3, &Num4]()
		{
			++Num3;
			++Num4;
			return Num3 + Num4;
		};

	// ��� : 10, 20
	printf("Num3 = %d, Num4 = %d\n", Num3, Num4);

	// ��� : 32
	printf("Func5 = %d\n", func5());

	// ��� : 11, 21
	printf("Num3 = %d, Num4 = %d\n", Num3, Num4);

	std::function<void()> func6 = []()
		{
			printf("Test Func6\n");
		};

	func6();

	return 0;
}