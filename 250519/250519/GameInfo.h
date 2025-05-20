#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <Windows.h>
#include <conio.h>

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }

enum class ETileType : char
{
	Road = '0',
	Wall = '1',
	Start = '2',
	Exit = '3',
	Bomb = '4'
};

static void MoveCursor(int x, int y)
{
	COORD	Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
