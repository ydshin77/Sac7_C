
#include <iostream>
#include <time.h>

void main()
{
	srand(time(0));
	rand();

	// 1 ~ 10 까지의 숫자를 2개씩 가지고 있는 20개짜리 배열 생성
	int Number[20] = {};

	for (int i = 0; i < 10; ++i)
	{
		Number[i] = i + 1;
		Number[i + 10] = i + 1;
	}

	// 값을 랜덤으로 섞기
	for (int i = 0; i < 100; ++i)
	{
		int Index1 = rand() % 20;
		int Index2 = rand() % 20;

		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}

	// Open은 카드가 열렸는지 저장하는 배열
	bool Open[20] = {};
	// 이전의 입력한 값을 저장하는 변수
	int PrevOpenIndex = -1;

	while (true)
	{
		// 배열의 숫자를 가로 10개, 세로 2줄로 출력
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				// Open값이 true여야만 숫자가 공개됨
				// false면 * 출력
				if (Open[i * 10 + j])
					printf("%d\t", Number[i * 10 + j]);
				else
					printf("*\t");
			}
			printf("\n");
		}
		
		// 값을 입력받음
		int Input = 0;
		printf("0 ~ 19 사이의 숫자를 입력해주세요 (20은 게임 종료) : ");
		scanf_s("%d", &Input);

		if (Input == 20)
			break;
		else if (Input < 0 || Input > 19)
		{
			printf("잘못된 값을 입력하였습니다. 다시 입력해주세요\n");
			continue;
		}

		// 이미 오픈되어 있는 카드면 다시 입력받게 함
		if (Open[Input])
			continue;

		// 올바른 값을 입력했다면 Open 값을 true로 변경
		Open[Input] = true;

		// PrevOpenIndex가 -1이라면 첫 번째 카드를 오픈하는 것
		if (PrevOpenIndex == -1)
		{
			// Open 값이 true기 때문에 선택한 인덱스의 숫자가 오픈됨
			PrevOpenIndex = Input;
			continue;
		}

		// 2번째 카드를 오픈하면 둘의 값을 비교
		// 같지 않다면 Open 값이 false로 바뀌어 *이 출력되고
		// 같다면 Open 값은 계속 true기 때문에 계속해서 숫자로 출력됨
		if (Number[PrevOpenIndex] != Number[Input])
		{
			Open[PrevOpenIndex] = false;
			Open[Input] = false;
		}

		PrevOpenIndex = -1;

		// 전부 다 열리면 게임 종료
		bool AllOpen = true;
		for (int i = 0; i < 20; ++i)
		{
			// Open이 모두 true가 아니라면 모두 열린 것이 아님
			if (!Open[i])
			{
				AllOpen = false;
				break;
			}
		}

		if (AllOpen)
		{
			printf("\n모든 카드를 맞추셨네요! 게임을 종료할게요");
			break;
		}
		
	}

}