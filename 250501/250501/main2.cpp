
#include <iostream>

/*
함수포인터 : 함수는 코드영역에 저장
함수주소는 코드 영역에 저장된 메모리 주소를 의미
함수포인터는 이런 함수 주소를 저장할 수 있는 변수 타입
함수타입은 반환타입, 인자에 영향을 받음
반환타입이나 인자가 다르면 다른 타입으로 인식함
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
	함수포인터 선언방법
	반환타입 (*포인터변수명)(인자타입들); 의 형태로 선언함

	함수 이름은 함수 주소임
	*/
	int (*Func1)(int, int) = nullptr;
	void (*Func2)() = nullptr;
	void (*Func3)(int) = nullptr;
	// 함수 포인터도 배열 선언이 가능
	int (*Func1Array[10])(int, int) = {};

	Func1 = Sum;
	Func1 = Minus;

	Func1Array[0] = Sum;
	Func1Array[1] = Minus;

	for (int i = 0; i < 2; ++i)
	{
		// 프로그램에 여러 버튼들 > 커서를 올리고 클릭하는 동작은 동일
		// 각자 다른 기능들은 함수 포인터를 사용 -> 콜백
		printf("Func1 Result = %d\n",Func1Array[i](10, 20));
	}

	// 함수의 호출은 함수주소(인자 전달)의 형태로 호출된다는 것
	// printf("Func1 Result = %d\n", Func1(10, 20));

	printf("Size = %d\n", sizeof(Func1));
	// 함수포인터 변수 이름만 빼면 타입이 된다.
	printf("Size = %d\n", sizeof(int(*)(int, int)));

	printf("Addr = %p\n", Sum);
	printf("Addr = %p\n", Minus);
	printf("Addr = %p\n", TestOutput);
	printf("Addr = %p\n", TestOutput1);
	printf("Addr = %p\n", OutputNumber);

	return 0;
}