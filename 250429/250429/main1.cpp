
#include <iostream>
#include <time.h>

void main()
{
	srand(time(0));
	rand();

	int Number[25] = {};

	// AI가 사용할 숫자 배열
	int AINumber[25] = {};

	// 위의 배열에 1 ~ 25 까지 차례로 대입
	for (int i = 0; i < 25; ++i)
	{
		Number[i] = i + 1;
		AINumber[i] = i + 1;
	}

	// 1 ~ 25 사이의 숫자를 섞음
	for (int i = 0; i < 100; ++i)
	{
		// 0 ~ 24 사이의 랜덤한 수를 얻어옴
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
		// system("DoS에서 쓰는 명령어");
		// cls : 콘솔 화면의 텍스트를 모두 지워줌
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

		// AI 출력
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
			printf("플레이어 승리\n");
			break;
		}
		else if (AILineCount >= 5)
		{
			printf("AI 승리\n");
			break;
		}

		// 숫자를 입력 받음
		printf("0 ~ 25 까지의 숫자를 입력하세요 (0: 종료) : ");
		scanf_s("%d", &Input);

		if (Input == 0)
			break;
		else if (Input < 0 || Input > 25)
		{
			printf("잘못된 숫자를 입력하였습니다\n");
			// pause : 콘솔 화면을 일시정지 시켜줌
			system("pause");
			continue;
		}

		// 입력한 숫자가 배열에 있는지 판단하기 위한 변수
		// 기본으로 못 찾았다는 의미로 false를 넣어두고, 찾았을 경우 true로 바꿈
		bool Find = false;

		// 찾아준 숫자의 인덱스를 저장하기 위한 변수
		int FindIndex = -1, AIFindIndex = -1;

		// 입력한 숫자가 배열에 있는지 찾기
		for (int i = 0; i < 25; ++i)
		{
			// 입력한 숫자가 숫자 배열에 있을 경우
			if (Number[i] == Input)
			{
				// 인덱스 저장
				FindIndex = i;

				Find = true;
				// 값이 -1일 경우 *로 취급
				Number[i] = -1;
				// 더이상 같은 숫자가 없기 때문에 반복 종료
				break;
			}
		}

		// Find 변수가 만약 true라면 배열에서 값을 찾았다는 의미
		// false라면 배열에서 값을 못 찾았다는 의미
		// 못찾았을 경우엔 처음으로 돌아가 다시 출력하고 입력을 받게 함
		if (!Find)	// Find == false
			continue;

		// AI의 숫자에서 입력한 숫자를 찾아 *로 만듦
		for (int i = 0; i < 25; ++i)
		{
			if (AINumber[i] == Input)
			{
				AIFindIndex = i;
				AINumber[i] = -1;
				break;
			}
		}


		// 2. 입력한 숫자가 영향을 줄 수 있는 줄을 구함 (효율적)
		// 가로, 세로는 무조건 체크하고 대각선 2줄에 영향을 줄 수 있는지 체크

		/*
		가로, 세로 체크
		가로 인덱스 : 인덱스 % 가로 개수
		세로 인덱스 : 인덱스 / 가로 개수
		7을 이용하여 가로 2, 세로 1를 구해야 함
		7 % 5 = 2
		7 / 5 = 1
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

		// AI가 입력 -> 1. 0~24의 숫자중 선택안된 숫자 선택 or 2. 줄을 완성할 가능성이 가장 높은 숫자 선택 / 게임의 장르에 따라 다름
		// 1. 선택할 수 있는 숫자 목록 만듦
		//int SelectNumber[25] = {};
		// 선택할 수 있는 숫자 목록의 개수
		//int SelectCount = 0;

		// 완성될 줄이 가장 많은 인덱스와 별이 가장 많은 인덱스를 저장할 변수 2개 선언
		// 인덱스가 아무 것도 없다는 걸 표현할 땐 -1로 초기화
		int AICheckIndex = -1, AICheckStarIndex = -1;
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
				AIStarCount = 0;
				AIStarCount1 = 0;

				for (int j = 0; j < 5; ++j)
				{
					// AI의 가로줄 체크
					if (AINumber[AIIndexY * 5 + j] == -1)
						++AIStarCount;

					// AI의 세로줄 체크
					if (AINumber[j * 5 + AIIndexX] == -1)
						++AIStarCount1;
				}

				// 위에서 현재 인덱스에 해당하는 가로, 세로 줄에 대해 *이 몇 개인지 저장을 해둠
				// 이전에 저장해둔 *의 개수와 현재 구해준 *의 개수를 비교하여 *이 더 많은 줄을 구해줌
				// 중복되는 코드가 많이 때문에 나중에 함수로 만들어놓고 하는게 편함 (두 줄을 한꺼번에 채울 수 있는 수 찾기를 만드려면 코드 또 떡칠)
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

				// 대각선 2줄에 대해서 체크한다.
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

		Input = AINumber[AICheckStarIndex];

		// 선택 가능한 숫자를 모아서 그 중 랜덤하게 하나를 선택하는 방식
		//for (int i = 0; i < 25; ++i)
		//{
		//	// 별이 아닐 경우
		//	if (AINumber[i] != -1)
		//	{
		//		SelectNumber[SelectCount] = AINumber[i];
		//		++SelectCount;
		//	}
		//}

		//Input = SelectNumber[rand() % SelectCount];

		// 플레이어의 숫자중 AI가 선택한 숫자를 찾아서 *로 바꿈
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