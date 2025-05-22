#include "ItemMoveSpeed.h"
#include "../Maze/Maze.h"
#include "../Scene/Scene.h"
#include "Player.h"

CItemMoveSpeed::CItemMoveSpeed()
{
	mItemType = EItemType::MoveSpeed;
}

CItemMoveSpeed::~CItemMoveSpeed()
{
}

bool CItemMoveSpeed::Init()
{
    return true;
}

void CItemMoveSpeed::Update(float DeltaTime)
{
	CItem::Update(DeltaTime);
}

void CItemMoveSpeed::Output(char* Buffer)
{
	int	CountX = mScene->GetMaze()->GetCountX() + 1;

	Buffer[mPos.Y * CountX + mPos.X] = 'S';
}

void CItemMoveSpeed::ItemGain()
{
	mPlayer-> MoveSpeedUp();
}
