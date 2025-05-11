#include <iostream>

int main()
{

	FILE* FileStream = nullptr;

	// Test.txt ����
	fopen_s(&FileStream, "Test.txt", "wt");

	// ���� ��Ʈ���� ���� ��� ������ ���� �� �ִٴ� �ǹ�
	if (FileStream)
	{
		// ���Ͽ� �ؽ�Ʈ ����
		fputc('A', FileStream);
		fputs("File Stream Test\n", FileStream);
		fputs("Stream Test", FileStream);

		fclose(FileStream);
	}

	fopen_s(&FileStream, "Test.txt", "rt");

	if (FileStream)
	{
		char FirstText = fgetc(FileStream);
		// ��� : A
		printf("%c", FirstText);

		char Text[256] = {};

		fgets(Text, 256, FileStream);
		// ��� : File Stream Test
		printf("%s", Text);

		fgets(Text, 256, FileStream);
		// ��� : Stream Test
		printf("%s", Text);

		fclose(FileStream);
	}

	return 0;
}