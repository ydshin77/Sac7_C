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
		// 정수 저장
		int Number = 100;

		fwrite(&Number, sizeof(int), 1, FileStream);

		// 배열 저장
		int Array[10] = {};

		for (int i = 0; i < 10; ++i)
		{
			Array[i] = i + 1;
		}

		fwrite(Array, sizeof(int), 10, FileStream);

		// 구조체 저장
		FPlayerInfo Player;

		strcpy_s(Player.Name, "민예식");
		Player.Attack = 100;
		Player.Defense = 50;
		Player.HP = 500;
		Player.HPMax = 500;
		Player.MP = 100;
		Player.MPMax = 100;

		// 구조체는 다양한 변수들이 하나에 묶여서 연속된 메모리로 묶이니까 개수는 1
		fwrite(&Player, sizeof(FPlayerInfo), 1, FileStream);

		fclose(FileStream);
	}

	fopen_s(&FileStream, "Test1.tbf", "rb");

	if (FileStream)
	{
		// 정수 읽어오기
		int Number = 0;

		fread(&Number, sizeof(int), 1, FileStream);

		// 출력 : 100
		printf("Number = %d\n", Number);

		// 배열 읽어오기
		int Array[10] = {};

		fread(Array, sizeof(int), 10, FileStream);

		// 출력 : 1 ~ 10
		for (int i = 0; i < 10; ++i)
		{
			printf("Array[%d] = %d\n", i, Array[i]);
		}

		// 구조체 읽어오기
		FPlayerInfo Player;

		fread(&Player, sizeof(FPlayerInfo), 1, FileStream);

		// 이름 출력
		printf("이름 : %s\n", Player.Name);

		// 직업 출력
		switch (Player.Job)
		{
		case EPlayerJob::Knight:
			printf("직업 : 기사\n");
			break;
		case EPlayerJob::Archer:
			printf("직업 : 궁수\n");
			break;
		case EPlayerJob::Magicion:
			printf("직업 : 마법사\n");
			break;
		}

		// 공격력, 방어력 출력
		printf("공격력 : %d\t\t방어력 : %d\n", Player.Attack, Player.Defense);

		// 체력, 마나 출력
		printf("체력 : %d / %d\t마나 : %d / %d",
			Player.HP, Player.HPMax, Player.MP, Player.MPMax);

		fclose(FileStream);
	}

	return 0;
}