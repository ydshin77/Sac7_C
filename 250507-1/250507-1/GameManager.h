#pragma once

#include "GameInfo.h"

// 메뉴 생성 (입력값이랑 비교할 거니까 namespace로 생성)
// enum class를 사용하면 정수와 비교 불가
// enum을 사용하면 다른 변수와 네이밍 충돌
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

// 전체 게임을 초기화하는 함수
bool GameInit();

// 게임이 종료될 때 호출되는 함수
void GameDestroy();

// 전체 게임을 진행해주는 함수
void Run();