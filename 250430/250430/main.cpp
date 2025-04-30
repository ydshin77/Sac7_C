// 함수를 사용하여 작성한 빙고 게임

#include <iostream>
#include <time.h>

// 전처리기 -> 컴파일 전에 수행
// define : 뒤에 쓴 코드를 복사해주는 것, 그 후 컴파일
// 장점 : 가독성 좋음, 값 바꿀 때 좋음 -> 효율적 / 단점 : 디버깅이 까다로움
// const int로 선언해도 전혀 문제 없음
#define LINECOUNT	5
#define ARRAYCOUNT	(LINECOUNT * LINECOUNT)

// 함수로 기능을 만들어 놓고 main에 필요한 걸 갖고와서 사용하기에 익숙해져야 함

// 함수를 선언과 구현 동시에 해도 되지만, 위에는 함수, 밑에는 구현. 이렇게 따로 해도 됨
// 위에 함수 선언 -> 어딘가에 구현 부분이 있을 것이다 / main 함수 밑에 구현 가능
// 함수 이름 클릭 후 F12 누르면 함수 정의 부분으로 이동 -> 다시 누르면 선언 부분으로
// 함수 선언부분 블록 잡고 컨트롤+. > c 누르면 구현 부분 자동 생성됨
// 단어 선택 : 더블클릭, 컨트롤클릭
void SetNumber(int Number[ARRAYCOUNT]);
void Shuffle(int Number[ARRAYCOUNT]);
void OutputInfo(int Number[ARRAYCOUNT], int LineCount);
int ChangeNumber(int Number[ARRAYCOUNT], int Input);
int ComputeLineCount(int Number[ARRAYCOUNT], int Index);
int SelectAI(int Number[ARRAYCOUNT]);

void main()
{
	srand(time(0));
	rand();
	
	// 배열[] 안에는 상수가 들어가야 됨 -> const 사용 가능
	// const int Count = 25;

	// 숫자 배열 생성
	int Number[ARRAYCOUNT] = {};
	int AINumber[ARRAYCOUNT] = {};

	// 숫자에 값 넣기
	SetNumber(Number);
	SetNumber(AINumber);

	// 숫자 섞기
	Shuffle(Number);
	Shuffle(AINumber);

	int Input = 0;
	int LineCount = 0, AILineCount = 0;

	while (true)
	{
		system("cls");

		// 플레이어 정보 출력
		printf("======== Player ========\n");
		OutputInfo(Number, LineCount);

		// AI 정보 출력
		printf("======== AI ========\n");
		OutputInfo(AINumber, AILineCount);

		// 5줄 이상 완성했다면 게임 종료
		if (LineCount >= LINECOUNT)
		{
			printf("플레이어 승리\n");
			break;
		}
		else if (AILineCount >= LINECOUNT)
		{
			printf("AI 승리\n");
			break;
		}

		// 숫자를 입력 받음
		printf("0 ~ 25 까지의 숫자를 입력하세요 (0: 종료) : ");
		scanf_s("%d", &Input);

		if (Input == 0)
			break;
		else if (Input < 0 || Input > ARRAYCOUNT)
		{
			printf("잘못된 숫자를 입력하였습니다\n");
			system("pause");
			continue;
		}

		// 입력한 숫자를 *로 바꿔줌
		int FindIndex = ChangeNumber(Number, Input);
		
		// *로 바꾼 인덱스가 -1이라면 이미 *로 바꾼 숫자를 입력한 것이므로 다시 입력받게 함
		if (FindIndex == -1)
			continue;

		int AIFindIndex = ChangeNumber(AINumber, Input);

		// 줄 수 체크
		// ComputeLineCount 함수에서 넘겨준 인덱스를 *로 바꾸었을 경우
		// 몇 줄이 추가되어야 하는지를 반환
		LineCount += ComputeLineCount(Number, FindIndex);
		AILineCount += ComputeLineCount(AINumber, AIFindIndex);

		// AI가 입력
		Input = SelectAI(AINumber);

		// AI가 찾아준 숫자를 *로 바꿔줌
		FindIndex = ChangeNumber(Number, Input);
		AIFindIndex = ChangeNumber(AINumber, Input);

		LineCount += ComputeLineCount(Number, FindIndex);
		AILineCount += ComputeLineCount(AINumber, AIFindIndex);

	}

}

void SetNumber(int Number[ARRAYCOUNT])
{
	for (int i = 0; i < ARRAYCOUNT; ++i)
	{
		Number[i] = i + 1;
	}
}

void Shuffle(int Number[ARRAYCOUNT])
{
	for (int i = 0; i < 100; ++i)
	{
		// 0 ~ 24 사이의 랜덤한 수 얻어옴
		int Index1 = rand() % ARRAYCOUNT;
		int Index2 = rand() % ARRAYCOUNT;

		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}
}

void OutputInfo(int Number[ARRAYCOUNT], int LineCount)
{
	for (int i = 0; i < LINECOUNT; ++i)
	{
		for (int j = 0; j < LINECOUNT; ++j)
		{
			if (Number[i * LINECOUNT + j] == -1)
				printf("*\t");
			else
				printf("%d\t", Number[i * LINECOUNT + j]);
		}
		printf("\n");
	}

	printf("완성된 줄 : %d\n", LineCount);
}

