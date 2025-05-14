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

// ��ü ������ �ʱ�ȭ�ϴ� �Լ�
bool BattleInit();

// ��Ʋ �޴��� ����ִ� �Լ�
void RunMap();