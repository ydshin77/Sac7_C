
// main.cpp -> 중복되는 코드들 함수로 만들어서 출력하기

#include <iostream>
#include <time.h>

void SetNumber(int Number[25])
{
	for (int i = 0; i < 25; i++)
	{
		Number[i] = i + 1;
	}
}

void RandomNumber(int Number[25])
{
	for (int i = 0; i < 100; ++i)
	{
		int Index1 = rand() % 25;
		int Index2 = rand() % 25;
		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}
}

void TileOutput(int Number[25])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (Number[i * 5 + j] == -1)
				printf("*\t");
			else
				printf("%d\t", Number[i * 5 + j]);
		}
		printf("\n");
	}
}

void CheckXY(int Number[25], int IndexX, int IndexY, int StarCount, int StarCount1)
{
	for (int i = 0; i < 5; ++i)
	{
		if (Number[IndexY * 5 + i] == -1)
			++StarCount;
		if (Number[i * 5 + IndexX] == -1)
			++StarCount1;
	}
}

void PlusLineCount(int StarCount, int LineCount)
{
	if (StarCount == 5)
		++LineCount;
}

void main()
{
	srand(time(0));
	rand();

	int Number[25] = {};
	int AINumber[25] = {};

	SetNumber(Number);
	SetNumber(AINumber);

	RandomNumber(Number);
	RandomNumber(AINumber);

	int Input = 0;
	int LineCount = 0, AILineCount = 0;

	while (true)
	{
		system("cls");

		printf("======== Player ========\n");
		TileOutput(Number);
		printf("완성된 줄 : %d\n", LineCount);

		printf("======== AI ========\n");
		TileOutput(AINumber);
		printf("완성된 줄 : %d\n", AILineCount);
		
		printf("0 ~ 25 까지의 숫자를 입력하세요 (0: 종료) : ");
		scanf_s("%d", &Input);

		if (Input == 0)
			break;
		else if (Input < 0 || Input > 25)
		{
			printf("잘못된 숫자를 입력하였습니다\n");
			system("pause");
			continue;
		}

		bool Find = false;
		int FindIndex = -1, AIFindIndex = -1;

		for (int i = 0; i < 25; ++i)
		{
			if (Number[i] == Input)
			{
				FindIndex = i;
				Find = true;
				Number[i] = -1;
				break;
			}
		}

		if (!Find)
			continue;

		for (int i = 0; i < 25; ++i)
		{
			if (AINumber[i] == Input)
			{
				AIFindIndex = i;
				AINumber[i] = -1;
				break;
			}
		}

		int IndexX = FindIndex % 5, IndexY = FindIndex / 5;
		int AIIndexX = AIFindIndex % 5, AIIndexY = AIFindIndex / 5;
		int StarCount = 0, StarCount1 = 0;
		int AIStarCount = 0, AIStarCount1 = 0;

		CheckXY(Number, IndexX, IndexY, StarCount, StarCount1);
		CheckXY(AINumber, AIIndexX, AIIndexY, AIStarCount, AIStarCount1);
		
		PlusLineCount(StarCount, LineCount);
		PlusLineCount(StarCount1, LineCount);
		PlusLineCount(AIStarCount, AILineCount);
		PlusLineCount(AIStarCount1, AILineCount);

	}

}