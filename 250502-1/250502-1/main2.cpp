#include <iostream>
#include <fstream>

int main()
{
	// ���� ��Ʈ�� ���� (���� ����)
	std::ofstream WriteFile("Test2.txt");

	// ������ ���� �� �ִ� �������� üũ -> ���� ��Ʈ���� �ȿ��������� ����
	if (!WriteFile.is_open())
		return 0;

	// �ؽ�Ʈ ����
	WriteFile << "�ؽ�Ʈ�߰�\n";
	WriteFile << "2��° �� �ؽ�Ʈ�߰�";

	// ���� ��Ʈ�� �ݱ�
	WriteFile.close();

	// ===============================
	
	// ���� ��Ʈ�� ����(���� �б�)
	std::ifstream ReadFile("Test2.txt");

	// ���� ��Ʈ���� �ȿ��������� ����
	if (!ReadFile.is_open())
		return 0;

	// �ؽ�Ʈ �о����
	char Text[256] = {};
	
	// ���� ���� ������ �� �� �б� (���๮�ڴ� ������)
	ReadFile.getline(Text, 256);
	// ��� : �ؽ�Ʈ�߰�
	printf("%s\n", Text);

	ReadFile.getline(Text, 256);
	// ��� : 2��° �� �ؽ�Ʈ�߰�
	printf("%s\n", Text);

	// ���� ��Ʈ�� �ݱ�
	ReadFile.close();

	return 0;
}