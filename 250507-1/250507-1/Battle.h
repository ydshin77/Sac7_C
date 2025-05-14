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
		End,
		MapCount = End - 2
	};
}

// 전체 전투를 초기화하는 함수
bool BattleInit();

// 배틀 메뉴를 띄워주는 함수
void RunMap();