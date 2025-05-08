#pragma once

#include "GameInfo.h"

namespace EMainMenu
{
	enum Type
	{
		None,
		Battle,
		Store,
		Inventory,
		Exit,
		End
	};
}

// 전체 게임을 초기화하는 함수.
bool GameInit();

// 게임이 종료될 때 호출되는 함수.
void GameDestroy();

// 전체 게임을 진행해주는 함수.
void Run();

