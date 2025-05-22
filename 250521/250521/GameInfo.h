#pragma once

#include <iostream>
#include <vector>
#include <list>
// unordered_map¿∫ hash map ¿Ã¥Ÿ.
#include <unordered_map>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }

#define	STAGE_WIDTH		9
#define	STAGE_HEIGHT	12

enum class EBlockType : char
{
	Empty = '0',
	Block = '1'
};

static void MoveCursor(int x, int y)
{
	COORD	Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
