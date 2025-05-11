#include <iostream>

enum class EPlayerJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion
};

struct FPlayerInfo
{
	char		Name[32] = {};
	EPlayerJob	Job = EPlayerJob::Knight;
	int			Attack = 0;
	int			Defense = 0;
	int			HP = 0;
	int			HPMax = 0;
	int			MP = 0;
	int			MPMax = 0;
};

int main()
{
	FILE* FileStream = nullptr;
	fopen_s(&FileStream, "Test1.tbf", "wb");

	if (FileStream)
	{
		// ���� ����
		int Number = 100;

		fwrite(&Number, sizeof(int), 1, FileStream);

		// �迭 ����
		int Array[10] = {};

		for (int i = 0; i < 10; ++i)
		{
			Array[i] = i + 1;
		}

		fwrite(Array, sizeof(int), 10, FileStream);

		// ����ü ����
		FPlayerInfo Player;

		strcpy_s(Player.Name, "�ο���");
		Player.Attack = 100;
		Player.Defense = 50;
		Player.HP = 500;
		Player.HPMax = 500;
		Player.MP = 100;
		Player.MPMax = 100;

		// ����ü�� �پ��� �������� �ϳ��� ������ ���ӵ� �޸𸮷� ���̴ϱ� ������ 1
		fwrite(&Player, sizeof(FPlayerInfo), 1, FileStream);

		fclose(FileStream);
	}

	fopen_s(&FileStream, "Test1.tbf", "rb");

	if (FileStream)
	{
		// ���� �о����
		int Number = 0;

		fread(&Number, sizeof(int), 1, FileStream);

		// ��� : 100
		printf("Number = %d\n", Number);

		// �迭 �о����
		int Array[10] = {};

		fread(Array, sizeof(int), 10, FileStream);

		// ��� : 1 ~ 10
		for (int i = 0; i < 10; ++i)
		{
			printf("Array[%d] = %d\n", i, Array[i]);
		}

		// ����ü �о����
		FPlayerInfo Player;

		fread(&Player, sizeof(FPlayerInfo), 1, FileStream);

		// �̸� ���
		printf("�̸� : %s\n", Player.Name);

		// ���� ���
		switch (Player.Job)
		{
		case EPlayerJob::Knight:
			printf("���� : ���\n");
			break;
		case EPlayerJob::Archer:
			printf("���� : �ü�\n");
			break;
		case EPlayerJob::Magicion:
			printf("���� : ������\n");
			break;
		}

		// ���ݷ�, ���� ���
		printf("���ݷ� : %d\t\t���� : %d\n", Player.Attack, Player.Defense);

		// ü��, ���� ���
		printf("ü�� : %d / %d\t���� : %d / %d",
			Player.HP, Player.HPMax, Player.MP, Player.MPMax);

		fclose(FileStream);
	}

	return 0;
}