#pragma once

#include <iostream>
#include <assert.h>
#include <time.h>

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }

enum class EMapMenu : unsigned char
{
	None,
	Easy,
	Normal,
	Hard,
	Back,
	End,
};
