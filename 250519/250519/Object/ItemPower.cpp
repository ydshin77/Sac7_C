#include "ItemPower.h"
#include "../Maze/Maze.h"
#include "../Scene/Scene.h"
#include "Player.h"

CItemPower::CItemPower()
{
	mItemType = EItemType::BombPower;
}

CItemPower::~CItemPower()
{
}

bool CItemPower::Init()
{
    return true;
}

void CItemPower::Update(float DeltaTime)
{
	CItem::Update(DeltaTime);
}

void CItemPower::Output(char* Buffer)
{
	int	CountX = mScene->GetMaze()->GetCountX() + 1;

	Buffer[mPos.Y * CountX + mPos.X] = 'P';
}

void CItemPower::ItemGain()
{
	mPlayer->PowerUp();
}
