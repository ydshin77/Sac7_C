#include <iostream>

int main()
{

	FILE* FileStream = nullptr;

	// Test.txt 생성
	fopen_s(&FileStream, "Test.txt", "wt");

	// 파일 스트림이 있을 경우 파일을 만들 수 있다는 의미
	if (FileStream)
	{
		// 파일에 텍스트 저장
		fputc('A', FileStream);
		fputs("File Stream Test\n", FileStream);
		fputs("Stream Test", FileStream);

		fclose(FileStream);
	}

	fopen_s(&FileStream, "Test.txt", "rt");

	if (FileStream)
	{
		char FirstText = fgetc(FileStream);
		// 출력 : A
		printf("%c", FirstText);

		char Text[256] = {};

		fgets(Text, 256, FileStream);
		// 출력 : File Stream Test
		printf("%s", Text);

		fgets(Text, 256, FileStream);
		// 출력 : Stream Test
		printf("%s", Text);

		fclose(FileStream);
	}

	return 0;
}