#include <iostream>

int main()
{	
	char Text1[128] = {"공격력 : 120"};
	char* Context = nullptr;

	char* TokResult = strtok_s(Text1, ":", &Context);

	int Attack = atoi(Context);

	char Text2[128] = {};

	sprintf_s(Text2, "새로운 문자열 만들기 %d\n", Attack);

	printf("Text2 = %s\n", Text2);

	return 0;
}