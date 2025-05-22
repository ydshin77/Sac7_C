#include "ItemCount.h"
#include "../Maze/Maze.h"
#include "../Scene/Scene.h"
#include "Player.h"

CItemCount::CItemCount()
{
	mItemType = EItemType::BombCount;
}

CItemCount::~CItemCount()
{
}

bool CItemCount::Init()
{
	return true;
}

void CItemCount::Update(float DeltaTime)
{
	CItem::Update(DeltaTime);
}

void CItemCount::Output(char* Buffer)
{
	int	CountX = mScene->GetMaze()->GetCountX() + 1;

	Buffer[mPos.Y * CountX + mPos.X] = 'C';
}

void CItemCount::ItemGain()
{
	mPlayer->CountUp();
}
