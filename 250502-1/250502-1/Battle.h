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

// ��ü ������ �ʱ�ȭ�ϴ� �Լ�
bool BattleInit();

// ��ü ������ �������ִ� �Լ�
void RunMap();