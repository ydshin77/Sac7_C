
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

		// --------- 빙고 2와 다른 부분 : 빙고를 체크하는 방법
		// 12줄을 모두 체크하여 완성된 줄의 수를 구함 (비효율적)

		// 반복될 때마다 누적이 될 수도 있기 때문에, 코드가 돌아갈 때마다 0으로 초기화
		LineCount = 0;

		// *로 바뀐 수를 저장하기 위한 변수
		int StarCount = 0, StarCount1 = 0;

		// 가로, 세로 체크
		for (int i = 0; i < 5; ++i)
		{
			// *로 바뀐 걸 체크하기 전에, *의 수를 저장하기 위한 변수를 0으로 초기화
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

		// 대각선 체크

		// 왼쪽 상단 -> 오른쪽 하단 대각선 체크
		// 가로, 세로 체크할 때 StarCount에 값이 들어갔을 수도 있으니 다시 초기화
		StarCount = 0;
		for (int i = 0; i <= 24; i += 6)
		{
			if (Number[i] == -1)
				++StarCount;
		}

		if (StarCount == 5)
			++LineCount;

		// 오른쪽 상단 -> 왼쪽 하단 대각선 체크
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