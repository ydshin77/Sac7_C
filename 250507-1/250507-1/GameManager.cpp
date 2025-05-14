
#include "GameManager.h"
#include "Battle.h"

// �÷��̾� ���� ����
FPlayerInfo* gPlayer = nullptr;

bool GameInit()
{
	// �÷��̾� ���� ���� �Ҵ�
	gPlayer = new FPlayerInfo;

	// �÷��̾� �̸� �Է�
	printf("�̸� : ");
	// 32��¥�� �迭������, ������ null���ڴ� �����Ͽ� 31��
	scanf_s("%s", gPlayer->Name, 31);

	// �÷��̾� ���� ����
	printf("1. ���\n");
	printf("2. �ü�\n");
	printf("3. ������\n");

	printf("������ �����ϼ��� : ");
	int Input = 0;
	scanf_s("%d", &Input);

	// 1 ~ 3�� �ƴ� ��ȣ�� �Է����� ��� false ��ȯ
	if (Input <= (int)EPlayerJob::None || Input >= (int)EPlayerJob::End)
		return false;

	// 1 ~ 3�� ���ý� ������ �Է°� ����
	gPlayer->Job = (EPlayerJob)Input;

	// Editor�� �ۼ��� �÷��̾� �⺻ ���� ���� �о����
	FPlayerEditorInfo JobInfo[3] = {};

	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "PlayerInfo.pli", "rb");

	if (!FileStream)
		return false;

	fread(JobInfo, sizeof(FPlayerEditorInfo), 3, FileStream);

	fclose(FileStream);

	// �÷��̾��� �ɷ�ġ�� �⺻ ������ �ɷ�ġ ����
	gPlayer->Attack = JobInfo[Input - 1].Attack;
	gPlayer->Defense = JobInfo[Input - 1].Defense;
	gPlayer->HP = JobInfo[Input - 1].HP;
	gPlayer->HPMax = JobInfo[Input - 1].HP;
	gPlayer->MP = JobInfo[Input - 1].MP;
	gPlayer->MPMax = JobInfo[Input - 1].MP;

	// ���� �ʱ�ȭ�� ���������� false ��ȯ
	if (!BattleInit())
		return false;

	return true;
}

void GameDestroy()
{
	// ���� �Ҵ��� �÷��̾� ���� ����
	SAFE_DELETE(gPlayer);
}

void Run()
{
	// ������ ��� ����ǰԲ� �ϱ� ���� ���ѷ��� �ۼ�
	// ������ ������ ���� break�� ���ؼ� while�� ���� ������
	while (true)
	{
		system("cls");

		// �޴� ��� �� ����
		printf("1. ����\n");
		printf("2. ����\n");
		printf("3. ����\n");
		printf("4. ����\n");
		printf("�޴��� �����ϼ��� : ");
		int Input = 0;
		scanf_s("%d", &Input);
	
		// 1 ~ 4���� �Է����� ���
		// �ٸ� ���� �Է��ϸ� while�� �� ���� �ö�
		switch (Input)
		{
		case EMainMenu::Battle:
			// ��Ʋ �޴� ���
			RunMap();
			break;
		case EMainMenu::Store:
			break;
		case EMainMenu::Inventory:
			break;
		case EMainMenu::Exit:
			printf("������ �����մϴ�.");
			return;
		}

	}
}
