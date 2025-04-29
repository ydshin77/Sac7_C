
#include <iostream>
#include <time.h>

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

void main() {

	

	srand(time(0));
	rand();

	// 1 ~ 10 까지 숫자를 2개씩 가지고 있는 20개짜리 배열을 만들고 섞기
	// Open은 카드가 열렸는지 저장하는 배열
	int Number[20] = {};
	bool Open[20] = {};

	for (int i = 0; i < 10; ++i)
	{
		Number[i] = i + 1;
		Number[i + 10] = i + 1;
	}

	for (int i = 0; i < 100; ++i)
	{
		int Index1 = rand() % 20;
		int Index2 = rand() % 20;

		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}

	int PrevOpenIndex = -1;

	while (true) {
		// 배열의 숫자를 가로 10개, 세로 2줄로 출력
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (Open[i * 10 + j])
					printf("%d\t", Number[i * 10 + j]);
				else
					printf("*\t");
			}
			printf("\n");
		}

		// 0 ~ 20 사이의 숫자를 입력 받음
		// 입력 받은 숫자가 20일 경우 break를 이용해 while문을 빠져나감
		int Input = 0;
		printf("0 ~ 19 사이의 숫자를 입력해주세요 (20은 게임 종료) : ");
		scanf_s("%d", &Input);

		if (Input == 20)
			break;
		// 0 ~ 19 사이의 값이 아닐 경우 다시 출력하고 입력 받게 함
		else if (Input < 0 || Input > 19)
			continue;
		// 이미 오픈되어 있는 카드라면 다시 입력받게 함
		if (Open[Input])
			continue;

		Open[Input] = true;

		// 카드 2개를 오픈하면 2개의 카드가 서로 같은 값인지 비교하여
		// 같은 값이면 계속 오픈된 상태를 유지하고
		// 다른 값이면 두 카드를 클로즈 상태로 만듦
		// PrevOpenIndex가 -1이라면 첫 번째 카드를 오픈하는 것

		if (PrevOpenIndex == -1)
		{
			PrevOpenIndex = Input;
			continue;
		}

		// 2번째 카드를 오픈하면 둘의 값 비교
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