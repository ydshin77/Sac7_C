#include <iostream>
#include <fstream>

int main()
{
	// 파일 쓰기
	std::ofstream WriteFile("Test3.tbf", std::ios::binary);

	if (!WriteFile.is_open())
		return 0;

	int Number = 100;

	WriteFile.write((const char*)&Number, sizeof(int));

	int Array[10] = {};
	for (int i = 0; i < 10; ++i)
	{
		Array[i] = i + 1;
	}

	WriteFile.write((const char*)Array, sizeof(int) * 10);

	WriteFile.close();

	// 파일 열기
	std::ifstream ReadFile("Test3.tbf", std::ios::binary);

	if (!ReadFile.is_open())
		return 0;

	// 제대로 갖고 왔는지 보려고 0으로 초기화
	Number = 0;
	for (int i = 0; i < 10; ++i)
	{
		Array[i] = 0;
	}

	ReadFile.read((char*) & Number, sizeof(int));
	
	// 출력 : 100
	printf("Number = %d\n", Number);

	ReadFile.read((char*)Array, sizeof(int) * 10);

	// 출력 : 1 ~ 10
	for (int i = 0; i < 10; ++i)
	{
		printf("Array[%d] = %d\n", i, Array[i]);
	}

	ReadFile.close();

	return 0;
}