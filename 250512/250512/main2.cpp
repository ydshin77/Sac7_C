
#include <iostream>
#include "Array.h"

struct FTest
{
	char Arr[1024];
};

int main()
{
	//// T Data ¿œ ∂ß 
	//CArray<FTest> Arr;

	//FTest test1;
	//Arr.push_back(test1);

	CArray<int> Arr1;

	/*Arr1.pop_back();

	Arr1.push_back(10);*/

	for (int i = 0; i < 10; ++i)
	{
		Arr1.push_back(i + 1);
	}

	Arr1.erase(7);

	Arr1.eraseIndex(2);

	int Size = Arr1.size();

	for (int i = 0; i < Size; ++i)
	{
		printf("Arr1[%d] = %d\n", i, Arr1[i]);
	}

	return 0;
}