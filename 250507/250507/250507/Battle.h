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

bool BattleInit();
void BattleDestroy();
void RunMap();

