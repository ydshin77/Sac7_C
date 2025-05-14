#pragma once

#include "GameInfo.h"

// �޴� ���� (�Է°��̶� ���� �Ŵϱ� namespace�� ����)
// enum class�� ����ϸ� ������ �� �Ұ�
// enum�� ����ϸ� �ٸ� ������ ���̹� �浹
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

// ��ü ������ �ʱ�ȭ�ϴ� �Լ�
bool GameInit();

// ������ ����� �� ȣ��Ǵ� �Լ�
void GameDestroy();

// ��ü ������ �������ִ� �Լ�
void Run();