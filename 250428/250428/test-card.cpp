// 로또 실습

#include <iostream>
#include <time.h>

void main()
{
	srand(time(0));
	rand();

	// 1 ~ 45 까지의 숫자를 담아놓기 위한 배열 생성
	int Number[45] = {};

	// 1 ~ 45 까지의 값을 대입
	for (int i = 0; i < 45; ++i)
	{
		Number[i] = i + 1;
	}
	
	// 게임 수 입력
	int GameCount = 0;
	printf("게임 수를 입력하시오 : ");
	scanf_s("%d", &GameCount);
	printf("\n");

	// 숫자 섞기
	for (int i = 0; i < 100; ++i)
	{
		// 랜덤한 인덱스 2개를 구함
		int Index1 = rand() % 45;
		int Index2 = rand() % 45;

		// 스왑 알고리즘을 사용하여 값 바꾸기
		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}

	// 섞은 숫자를 오름차순으로 정렬
	for (int i = 0; i < 5; ++i)
	{
		for (int j = i + 1; j < 6; ++j)
		{
			if (Number[i] > Number[j])
			{
				int Temp = Number[i];
				Number[i] = Number[j];
				Number[j] = Temp;
			}
		}
	}

	// 결과값 저장
	int Result[7] = {};
	for (int i = 0; i < 7; ++i)
		Result[i] = Number[i];

	printf("당첨 번호 : \n");

	for (int i = 0; i < 6; ++i)
		// \t : Tab 1 해주는 것
		printf("%d\t", Result[i]);

	printf("/\t%d\n", Result[6]); 
	printf("\n");

	// 입력한 게임 수만큼 6개의 랜덤한 번호 출력
	for (int Game = 0; Game < GameCount; ++Game)
	{
		for (int i = 0; i < 100; ++i)
		{
			int Index1 = rand() % 45;
			int Index2 = rand() % 45;

			int Temp = Number[Index1];
			Number[Index1] = Number[Index2];
			Number[Index2] = Temp;
		}

		for (int i = 0; i < 5; ++i)
		{
			for (int j = i + 1; j < 6; ++j)
			{
				if (Number[i] > Number[j])
				{
					int Temp = Number[i];
					Number[i] = Number[j];
					Number[j] = Temp;
				}
			}
		}

		for (int i = 0; i < 6; ++i)
			printf("%d\t", Number[i]);

		// 당첨 번호와 몇 개가 같은지 저장하는 변수 생성
		int Pair = 0;

		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				// 같은 숫자가 있을 경우 Pair를 1 증가하고 다음 숫자 검사
				if (Result[i] == Number[j])
				{
					++Pair;
					break;
				}
			}
		}

		switch (Pair)
		{
		case 3:
			printf(" : 5등\n");
			break;
		case 4:
			printf(" : 4등\n");
			break;
		case 5:
			// 보너스 번호가 있는지 비교
			bool Second;
			Second = false;
			for (int i = 0; i < 6; ++i)
			{
				if (Result[6] == Number[i])
				{
					Second = true;
					break;
				}
			}
			if (Second)
				printf(" : 2등\n");
			else
				printf(" : 3등\n");
		case 6 :
			printf(" : 1등\n");
			break;
		default:
			printf(" : 꽝\n");
			break;
		}

	}

}