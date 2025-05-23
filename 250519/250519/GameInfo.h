#pragma once

#include <iostream>
#include <vector>
#include <list>
// unordered_map�� hash map �̴�.
#include <unordered_map>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }

enum class ETileType : char
{
	Road = '0',
	Wall = '1',
	Start = '2',
	Exit = '3',
	Bomb = '4',
	Trap = '5'
};

enum class EItemType : unsigned char
{
	BombPower,
	BombCount,
	MoveSpeed,
	End
};

static void MoveCursor(int x, int y)
{
	COORD	Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
