#include "Battle.h"

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
}

bool CBattle::Init(EMapMenu Map)
{
	return true;
}

void CBattle::Run()
{
	while (true)
	{
		system("cls");
		printf("================ Player ================\n");
		//OutputPlayerBattle();

		printf("================ Monster ================\n");
		//OutputMonsterBattle(Monster);

		// ���� �޴�
		printf("1. ����\n");
		printf("2. ��������\n");
		printf("�޴��� �����ϼ��� : ");
		int	Input;
		scanf_s("%d", &Input);
	}
}
