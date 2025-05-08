#include <iostream>

// strcpy_s(Text1, "문자열 테스트") 와 같은 방식
void StringCopy(char* Buffer, const char* Text)
{
	int Index = 0;

	while (Text[Index] != 0)
	{
		Buffer[Index] = Text[Index];
		++Index;
	}
	// 널 문자 복사
	Buffer[Index] = 0;
}

int main()
{
	char Text1[20] = "문자열 테스트";

	StringCopy(Text1, "복사할대상");
	
	printf("Text1 = %s\n", Text1);

	return 0;
}