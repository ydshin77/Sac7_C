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

		// 전투 메뉴
		printf("1. 공격\n");
		printf("2. 도망가기\n");
		printf("메뉴를 선택하세요 : ");
		int	Input;
		scanf_s("%d", &Input);
	}
}
