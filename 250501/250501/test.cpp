#include <iostream>

// strcpy_s(Text1, "���ڿ� �׽�Ʈ") �� ���� ���
void StringCopy(char* Buffer, const char* Text)
{
	int Index = 0;

	while (Text[Index] != 0)
	{
		Buffer[Index] = Text[Index];
		++Index;
	}
	// �� ���� ����
	Buffer[Index] = 0;
}

int main()
{
	char Text1[20] = "���ڿ� �׽�Ʈ";

	StringCopy(Text1, "�����Ҵ��");
	
	printf("Text1 = %s\n", Text1);

	return 0;
}