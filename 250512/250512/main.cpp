
#include <iostream>
// ��� �Լ� �����͸� ������ �� �ִ� ��� ����
#include <functional>

class CTest
{
public:
	CTest()
	{

	}

	~CTest()
	{

	}

public:
	void OutputTest()
	{
		printf("CTest::OutputTest Function\n");
	}

	void OutputTest1()
	{
		printf("CTest::OutputTest1 Function\n");
	}

	static void OutputTestStatic()
	{
		printf("CTest::OutputTestStatic Function\n");
	}
};

void Output()
{
	printf("Output Function\n");
}

struct FTestFunc
{
	void(CTest::* Func1) ();
	CTest* Object;
};

// ������ ������ ���� ���� �Լ� �����ε����� �۾� -> ������ ���ø��� ����� �۾�
void OutputNumber(int Number)
{
	printf("Number = %d\n", Number);
}

void OutputNumber(float Number)
{
	printf("Number = %f\n", Number);
}

/*
���ø� : �������� Ÿ���� ������ �� ����
������ �ð��� Ÿ���� �����Ǹ� ������ Ÿ������ �ڵ带 �������
template <typename ���ϴ��̸�>
template <class ���ϴ��̸�> �� ���·� ����
template <typename T, typename T1> �̷� ���°� ��
T�� T1�� Ÿ���� ��
*/
template <typename T>
void OutputTemplate(T Num)
{
	std::cout << Num << std::endl;
}

template <typename T>
void OutputTemplateFunc(T Func)
{
	Func();
}

template <typename T, typename F>
void OutputObject(T* Obj, F Func)
{
	(Obj->*Func)();
}

void OutputFunctional(int Number, float Number2)
{
	std::cout << Number << ", " << Number2 << std::endl;
	//printf("Number = %d, Number2 = %.f\n", Number, Number2);
}

int main()
{
	Output();
	CTest::OutputTestStatic();

	CTest test, test1, test2;

	// this�� ������� �ʴ� ���������� �Ȱ��� ���� -> �Ϲ��Լ� �����Ϳ��� ���� �� ����
	test.OutputTest();
	test.OutputTestStatic();

	void (*Func) ();

	Func = Output;

	Func();

	Func = CTest::OutputTestStatic;

	Func();

	//Func = CTest::OutputTest;
	// �Ϲ� ����Լ� �����ʹ� &Ŭ������::�Լ��� ���� �ؾ� ��
	// �Ϲ��Լ� �����Ϳ��� ������ : �������� ����
	void(CTest:: * Func1)() = &CTest::OutputTest;

	// ����Լ��� ������ this ������ �Ǿ����
	// ����Լ� ������ ȣ�� ���
	// (��ü.*����Լ�������) (����); �� ���·� ȣ��
	(test.*Func1)();

	(test1.*Func1)();

	// fuctional ����
	//std::function 

	// T�� int�� �� (Ŭ����, ������, ����ü �� ���ϴ� Ÿ�� ���� �� ����)
	OutputTemplate<int>(10);
	// T�� float�� ��
	OutputTemplate<float>(3.14f);
	// �Լ� ȣ�⵵ ����
	OutputTemplateFunc<void(*)()> (Output);
//	OutputTemplateFunc<CTest, void(CTest::*)()>(&test, &CTest::OutputTest);

	OutputObject<CTest, void(CTest::*)()>(&test,
		&CTest::OutputTest);

	std::function<void(int, float)>	func3;
	// 1������ : �Լ� �ּ�
	// 2������ ���ʹ� �ּҸ� �־��ִ� �Լ��� ���ڸ� � ������
	// ȣ���������� �����Ѵ�.
	func3 = std::bind(OutputFunctional, std::placeholders::_1,
		std::placeholders::_2);

	func3(10, 3.14f);

	func3 = std::bind(OutputFunctional, std::placeholders::_2,
		std::placeholders::_1);

	func3(10, 3.14f);

	std::function<void()> func2;
	// 1������ : �Լ��ּ�
	// 2������ : ��ü
	// 3�����ں��ʹ� ����
	func2 = std::bind(&CTest::OutputTest, test);
	func2();

	func2 = std::bind(&CTest::OutputTest1, test);
	func2();

	// ���� : �͸��Լ� (�Լ��� ������ ������ִ� ���)
	// auto : ���� �޴� ���� Ÿ������ �ڵ����� Ÿ���� ������
	auto Num = 10; // int�� ��
	auto Num1 = 3.14f; // float�� ��

	auto	func4 = []()
		{
			printf("Func4 ����\n");
		};

	func4();

	auto	func5 = [](int Num)
		{
			printf("Func5 ���� : %d\n", Num);
		};

	func5(500);

	auto	func6 = [](int Num1, int Num2) -> int
		{
			return Num1 + Num2;
		};

	printf("%d\n", func6(30, 40));

	int	Num3 = 10, Num4 = 20;

	// �ܺ� ���� ĸó ���.
	auto	func7 = [Num3, Num4]()
		{
			return Num3 + Num4;
		};

	printf("Func7 = %d\n", func7());

	auto	func8 = [&Num3, &Num4]()
		{
			++Num3;
			++Num4;
			return Num3 + Num4;
		};

	printf("Num3 = %d, Num4 = %d\n", Num3, Num4);
	printf("Func8 = %d\n", func8());

	std::function<void()>	func9 = []()
		{
			printf("Test Func9\n");
		};

	func9();

	return 0;
}