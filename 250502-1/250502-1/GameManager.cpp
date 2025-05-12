
#include "GameManager.h"
#include "Battle.h"

// 플레이어 정보 생성
FPlayerInfo* gPlayer = nullptr;

bool GameInit()
{
	// 플레이어 정보 동적 할당
	gPlayer = new FPlayerInfo;

	// 플레이어 이름 입력 및 직업 선택 24.50
	printf("이름 : ");
	scanf_s("%s", gPlayer->Name);
	
	// 전투 초기화에 실패했으면 게임 초기화 실패
	if (!BattleInit)
		return false;

	return true;
}

void GameDestroy()
{
	// 동적 할당한 플레이어 정보 제거
	SAFE_DELETE(gPlayer);
}

void Run()
{
	// 게임이 계속 실행되게끔 하기 위해 무한루프 작성
	// 게임을 종료할 때는 break를 통해서 while문 빠져 나오기
	while (true)
	{
		system("cls");

		// 메뉴 출력 및 선택
		printf("1. 전투\n");
		printf("2. 상점\n");
		printf("3. 가방\n");
		printf("4. 종료\n");
		printf("메뉴를 선택하세요 : ");
		int Input = 0;
		scanf_s("%d", &Input);
	
		// 1 ~ 4번을 입력했을 경우
		// 다른 값을 입력하면 while문 맨 위로 올라감
		switch (Input)
		{
		case EMainMenu::Battle:
			// 배틀 메뉴 출력
			RunMap();
			break;
		case EMainMenu::Store:
			break;
		case EMainMenu::Inventory:
			break;
		case EMainMenu::Exit:
			printf("게임을 종료합니다.");
			return;
		}

	}
}
