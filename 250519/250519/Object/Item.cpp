#include "Item.h"
#include "Player.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

bool CItem::Init()
{
    return true;
}

void CItem::Update(float DeltaTime)
{
    COORD   PlayerPos = mPlayer->GetPos();

    if (PlayerPos.X == mPos.X &&
        PlayerPos.Y == mPos.Y)
    {
        ItemGain();
        Destroy();
    }
}

void CItem::Output(char* Buffer)
{
}