int ChangeNumber(int Number[ARRAYCOUNT], int Input)
{
	for (int i = 0; i < ARRAYCOUNT; ++i)
	{
		// 입력한 숫자가 숫자 배열에 있을 경우
		if (Number[i] == Input)
		{
			// 값이 -1일 경우 *로 취급
			Number[i] = -1;
			// 찾아준 값의 배열 인덱스 반환
			return i;
		}
	}
	// 위의 for문에서 못 찾을 경우 여기로 와서 -1 반환
	// 이 경우 못 찾은 것 -> 이미 *로 바뀐 숫자를 입력한 경우
	return -1;
}

int ComputeLineCount(int Number[ARRAYCOUNT], int Index)
{
	// 함수에 LineCount 인자를 넣을 수도 있음
	// 몇 개가 추가되는지에 따라서 return 해줌

	// 가로, 세로 체크
	int LineCount = 0;

	int IndexX = Index % LINECOUNT;
	int IndexY = Index / LINECOUNT;

	int StarCount = 0, StarCount1 = 0;

	// 한 줄의 수만큼 반복
	for (int i = 0; i < LINECOUNT; ++i)
	{
		// 가로줄 체크
		if (Number[IndexY * LINECOUNT + i] == -1)
			++StarCount;

		// 세로줄 체크
		if (Number[i * LINECOUNT + IndexX] == -1)
			++StarCount1;
	}

	if (StarCount == LINECOUNT)
		++LineCount;

	if (StarCount1 == LINECOUNT)
		++LineCount;

	// 대각선 인덱스 : 0, 6, 12, 18, 24
	if (Index % (LINECOUNT + 1) == 0)
	{
		StarCount = 0;
		for (int i = 0; i < ARRAYCOUNT; i += (LINECOUNT + 1))
		{
			if (Number[i] == -1)
				++StarCount;
		}
		if (StarCount == LINECOUNT)
			++LineCount;
	}

	// 대각선 인덱스 : 4, 8, 12, 16, 20
	if (Index % (LINECOUNT - 1) == 0 && Index != 0 && Index != (ARRAYCOUNT - 1))
	{
		StarCount = 0;
		for (int i = LINECOUNT - 1; i <= (LINECOUNT * (LINECOUNT - 1)); i += (LINECOUNT - 1))
		{
			if (Number[i] == -1)
				++StarCount;
		}
		if (StarCount == LINECOUNT)
			++LineCount;
	}

	return LineCount;
}

int SelectAI(int Number[ARRAYCOUNT])
{
	// 완성될 줄이 가장 많은 인덱스와 별이 가장 많은 인덱스를 저장할 변수 2개 선언.
	int AICheckIndex = -1, AICheckStarIndex = -1;
	int AIPrevStarCount = -1;
	int StarCount = 0, StarCount1 = 0;

	// 선택 가능한 숫자 중 가장 많은 줄을 완성할 수 있는 숫자를 선택하는 방식
	// 아무 줄도 완성할 수 없다면 줄에 별이 가장 많은 것 선택
	for (int i = 0; i < ARRAYCOUNT; ++i)
	{
		// 별이 아닐 경우에만 체크
		if (Number[i] != -1)
		{
			int IndexX = i % LINECOUNT;
			int IndexY = i / LINECOUNT;

			StarCount = 0, StarCount1 = 0;

			for (int j = 0; j < LINECOUNT; ++j)
			{
				// AI의 가로줄 체크
				if (Number[IndexY * LINECOUNT + j] == -1)
					++StarCount;

				// AI의 세로줄 체크
				if (Number[j * LINECOUNT + IndexX] == -1)
					++StarCount1;
			}

			// 위에서 현재 인덱스에 해당하는 가로, 세로줄에 대해
			// *이 몇 개인지 저장을 해둔 상태
			// 이전에 저장해둔 *의 개수와 현재 구해준 *의 개수를 비교하여
			// *이 더 많은 줄을 구해줌
			if (AIPrevStarCount < StarCount)
			{
				AICheckStarIndex = i;
				AIPrevStarCount = StarCount;
			}
			else if (AIPrevStarCount < StarCount1)
			{
				AICheckStarIndex = i;
				AIPrevStarCount = StarCount1;
			}

			// 대각선 2줄에 대해서 체크한다.
			if (i % (LINECOUNT + 1) == 0)
			{
				StarCount = 0;

				for (int i = 0; i < ARRAYCOUNT; i += (LINECOUNT + 1))
				{
					if (Number[i] == -1)
						++StarCount;
				}

				if (AIPrevStarCount < StarCount)
				{
					AICheckStarIndex = i;
					AIPrevStarCount = StarCount;
				}
			}

			if (i % (LINECOUNT - 1) == 0 && i != 0 && i != (ARRAYCOUNT - 1))
			{
				StarCount = 0;

				for (int i = LINECOUNT - 1; i <= (LINECOUNT * (LINECOUNT - 1)); 
					i += (LINECOUNT - 1))
				{
					if (Number[i] == -1)
						++StarCount;
				}

				if (AIPrevStarCount < StarCount)
				{
					AICheckStarIndex = i;
					AIPrevStarCount = StarCount;
				}
			}
		}
	}

	return Number[AICheckStarIndex];
}
