
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
	포인터 :
	메모리 주소를 저장하기 위한 변수 타입 (OS는 메모리 주소 할당 및 제어)
	주소를 통해 메모리에 접근할 수 있는 기능 -> 잘못 쓸 경우엔 무조건 프로그램 죽음
	모든 변수 타입은 포인터 타입 변수를 선언할 수 있음

	포인터 이론들은 모두 다 암기

	메모리 주소를 갖고 있는 변수,
	일반 변수를 찾아가기 위해 주소를 가지고 있는 타입

	변수타입* 포인터변수이름;

	위의 형태로 포인터 변수를 선언함

	포인터 타입의 메모리 크기는 x64일 때 8바이트, x86일 때 4바이트

	역참조 :
	포인터 변수가 가지고 있는 메모리 주소에 접근하여
	해당 주소에 있는 값을 변경하거나 사용할 수 있게 해줌
	*포인터변수명 = 100;
	
	위와 같이 포인터변수명 앞에 *을 붙여 역참조를 함

	변수 타입에 영향을 받아 해당 타입 변수의 메모리 주소를 저장할 수 있게 됨
	단, void는 타입이 없다는 의미인데, 일반 void 타입 변수는 선언이 불가능하지만
	void* 타입 변수는 선언이 가능하여 모든 변수 타입의 메모리 주소를 저장할 수 있음
	단, void*는 역참조가 불가능함
	*/

	// 변수를 선언했다는 건 메모리 어딘가에 저장이 되어있다는 것
	float Number1 = 3.14f;
	int Number = 100;

	// 포인터 초기화를 안하면 쓰레기값이 들어있음 > 어쨌든 값이 있는 거니까 컴퓨터는 그 값을 참조함 => 에러 발생, 프로그램 죽음
	// 초기화 할 때 nullptr이나 0 쓰면 됨
	// 0 > 참조하는게없다 / 0이 아닌 다른 값 > 참조하는게있다
	int* Address = nullptr;

	// nullptr일 때 참조하면 에러
	//*Address = 200;
	
	Address = &Number;
	// float 타입 변수의 주소를 int* 타입에 대입해주기 때문에 에러가 발생
	// Address = &Number1;
	// 아래와 같이 형변환을 하면 가능함
	// Address = (int*)&Number1;

	// Address는 Number 변수의 메모리 주소를 가지고 있기 때문에
	// 그 주소에 접근하여 값을 1234로 변경함
	// 즉, Number 변수의 값이 1234로 변경된 것
	*Address = 1234;

	// 함수에서 변수의 값을 바꿀 수 있기 때문에 포인터 사용 자주 함
	ChangeNumber(Number);
	ChangeNumber(&Number);


	bool Test1 = true;
	bool* Address1 = &Test1;
	
	void* VoidAddress = &Number;
	VoidAddress = &Number1;
	VoidAddress = &Test1;

	//*VoidAddress = true;
	// 아래는 void*를 임시로 bool*로 변환시켜 인식시켜주기 때문에 역참조가 가능
	*((bool*)VoidAddress) = true;

	printf("Number = %d\n", Number);

	// 변수 앞에 & 를 붙여주면 해당 변수의 메모리 주소를 의미
	// 메모리 주소는 16진수로 표현이 됨
	// %x : 16진수 출력 / %8x : 16진수 8자리 출력
	// %p : 메모리 주소 출력
	printf("&Number = %p\n", &Number);
	printf("Address = %p\n", Address);
	printf("Address1 = %p\n", Address1);
	printf("*Address = %d\n", *Address);
	
	/*
	포인터와 배열의 관계
	배열 이름은 배열의 시작 메모리 주소를 의미함 = 배열 이름은 일종의 포인터
	*/
	int Array[100] = {};

	printf("%p\n", Array);

	// 배열 이름은 배열의 시작 메모리 주소이기 때문에
	// 포인터 변수에 해당 배열의 시작 메모리 주소를 저장할 수도 있음
	int* ArrayAddress = Array;

	// 배열이름[인덱스] 로 접근하는 것은 배열시작주소[인덱스]와 같음
	Array[3] = 500;

	// 포인터변수도 배열의 시작 메모리 주소를 가지고 있기 때문에
	// 인덱스를 이용하여 배열에 접근할 수 있음
	ArrayAddress[3] = 1111;

	// 보통은 포인터를 이용하여 값을 넘김(ex. 함수)
	printf("Array[3] = %d\n", Array[3]);

	/*
	포인터 연산 : +, -, ++, -- 4가지가 지원됨
	포인터 연산은 일반적인 연산과 다르게 연산됨
	1을 더하면 단순하게 메모리 주소에 1을 더하는 것이 아닌,
	포인터변수 타입의 메모리 크기만큼을 더해주게 됨
	2를 더하면 2 * 타입크기 만큼을 주소에 더해주게 됨
	*/

	printf("Array = %p\n", Array);
	printf("&Array[0] = %p\n", &Array[0]);
	printf("ArrayAddress = %p\n", ArrayAddress);
	printf("ArrayAddress + 1 = %p\n", ArrayAddress + 1);
	printf("ArrayAddress + 3 = %p\n", ArrayAddress + 3);
	printf("&Array[3] = %p\n", &Array[3]);

	printf("*(ArrayAddress + 3) = %d\n", *(ArrayAddress + 3));
	// 역참조(*)도 연산자임, 괄호가 없으면 연산자 처리됨, 연산자 우선순위때문에 괄호 신경써야됨
	printf("*ArrayAddress + 3 = %d\n", *ArrayAddress + 3);
	// 역참조가 먼저 된 것, ArradAddress엔 0이 들어가있음, 그래서 3이 나오는 것
	printf("Array[3] = %d\n", Array[3]);

	printf("%p\n", ArrayAddress);

	// 증감이 왼쪽에 있냐, 오른쪽에 있냐에 따라 우선순위가 다름
	*ArrayAddress++ = 500;
	//*++ArrayAddress = 500;

	printf("Array[0] = %d\n", Array[0]);
	printf("Array[1] = %d\n", Array[1]);

	printf("%p\n", ArrayAddress);

	/*
	printf("%p\n", ArrayAddress);
	printf("++ %p\n", ++ArrayAddress);
	// 주소 출력 먼저 -> 그 후에 증가
	printf("++ %p\n", ArrayAddress++);
	printf("%p\n", ArrayAddress);
	*/

	double Test2 = 0.13;
	double* Test2Addr = &Test2;
	printf("Test2Addr = %p\n", Test2Addr);
	printf("Test2Addr + 1 = %p\n", Test2Addr + 1);

	/*
	포인터 변수도 const 키워드를 이용하여 상수로 만들 수 있음
	const int* Addr; 참조하는 메모리 주소는 변경이 가능하지만 역참조를 하여 값을 바꾸는 것은 불가능함 -> 참조하는 대상의 값 변경 불가, 참조 대상 변경은 가능
	int* const Addr; 처음 선언과 동시에 메모리 주소의 대입만 가능하고, 그 이후에는 다른 메모리 주소를 저장할 수 없음 -> 값 변경 가능, 대상 변경 불가
	const int* const Addr; -> 참조하는 대상도 변경할 수 없고, 참조하는 대상의 값도 변경할 수 없음
	함수 인자로 넘길 때 const 포인터 변수 자주 사용 -> 팀작업할때자주이용
	const reference와 같이 const point는 자주 사용됨 -> 숙지 필수
	*/
	const int* cAddr = &Number;

	int Number22 = 300;

	cAddr = &Number22;

	Number = *cAddr;

	// L밸류 : 왼쪽 밸류, 값이 대입되는), R밸류 : 오른쪽 값, 값이 실행되는
	// *cAddr = 2222;

	int* const Addrc = &Number;

	//Addrc = &Number22;

	FPlayerInfo Player;
	FPlayerInfo* PlayerAddr = &Player;

	// 일반 변수기 때문에 . 사용 가능
	Player.Attack = 500;
	// 메모리 변수기 때문에 . 사용 불가 (연산자라..?)
	//*PlayerAddr.Attack = 600;
	(*PlayerAddr).Attack = 600;

	// 위와 같이 동작함., 화살표 연산자(->) -> 포인터 변수가 가지고 있는 주소게 접근하여
	// 멤버변수를 사용할 수 있게 해줌
	PlayerAddr->Attack = 600;

}