// 이 헤더파일이 여러 곳에서 include가 되더라도 1번만 처리되도록
// 컴파일러에게 알려주는 역할을 한다.
#pragma once

#include <iostream>

//#define	AA		10
#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }


//static int	gNumber = 12;

enum class EPlayerJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

struct FPlayerInfo
{
	char	Name[32] = {};
	EPlayerJob	Job = EPlayerJob::None;
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		HPMax = 0;
	int		MP = 0;
	int		MPMax = 0;
	int		Level = 1;
	int		Exp = 0;
	int		Gold = 10000;
};

struct FMonsterInfo
{
	char	Name[32] = {};
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		HPMax = 0;
	int		MP = 0;
	int		MPMax = 0;
	int		Level = 1;

	// 아래 정보는 플레이어가 몬스터를 잡았을 때 획득할 수 있는 경험치와
	// 돈이다.
	int		Exp = 0;
	int		Gold = 0;
};


// 이 전역변수는 cpp마다 따로 생성이 된다.
static int	gNumber = 100;

// extern은 이미 만들어져있는 전역변수를 이 헤더파일을 include 하면
// 다른 곳에서 공유해서 사용할 수 있게 해주는 기능이다.
extern FPlayerInfo* gPlayer;

struct FPlayerEditorInfo
{
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		MP = 0;
};
