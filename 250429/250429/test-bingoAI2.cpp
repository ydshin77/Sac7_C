
#include <iostream>
#include <time.h>

void main()
{
	srand(time(0));
	rand();

	int Number[25] = {};
	// AI가 사용할 숫자 배열
	int AINumber[25] = {};

	// 1 ~ 25 까지 차례로 대입
	for (int i = 0; i < 25; ++i)
	{
		Number[i] = i + 1;
		AINumber[i] = i + 1;
	}

	// 숫자 섞기
	for (int i = 0; i < 100; ++i)
	{
		int Index1 = rand() % 25;
		int Index2 = rand() % 25;

		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;

		Index1 = rand() % 25;
		Index2 = rand() % 25;

		Temp = AINumber[Index1];
		AINumber[Index1] = AINumber[Index2];
		AINumber[Index2] = Temp;
	}

	int Input = 0;
	int LineCount = 0, AILineCount = 0;

	while (true)
	{
		system("cls");

		// 플레이어 정보 출력
		printf("======== Player ========\n");
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

		printf("완성된 줄 : %d\n", LineCount);

		// AI 정보 출력
		printf("======== AI ========\n");
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (AINumber[i * 5 + j] == -1)
					printf("*\t");
				else
					printf("%d\t", AINumber[i * 5 + j]);
			}
			printf("\n");
		}

		printf("완성된 줄 : %d\n", AILineCount);

		// 5줄 이상을 완성했다면 게임 종료
		if (LineCount >= 5)
		{
			printf("플레이어 승리!");
			break;
		}
		else if (AILineCount >= 5)
		{
			printf("AI 승리!");
			break;
		}

		// 숫자 입력 받기
		printf("0 ~ 25 까지의 숫자를 입력하세요 (0은 종료) : ");
		scanf_s("%d", &Input);

		if (Input == 0)
			break;
		else if (Input < 0 || Input > 25)
		{
			printf("잘못된 숫자를 입력하였습니다\n");
			system("pause");
			continue;
		}

		int FindIndex = -1, AIFindIndex = -1;
		bool Find = false;

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

		// AI 숫자에서 입력한 숫자를 찾아 *로 만듦
		for (int i = 0; i < 25; ++i)
		{
			if (AINumber[i] == Input)
			{
				AIFindIndex = i;
				AINumber[i] = -1;
				break;
			}
		}

		/*
		가로, 세로 체크
		가로 인덱스 : 인덱스 % 가로 개수
		세로 인덱스 : 인덱스 / 가로 개수
		*/

		int IndexX = FindIndex % 5;
		int IndexY = FindIndex / 5;
		int AIIndexX = AIFindIndex % 5;
		int AIIndexY = AIFindIndex / 5;

		int StarCount = 0, StarCount1 = 0;
		int AIStarCount = 0, AIStarCount1 = 0;

		// 한 줄의 수만큼 반복
		for (int i = 0; i < 5; ++i)
		{
			// 가로줄 체크
			if (Number[IndexY * 5 + i] == -1)
				++StarCount;

			// 세로줄 체크
			if (Number[i * 5 + IndexX] == -1)
				++StarCount1;

			// AI의 가로줄 체크
			if (AINumber[AIIndexY * 5 + i] == -1)
				++AIStarCount;

			// AI의 세로줄 체크
			if (AINumber[i * 5 + AIIndexX] == -1)
				++AIStarCount1;
		}

		if (StarCount == 5)
			++LineCount;

		if (StarCount1 == 5)
			++LineCount;

		if (AIStarCount == 5)
			++AILineCount;

		if (AIStarCount1 == 5)
			++AILineCount;

		// 대각선 인덱스 : 0, 6, 12, 18, 24
		if (FindIndex % 6 == 0)
		{
			StarCount = 0;
			for (int i = 0; i <= 24; i += 6)
			{
				if (Number[i] == -1)
					++StarCount;
			}
			if (StarCount == 5)
				++LineCount;
		}

		if (AIFindIndex % 6 == 0)
		{
			AIStarCount = 0;
			for (int i = 0; i <= 24; i += 6)
			{
				if (AINumber[i] == -1)
					++AIStarCount;
			}
			if (AIStarCount == 5)
				++AILineCount;
		}

		// 대각선 인덱스 : 4, 8, 12, 16, 20 -> 0과 24는 제외
		if (FindIndex % 4 == 0 && FindIndex != 0 && FindIndex != 24)
		{
			StarCount = 0;
			for (int i = 4; i <= 20; i += 4)
			{
				if (Number[i] == -1)
					++StarCount;
			}
			if (StarCount == 5)
				++LineCount;
		}

		if (AIFindIndex % 4 == 0 && AIFindIndex != 0 && AIFindIndex != 24)
		{
			AIStarCount = 0;
			for (int i = 4; i <= 20; i += 4)
			{
				if (AINumber[i] == -1)
					++AIStarCount;
			}
			if (AIStarCount == 5)
				++AILineCount;
		}

		// --------- AI가 입력 -> AI 빙고1 과 다른 부분
		// : AI가 숫자를 입력하는 알고리즘 (위의 코드는 동일)
		// -> 게임의 장르에 따라 선택하기
		
		// 인덱스가 아무 것도 없다는 걸 표현할 땐 -1로 초기화
		// 별이 가장 많은 인덱스와 가장 많은 별의 개수를 저장하는 변수 선언
		int AICheckStarIndex = -1;
		int AIPrevStarCount = -1;
		
		// 선택 가능한 숫자 중 가장 많은 줄을 완성할 수 있는 숫자를 선택하는 방식
		// 아무 줄도 완성할 수 없다면 줄에 별이 가장 많은 것 선택
		for (int i = 0; i < 25; ++i)
		{
			// 별이 아닐 경우에만 체크
			if (AINumber[i] != -1)
			{
				AIIndexX = i % 5;
				AIIndexY = i / 5;
				AIStarCount = 0, AIStarCount1 = 0;

				for (int j = 0; j < 5; ++j)
				{
					// AI의 가로줄 체크
					if (AINumber[AIIndexY * 5 + j] == -1)
						++AIStarCount;

					// AI의 세로줄 체크
					if (AINumber[j * 5 + AIIndexX] == -1)
						++AIStarCount1;
				}

				// 위에서 현재 인덱스에 해당하는 가로, 세로 줄에 대해 별이 몇 개인지 저장을 해둠
				// 이전에 저장해둔 별의 개수와 현재 구해준 별의 개수를 비교하여 별이 더 많은 줄을 구함
				if (AIPrevStarCount < AIStarCount)
				{
					AICheckStarIndex = i;
					AIPrevStarCount = AIStarCount;
				}
				else if (AIPrevStarCount < AIStarCount1)
				{
					AICheckStarIndex = i;
					AIPrevStarCount = AIStarCount1;
				}

				// 대각선 2줄에 대해서 체크
				if (AIFindIndex % 6 == 0)
				{
					AIStarCount = 0;
					for (int i = 0; i <= 24; i += 6)
					{
						if (AINumber[i] == -1)
							++AIStarCount;
					}

					if (AIPrevStarCount < AIStarCount)
					{
						AICheckStarIndex = i;
						AIPrevStarCount = AIStarCount;
					}
				}

				if (AIFindIndex % 4 == 0 && AIFindIndex != 0 && AIFindIndex != 24)
				{
					AIStarCount = 0;
					for (int i = 4; i <= 20; i += 4)
					{
						if (AINumber[i] == -1)
							++AIStarCount;
					}

					if (AIPrevStarCount < AIStarCount)
					{
						AICheckStarIndex = i;
						AIPrevStarCount = AIStarCount;
					}
				}


			}


		}

		// 별이 가장 많은 인덱스를 선택 후 Input에 저장
		Input = AINumber[AICheckStarIndex];
		
		// 플레이어의 숫자 중 AI가 선택한 숫자를 찾아서 *로 바꿈
		// 중복될 숫자가 나올 확률 0% (아래의 코드는 AI 1과 동일)
		for (int i = 0; i < 25; ++i)
		{
			if (Number[i] == Input)
			{
				FindIndex = i;
				Number[i] = -1;
				break;
			}
		}

		for (int i = 0; i < 25; ++i)
		{
			if (AINumber[i] == Input)
			{
				AIFindIndex = i;
				AINumber[i] = -1;
				break;
			}
		}

		IndexX = FindIndex % 5;
		IndexY = FindIndex / 5;
		AIIndexX = AIFindIndex % 5;
		AIIndexY = AIFindIndex / 5;

		StarCount = 0, StarCount1 = 0;
		AIStarCount = 0, AIStarCount1 = 0;

		// 한 줄의 수만큼 반복
		for (int i = 0; i < 5; ++i)
		{
			// 가로줄 체크
			if (Number[IndexY * 5 + i] == -1)
				++StarCount;

			// 세로줄 체크
			if (Number[i * 5 + IndexX] == -1)
				++StarCount1;

			// AI의 가로줄 체크
			if (AINumber[AIIndexY * 5 + i] == -1)
				++AIStarCount;

			// AI의 세로줄 체크
			if (AINumber[i * 5 + AIIndexX] == -1)
				++AIStarCount1;
		}

		if (StarCount == 5)
			++LineCount;

		if (StarCount1 == 5)
			++LineCount;

		if (AIStarCount == 5)
			++AILineCount;

		if (AIStarCount1 == 5)
			++AILineCount;

		// 대각선 인덱스 : 0, 6, 12, 18, 24
		if (FindIndex % 6 == 0)
		{
			StarCount = 0;
			for (int i = 0; i <= 24; i += 6)
			{
				if (Number[i] == -1)
					++StarCount;
			}
			if (StarCount == 5)
				++LineCount;
		}

		if (AIFindIndex % 6 == 0)
		{
			AIStarCount = 0;
			for (int i = 0; i <= 24; i += 6)
			{
				if (AINumber[i] == -1)
					++AIStarCount;
			}
			if (AIStarCount == 5)
				++AILineCount;
		}

		// 대각선 인덱스 : 4, 8, 12, 16, 20 -> 0과 24는 제외
		if (FindIndex % 4 == 0 && FindIndex != 0 && FindIndex != 24)
		{
			StarCount = 0;
			for (int i = 4; i <= 20; i += 4)
			{
				if (Number[i] == -1)
					++StarCount;
			}
			if (StarCount == 5)
				++LineCount;
		}

		if (AIFindIndex % 4 == 0 && AIFindIndex != 0 && AIFindIndex != 24)
		{
			AIStarCount = 0;
			for (int i = 4; i <= 20; i += 4)
			{
				if (AINumber[i] == -1)
					++AIStarCount;
			}
			if (AIStarCount == 5)
				++AILineCount;
		}


	}

}