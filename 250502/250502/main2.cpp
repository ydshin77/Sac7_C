
#include <iostream>
#include <fstream>

int main()
{
	// 2�� ���ڿ� std::ios::binary �� �־��ָ� ���̳ʸ� ������ �ȴ�.
	std::ofstream	WriteFile("Test2.txt");

	// ������ ���� �� �ִ� �������� üũ�Ѵ�.
	if (!WriteFile.is_open())
		return 0;

	WriteFile << "�ؽ�Ʈ�߰�\n";
	WriteFile << "2��° �� �ؽ�Ʈ�߰�";


	WriteFile.close();

	std::ifstream	ReadFile("Test2.txt");

	if (!ReadFile.is_open())
		return 0;

	char	Text[256] = {};

	// ���๮�� ������ ������ �о���� ���๮�ڴ� ������.
	ReadFile.getline(Text, 256);

	printf("%s\n", Text);

	ReadFile.getline(Text, 256);

	printf("%s\n", Text);

	// ���ڸ� �о����, �����̽���, ���� ���� �������� �о�´�.
	/*ReadFile >> Text;

	printf("%s", Text);

	ReadFile >> Text;

	printf("%s", Text);*/

	ReadFile.close();

	return 0;
}