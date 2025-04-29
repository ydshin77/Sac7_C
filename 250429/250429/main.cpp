
#include <iostream>
#include <time.h>

void main()
{
	/*
	1 ~ 25 사이의 숫자를 저장하기 위한 배열 25개짜리를 만듦
	1 ~ 25 사이의 숫자를 골고루 섞어줌
	while문을 이용하여 무한루프를 돌며 5x5로 출력하고 숫자를 입력받음
	입력 받은 숫자가 0이라면 게임을 종료하고 1 ~ 25 사이의 숫자라면
	해당 숫자를 찾아서 *로 출력함
	한 줄이 모두 *로 바뀌면 줄 카운트가 증가
	가로 5줄, 세로 5줄, 대각선 2줄에 대해 완성된 줄을 체크하여
	5줄 이상이면 게임 종료
	*/

	srand(time(0));
	rand();

	int Number[25] = {};

	// 위의 배열에 1 ~ 25 까지 차례로 대입
	for (int i = 0; i < 25; ++i)
	{
		Number[i] = i + 1;
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
	}

	int Input = 0;
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
			break;

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
		int FindIndex = -1;

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
		
		// 2. 입력한 숫자가 영향을 줄 수 있는 줄을 구함 (효율적)
		// 가로, 세로는 무조건 체크하고 대각선 2줄에 영향을 줄 수 있는지 체크

		/*
		가로, 세로 체크
		가로 인덱스 : 인덱스 % 가로 개수
		세로 인덱스 : 인덱스 / 가로 개수
		ex. 7을 이용하여 가로 2, 세로 1를 구해야 함
		7 % 5 = 2
		7 / 5 = 1
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

		/*
		// 1. 12줄을 모두 체크하여 완성된 줄의 수를 구함 (비효율적)
		LineCount = 0;

		// *로 바뀐 수를 저장하기 위한 변수
		int StarCount = 0, StarCount1 = 0;

		for (int i = 0; i < 5; ++i)
		{
			// *로 바뀐 걸 체크하기 전에 *의 수를 저장하기 위한 변수를 0으로 초기화
			StarCount = 0;
			StarCount1 = 0;

			// j for문을 5번 돌며 별의 숫자가 몇 개인지 구함
			for (int j = 0; j < 5; ++j)
			{
				// 가로줄 체크
				if (Number[i * 5 + j] == -1)
					++StarCount;

				// 세로줄 체크
				if (Number[j * 5 + i] == -1)
					++StarCount1;
			}

			// 한 줄이 모두 *로 바뀌었을 경우 줄 수 증가
			if (StarCount == 5)
				++LineCount;

			if (StarCount1 == 5)
				++LineCount;
		}

		StarCount = 0;

		// 왼쪽 상단 - > 오른쪽 하단 대각선 체크
		for (int i = 0; i <= 24; i += 6)
		{
			if (Number[i] == -1)
				++StarCount;
		}

		if (StarCount == 5)
			++LineCount;

		StarCount = 0;

		// 오른쪽 상단 -> 왼쪽 하단 대각선 체크

		for (int i = 4; i <= 20; i += 4)
		{
			if (Number[i] == -1)
				++StarCount;
		}

		if (StarCount == 5)
			++LineCount;
		*/

	}

}