#pragma once

#include "GameInfo.h"

namespace EMapMenu
{
	enum Type
	{
		None,
		Easy,
		Normal,
		Hard,
		Back,
		End
	};
}

// 전체 전투를 초기화하는 함수
bool BattleInit();

// 전체 전투를 진행해주는 함수
void RunMap();