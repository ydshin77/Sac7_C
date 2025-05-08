
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
	char	Name[32] = {};
	EPlayerJob	Job = EPlayerJob::Knight;
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		HPMax = 0;
	int		MP = 0;
	int		MPMax = 0;
};

int main()
{
	/*
	바이너리파일 : 특정 메모리의 데이터를 그대로 파일에 옮겨서 저장할 때
	사용한다.
	*/
	FILE* FileStream = nullptr;
	fopen_s(&FileStream, "Test1.tbf", "wb");
	
	if (FileStream)
	{
		int	Number = 100;

		// 1번인자의 주소로부터 번인자의 크기 * 3번인자의 개수 만큼의 
		// 바이트를 파일에 복사한다.
		fwrite(&Number, sizeof(int), 1, FileStream);

		int	Array[10] = {};

		for (int i = 0; i < 10; ++i)
		{
			Array[i] = i + 1;
		}

		fwrite(Array, sizeof(int), 10, FileStream);

		FPlayerInfo	Player;

		strcpy_s(Player.Name, "기사");
		Player.Attack = 100;
		Player.Defense = 50;
		Player.HP = 500;
		Player.HPMax = 500;
		Player.MP = 100;
		Player.MPMax = 100;

		fwrite(&Player, sizeof(FPlayerInfo), 1, FileStream);

		fclose(FileStream);
	}

	fopen_s(&FileStream, "Test1.tbf", "rb");

	if (FileStream)
	{
		int	Number = 0;

		fread(&Number, sizeof(int), 1, FileStream);

		printf("Number = %d\n", Number);

		int	Array[10] = {};

		fread(Array, sizeof(int), 10, FileStream);

		for (int i = 0; i < 10; ++i)
		{
			printf("Array[%d] = %d\n", i, Array[i]);
		}

		FPlayerInfo	Player;

		fread(&Player, sizeof(FPlayerInfo), 1, FileStream);

		printf("이름 : %s\n", Player.Name);

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
		printf("공격력 : %d\t방어력 : %d\n", Player.Attack,
			Player.Defense);
		printf("체력 : %d / %d\t마나 : %d / %d\n",
			Player.HP, Player.HPMax, Player.MP, Player.MPMax);

		fclose(FileStream);
	}

	return 0;
}