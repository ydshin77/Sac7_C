
#include "Battle.h"

bool BattleInit()
{
	return true;
}

void RunMap()
{
	while (true)
	{
		// 전투 메뉴를 보여주고 선택한다.
		system("cls");
		printf("1. 쉬움\n");
		printf("2. 보통\n");
		printf("3. 어려움\n");
		printf("4. 뒤로가기\n");
		printf("메뉴를 선택하세요 : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		switch (Input)
		{
		case EMapMenu::Easy:
			break;
		case EMapMenu::Normal:
			break;
		case EMapMenu::Hard:
			break;
		case EMapMenu::Back:
			return;
		}
	}
}
