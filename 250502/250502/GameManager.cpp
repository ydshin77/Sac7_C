
#include "GameManager.h"
#include "Battle.h"

FPlayerInfo* gPlayer = nullptr;

bool GameInit()
{
	gPlayer = new FPlayerInfo;

	// 플레이어 이름을 입력하고 직업을 선택한다.
	printf("이름 : ");
	scanf_s("%s", gPlayer->Name, 31);

	printf("1. 기사\n");
	printf("2. 궁수\n");
	printf("3. 마법사\n");
	printf("직업을 선택하세요 : ");
	int	Input = 0;
	scanf_s("%d", &Input);

	if (Input <= (int)EPlayerJob::None ||
		Input >= (int)EPlayerJob::End)
		return false;

	gPlayer->Job = (EPlayerJob)Input;

	// 직업에 따라 플레이어 기본 정보를 설정한다.
	FPlayerEditorInfo	JobInfo[3] = {};

	FILE* File = nullptr;

	fopen_s(&File, "PlayerInfo.pli", "rb");

	if (!File)
		return false;

	fread(JobInfo, sizeof(FPlayerEditorInfo), 3, File);

	fclose(File);

	gPlayer->Attack = JobInfo[Input - 1].Attack;
	gPlayer->Defense = JobInfo[Input - 1].Defense;
	gPlayer->HP = JobInfo[Input - 1].HP;
	gPlayer->HPMax = gPlayer->HP;
	gPlayer->MP = JobInfo[Input - 1].MP;
	gPlayer->MPMax = gPlayer->MP;

	if (!BattleInit())
		return false;

	return true;
}

void GameDestroy()
{
	SAFE_DELETE(gPlayer);
}

void Run()
{
	while (true)
	{
		system("cls");
		printf("1. 전투\n");
		printf("2. 상점\n");
		printf("3. 가방\n");
		printf("4. 종료\n");
		printf("메뉴를 선택하세요 : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		// 잘못된 값을 입력했을 경우
		/*if (Input <= EMainMenu::None || Input >= EMainMenu::End)
			continue;

		else if (Input == EMainMenu::Exit)
			break;*/

		switch (Input)
		{
		case EMainMenu::Battle:
			RunMap();
			break;
		case EMainMenu::Store:
			break;
		case EMainMenu::Inventory:
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}
