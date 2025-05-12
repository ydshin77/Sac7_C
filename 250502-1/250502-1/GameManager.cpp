
#include "GameManager.h"
#include "Battle.h"

// �÷��̾� ���� ����
FPlayerInfo* gPlayer = nullptr;

bool GameInit()
{
	// �÷��̾� ���� ���� �Ҵ�
	gPlayer = new FPlayerInfo;

	// �÷��̾� �̸� �Է� �� ���� ���� 24.50
	printf("�̸� : ");
	scanf_s("%s", gPlayer->Name);
	
	// ���� �ʱ�ȭ�� ���������� ���� �ʱ�ȭ ����
	if (!BattleInit)
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
