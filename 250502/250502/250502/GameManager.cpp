
#include "GameManager.h"
#include "Battle.h"

FPlayerInfo* gPlayer = nullptr;

bool GameInit()
{
	gPlayer = new FPlayerInfo;

	// �÷��̾� �̸��� �Է��ϰ� ������ �����Ѵ�.
	printf("�̸� : ");
	scanf_s("%s", gPlayer->Name, 31);

	printf("1. ���\n");
	printf("2. �ü�\n");
	printf("3. ������\n");
	printf("������ �����ϼ��� : ");
	int	Input = 0;
	scanf_s("%d", &Input);

	if (Input <= (int)EPlayerJob::None ||
		Input >= (int)EPlayerJob::End)
		return false;

	gPlayer->Job = (EPlayerJob)Input;

	// ������ ���� �÷��̾� �⺻ ������ �����Ѵ�.
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
		printf("1. ����\n");
		printf("2. ����\n");
		printf("3. ����\n");
		printf("4. ����\n");
		printf("�޴��� �����ϼ��� : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		// �߸��� ���� �Է����� ���
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
