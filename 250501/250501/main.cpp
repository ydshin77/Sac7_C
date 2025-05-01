
#include <iostream>

void ArrTest(int (*Arr)[10])
{
}

void main()
{
	/*
	다중포인터 : 이전포인터타입 변수의 메모리 주소를 저장하는 기능
	포인터 -> 일반 변수의 메모리 주소
	2중 -> 일반포인터 변수의 메모리 주소
	3중 -> 2중 포인터 변수의 메모리 주소
	*/
	int		Number = 100;
	int*	Addr = &Number;
	int**	Addr2 = &Addr;

	printf("Number = %d\n", Number);
	printf("Number Address = %p\n", &Number);
	printf("Addr = %p\n", Addr);
	printf("*Addr = %d\n", *Addr);
	printf("Addr Address = %p\n", &Addr);
	printf("Addr2 = %p\n", Addr2);
	printf("*Addr2 = %p\n", *Addr2);
	printf("**Addr2 = %d\n", **Addr2);
	printf("Addr2 Address = %p\n", &Addr2);

	int Array[100] = {};
	int* ArrayAddr = Array;
	int* ArrayAddrArr[20] = {};

	// 이차원배열이 쓸 때는 편리한데 인자로 넘겨줄 때는 불편함 -> 동적 배열을 쓰면 이것보단 편리
	int Array1[5][10] = {};
	int** ArrayAddr1 = nullptr;
	
	//ArrayAddr1 = Array1;
	//int* ArrayAddr1[10] = {};
	//ArrayAddr1 = Array1;
	
	int* ArrayAddr2 = &Array1[0][0];

	ArrTest(Array1);

}