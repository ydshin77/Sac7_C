
#include <iostream>
// 모든 함수 포인터를 저장할 수 있는 기능 지원
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

// 기존엔 변수가 여러 개면 함수 오버로딩으로 작업 -> 보통은 템플릿을 사용해 작업
void OutputNumber(int Number)
{
	printf("Number = %d\n", Number);
}

void OutputNumber(float Number)
{
	printf("Number = %f\n", Number);
}

/*
템플릿 : 가변적인 타입을 대응할 때 사용됨
컴파일 시간에 타입이 결정되며 결정된 타입으로 코드를 만들어줌
template <typename 원하는이름>
template <class 원하는이름> 의 형태로 만듦
template <typename T, typename T1> 이런 형태가 됨
T와 T1은 타입이 됨
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

	// this를 사용하지 않는 전역변수와 똑같이 동작 -> 일반함수 포인터에도 담을 수 있음
	test.OutputTest();
	test.OutputTestStatic();

	void (*Func) ();

	Func = Output;

	Func();

	Func = CTest::OutputTestStatic;

	Func();

	//Func = CTest::OutputTest;
	// 일반 멤버함수 포인터는 &클래스명::함수명 으로 해야 함
	// 일반함수 포인터와의 차이점 : 문법적인 사용법
	void(CTest:: * Func1)() = &CTest::OutputTest;

	// 멤버함수는 무조건 this 지정이 되어야함
	// 멤버함수 포인터 호출 방법
	// (객체.*멤버함수포인터) (인장); 의 형태로 호출
	(test.*Func1)();

	(test1.*Func1)();

	// fuctional 사용법
	//std::function 

	// T가 int가 됨 (클래스, 열거형, 구조체 등 원하는 타입 넣을 수 있음)
	OutputTemplate<int>(10);
	// T가 float이 됨
	OutputTemplate<float>(3.14f);
	// 함수 호출도 가능
	OutputTemplateFunc<void(*)()> (Output);
//	OutputTemplateFunc<CTest, void(CTest::*)()>(&test, &CTest::OutputTest);

	OutputObject<CTest, void(CTest::*)()>(&test,
		&CTest::OutputTest);

	std::function<void(int, float)>	func3;
	// 1번인자 : 함수 주소
	// 2번인자 부터는 주소를 넣어주는 함수의 인자를 어떤 순서로
	// 호출해줄지를 결정한다.
	func3 = std::bind(OutputFunctional, std::placeholders::_1,
		std::placeholders::_2);

	func3(10, 3.14f);

	func3 = std::bind(OutputFunctional, std::placeholders::_2,
		std::placeholders::_1);

	func3(10, 3.14f);

	std::function<void()> func2;
	// 1번인자 : 함수주소
	// 2번인자 : 객체
	// 3번인자부터는 같음
	func2 = std::bind(&CTest::OutputTest, test);
	func2();

	func2 = std::bind(&CTest::OutputTest1, test);
	func2();

	// 람다 : 익명함수 (함수를 빠르게 만들어주는 기능)
	// auto : 대입 받는 값의 타입으로 자동으로 타입이 결정됨
	auto Num = 10; // int가 됨
	auto Num1 = 3.14f; // float가 됨

	auto	func4 = []()
		{
			printf("Func4 람다\n");
		};

	func4();

	auto	func5 = [](int Num)
		{
			printf("Func5 람다 : %d\n", Num);
		};

	func5(500);

	auto	func6 = [](int Num1, int Num2) -> int
		{
			return Num1 + Num2;
		};

	printf("%d\n", func6(30, 40));

	int	Num3 = 10, Num4 = 20;

	// 외부 변수 캡처 방식.
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