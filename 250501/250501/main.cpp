
#include <iostream>

void ArrTest(int (*Arr)[10])
{
}

void main()
{
	/*
	���������� : ����������Ÿ�� ������ �޸� �ּҸ� �����ϴ� ���
	������ -> �Ϲ� ������ �޸� �ּ�
	2�� -> �Ϲ������� ������ �޸� �ּ�
	3�� -> 2�� ������ ������ �޸� �ּ�
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

	// �������迭�� �� ���� ���ѵ� ���ڷ� �Ѱ��� ���� ������ -> ���� �迭�� ���� �̰ͺ��� ��
	int Array1[5][10] = {};
	int** ArrayAddr1 = nullptr;
	
	//ArrayAddr1 = Array1;
	//int* ArrayAddr1[10] = {};
	//ArrayAddr1 = Array1;
	
	int* ArrayAddr2 = &Array1[0][0];

	ArrTest(Array1);

}