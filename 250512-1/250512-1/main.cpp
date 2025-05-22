#include <iostream>

int main()
{
	auto Num = 10;
	auto Num1 = 3.14f;

	auto func1 = []()
		{
			printf("Func1 람다\n");
		};

	func1();

	auto func2 = [](int Num)
		{
			printf("Func2 람다 : %d\n", Num);
		};

	func2(20);

	// 반환 타입을 지정할 땐 화살표(->) 사용
	auto func3 = [](int Num1, int Num2) -> int
		{
			return Num1 + Num2;
		};

	printf("Func3 = %d\n", func3(30, 40));

	auto Num3 = 10, Num4 = 20;

	// 외부 변수 캡쳐 방식 -> 인자를 안넣어도 Num3, Num4로 처리 44 49
	auto func4 = [Num3, Num4]()
		{
			return Num3 + Num4;
		};

	printf("Func4 = %d\n", func4());

	return 0;
}