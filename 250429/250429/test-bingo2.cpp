
#include <iostream>
#include <time.h>

void main()
{
	srand(time(0));
	rand();

	// 25개짜리 배열 생성
	int Number[25] = {};

	// 1 ~ 25 까지의 값 넣기
	for (int i = 0; i < 25; ++i)
	{
		Number[i] = i + 1;
	}

	// 숫자 섞기
	for (int i = 0; i < 100; ++i)
	{
		int Index1 = rand() % 25;
		int Index2 = rand() % 25;
		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}

	// 입력 값을 저장하는 변수
	int Input = 0;
	// 완성된 줄의 수를 저장하는 변수
	int LineCount = 0;

	while (true)
	{
		// system("DoS에서 쓰는 명령어");
		// cls : 콘솔 화면의 텍스트를 모두 지워줌
		system("cls");

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

		// 5줄 이상을 완성했다면 게임 종료
		if (LineCount >= 5)
		{
			printf("굉장하군요! 게임을 종료합니다");
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

		// 찾아준 숫자의 인덱스를 저장하기 위한 변수
		int FindIndex = -1;

		// 입력한 숫자가 배열에 있는지 판단하기 위한 변수
		// 기본으로 못 찾았다는 의미인 false를 넣어두고, 찾았을 경우엔 true로 바꿈
		bool Find = false;

		for (int i = 0; i < 25; ++i)
		{
			if (Number[i] == Input)
			{
				// 인덱스 저장
				FindIndex = i;
				// 입력한 숫자를 찾았으니 true로 변경
				Find = true;
				// 해당 인덱스의 값을 -1로 바꿔 *로 출력
				Number[i] = -1;
				// 값을 -1로 바꾸면 더이상 같은 숫자(Input)가 없기 때문에 반복 종료
				break;
			}
		}

		// Find 변수가 true라면 배열에서 값을 찾았다는 의미 -> false면 못찾은 것
		// 못찾았을 경우엔 처음으로 돌아가 다시 출력하고 입력을 받게 함
		if (!Find)		// Find == false
			continue;

		// --------- 빙고 2와 다른 부분 : 빙고를 체크하는 방법 (위의 코드는 동일)
		// 입력한 숫자가 영향을 줄 수 있는 줄을 구함 (효율적)
		// 가로, 세로는 무조건 체크하고, 대각선 2줄에 영향을 줄 수 있는지 체크
		
		/*
		가로, 세로 체크
		가로 인덱스 : 인덱스 % 가로 개수
		세로 인덱스 : 인덱스 / 가로 개수
		*/

		int IndexX = FindIndex % 5;
		int IndexY = FindIndex / 5;

		int StarCount = 0, StarCount1 = 0;
		
		// 한 줄의 수만큼 반복
		for (int i = 0; i < 5; ++i)
		{
			// 가로줄 체크
			if (Number[IndexY * 5 + i] == -1)
				++StarCount;

			// 세로줄 체크
			if (Number[i * 5 + IndexX] == -1)
				++StarCount1;
		}
		
		if (StarCount == 5)
			++LineCount;

		if (StarCount1 == 5)
			++LineCount;

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
		

	}

}