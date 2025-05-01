
#include <iostream>

int StringCount(const char* Text)
{
	int Index = 0;

	while (Text[Index] != 0)
	{
		++Index;
	}

	return Index;
}

void StringCopy(char* Buffer, const char* Text)
{
	int Index = 0;

	while (Text[Index] != 0)
	{
		Buffer[Index] = Text[Index];
		++Index;
	}

	Buffer[Index] = 0;
}

void StringCat(char* Buffer, const char* Text)
{
	int Index = 0;

	while (Buffer[Index] != 0)
	{
		++Index;
	}

	int	Index1 = 0;

	while (Text[Index1] != 0)
	{
		Buffer[Index] = Text[Index1];
		++Index;
		++Index1;
	}

	Buffer[Index] = 0;
}

bool StringCmp(const char* Text1, const char* Text2)
{
	// ���ڿ��� ���̸� ���Ͽ� ������ �ٸ����� �Ǵ� -> �ٸ��� �Լ� ������ ��
	int Length1 = StringCount(Text1);
	int Length2 = StringCount(Text2);

	if (Length1 != Length2)
		return false;

	// ���ڿ��� ������ �Ǵ�
	for (int i = 0; i < Length1; ++i)
	{
		if (Text1[i] != Text2[i])
			return false;
	}
	return true;
}

int main()
{
	// ���ڿ� ���ͷ� : "" �ȿ� ���ڿ��� �� ��
	// utf-8 ���ڿ��� �ѱ� 1���� 3����Ʈ�� ǥ��, �ٸ� ���ڵ��� 2����Ʈ
	// "���ڿ� �׽�Ʈ" : �ѱ� 6�� 18����Ʈ + ���� 1����Ʈ + ������ 0 : 20����Ʈ
	
	// "sss" �̷��� �ϸ� const char �迭�� �ǰ� �ش� �迭�� ���� �ּҸ� ��ȯ�ϰ� ��
	// �׷��� ��ȯ�� Ÿ���� �迭�� const char �迭�̱� ������ const char*�� �νĵ�
	// char* Text = "���ڿ� �׽�Ʈ";
	const char* Text = "���ڿ� �׽�Ʈ";
	
	// �Ʒ�ó�� ���ڿ� �迭 �ʱ�ȭ�� ������
	char Text1[20] = "���ڿ� �׽�Ʈ";
	// Text1 = "Test";

	// string copy, ���ڿ� ���� �Լ�
	// 2�� ������ ���ڿ��� 1�� ������ �迭�� ��������
	strcpy_s(Text1, "���ڿ��̴�");

	printf("Text1 = %s\n", Text1);

	// �Ʒ������� �����迭�� ����� �� �迭�� ���� �ּҸ� ��ȯ���ְ� ����
	// ��ȯ�� �迭�� ���� �ּҴ� Text2 ������ ������ ��Ƶ�
	char* Text2 = new char[20];

	// �Ʒ����� Text2�� ����ϸ� �� ������ ������ �����̱� ������
	// �迭�� �����Ҵ��� �ߴ��� �Լ������� �ܼ� ������ ������ �ν��� ��
	// �׷��� ������ strcpy_s �Լ��� �����ε��� �Լ���
	// char*, rsize_t, const char* Ÿ������ �����ε��� �Լ��� ȣ��ǰ� ��
	
	// ���ۿ����÷ο찡 ���� �ʵ��� �����ϴ°� strcpr_s
	//strcpy_s(Text2, 20, "�����Լ��׽�Ʈ�Դϴ�....");

	printf("Text2 = %s\n", Text2);

	int Count = strlen("�����Ҵ��");

	Count = StringCount("�����Ҵ��");

	// String Length
	// size_t�� unsigned __int64 Ÿ��

	printf("Count = %d\n", Count);

	StringCopy(Text1, "�����Ҵ��");

	printf("Text1 = %s\n", Text1);

	char Text3[128] = {};

	strcpy_s(Text3, "���ڿ��׽�Ʈ");

	strcat_s(Text3, " ���ڿ����̱�");

	printf("Text3 = %s\n", Text3);

	StringCopy(Text3, "���ڿ�");
	StringCat(Text3, "���̱�");

	printf("Text3 = %s\n", Text3);

	// ���ڿ� �� string compare
	// ��ȯ���� 0�̸� �� ���ڿ��� ����
	// ������ ������ ���� ���ڿ��� ������ ���ڿ����� ���������� �տ� �ִٴ� �ǹ�
	// ����� ������ ������ ���ڿ��� ���� ���ڿ����� ���������� �տ� �ִٴ� �ǹ�
	int Result = strcmp("���ڿ�", "���ڿ�");

	printf("Result = %d\n", Result);

	Result = strcmp("���ڿ�2", "���ڿ�1");

	printf("Result = %d\n", Result);

	Result = strcmp("���ڿ�111", "���ڿ�22");

	printf("Result = %d\n", Result);

	printf("StringCmp = %d\n", StringCmp("���ڿ�", "���ڿ�"));

	char	Text4[128] = "���ݷ�, ����, ü��";

	 // string token ���ڿ� �и�
	 char* Context = nullptr;
	 char* TokResult = strtok_s(Text4, ",", &Context);

	 printf("Context = %s\n", Context);
	 printf("TokResult = %s\n", TokResult);

	 //Context = nullptr;
	 TokResult = strtok_s(nullptr, ",", &Context);

	 printf("Context = %s\n", Context);
	 printf("TokResult = %s\n", TokResult);

	 char Text5[128] = "���ݷ� : 120";
	 Context = nullptr;

	 TokResult = strtok_s(Text5, ":", &Context);

	 printf("Context = %s\n", Context);
	 printf("TokResult = %s\n", TokResult);

	 // Context�� ���� 120 ���ڿ��� ���� 120���� ��ȯ > atoi
	 // �ǿܷ� ���� ���� ��� (�𸮾󿡼� ���ڿ��� �ٷ� �� fstring ����ϴµ� �������� �ʴ� ��ɵ� ������ �˾Ƶα�)
	 int Attack = atoi(Context);
	 printf("Attack = %d\n", Attack);

	 // ���� 120�� ���ڿ� 120���� ��ȯ > itoa
	 char Text6[64] = {};
	 //itoa(Attack, Text6, 10);
	 _itoa_s(Attack, Text6, 10);
	 printf("Text6 = %s\n", Text6);

	 char Text7[128] = {};

	 // ���ڿ��� ������ִ� �Լ�
	 // 2, 3�� ���ڸ� �̿��Ͽ� printfó�� ���ڿ��� ������� �Ŀ� 1�������� ���ڿ��� ä����
	 sprintf_s(Text7, "Attack = %d", Attack);
	 printf("Text7 = %s\n", Text7);

	 // �弳 ���͸� ���� �����, ä�� �߿� �װ� �ִ��� ã�Ƽ� ���͸��� �� �ַ� ��� -> ���ڿ� ���� ǥ����

	return 0;
}