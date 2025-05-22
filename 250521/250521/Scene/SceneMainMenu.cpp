#include "SceneMainMenu.h"
#include "../GameManager.h"
#include "SceneManager.h"
#include "SceneGame.h"

namespace EMainMenu
{
	enum Type
	{
		None,
		Start,
		Exit,
		End
	};
}

CSceneMainMenu::CSceneMainMenu()
{
}

CSceneMainMenu::~CSceneMainMenu()
{
}

void CSceneMainMenu::Run()
{
	system("cls");
	printf("1. 게임시작\n");
	printf("2. 종료\n");
	printf("메뉴를 선택하세요 : ");
	int	Input;
	scanf_s("%d", &Input);

	switch (Input)
	{
	case EMainMenu::Start:
	{
		CSceneGame* NextScene = CSceneManager::GetInst()->CreateNextScene<CSceneGame>();

		NextScene->SetStageNumber(1);
	}
		break;
	case EMainMenu::Exit:
		CGameManager::GetInst()->Exit();
		break;
	}
}
