#include "Bomb.h"
#include "../Maze/Maze.h"
#include "../Scene/SceneGame.h"
#include "Player.h"
#include "ItemPower.h"
#include "ItemCount.h"
#include "ItemMoveSpeed.h"
#include "Trap.h"

CBomb::CBomb()
{
}

CBomb::~CBomb()
{
}

bool CBomb::Init()
{
    return true;
}

void CBomb::Update(float DeltaTime)
{
	mFireTime -= DeltaTime;

	if (mFireTime <= 0.f)
	{
		CMaze* Maze = mScene->GetMaze();

		int	TileCountX = Maze->GetCountX();
		int	TileCountY = Maze->GetCountY();

		for (int i = 1; i <= mPower; ++i)
		{
			COORD	Pos = mPos;
			ETileType	Type;

			// 위
			Pos.Y -= i;
			if (Pos.Y >= 0)
			{
				BreakWall(Pos);
			}

			// 아래
			Pos = mPos;
			Pos.Y += i;
			if (Pos.Y < TileCountY)
			{
				BreakWall(Pos);
			}

			// 왼쪽
			Pos = mPos;
			Pos.X -= i;
			if (Pos.X >= 0)
			{
				BreakWall(Pos);
			}

			// 오른쪽
			Pos = mPos;
			Pos.X += i;
			if (Pos.X < TileCountX)
			{
				BreakWall(Pos);
			}
		}

		mScene->GetMaze()->SetTileType(ETileType::Road,
			mPos);

		mPlayer->RestoreBombCount();
		Destroy();
	}
}

void CBomb::Output(char* Buffer)
{
	int	CountX = mScene->GetMaze()->GetCountX() + 1;

	Buffer[mPos.Y * CountX + mPos.X] = '%';
}

void CBomb::BreakWall(const COORD& Pos)
{
	CMaze* Maze = mScene->GetMaze();

	ETileType Type = Maze->GetTileType(Pos);

	if (Type == ETileType::Wall)
	{
		Maze->SetTileType(ETileType::Road, Pos);

		// 아이템이 나올 확률을 구한다.
		float	Percent = rand() % 10001 / 100.f;

		if (Percent <= 50.f)
		{
			EItemType	DropItemType =
				(EItemType)(rand() % (int)EItemType::End);

			CItem* Item = nullptr;

			switch (DropItemType)
			{
			case EItemType::BombPower:
				Item = mScene->CreateObj<CItemPower>(Pos.X, Pos.Y);
				break;
			case EItemType::BombCount:
				Item = mScene->CreateObj<CItemCount>(Pos.X, Pos.Y);
				break;
			case EItemType::MoveSpeed:
				Item = mScene->CreateObj<CItemMoveSpeed>(Pos.X, Pos.Y);
				break;
			}

			Item->SetPlayer(mPlayer);
		}
	}

	CSceneGame* Scene = dynamic_cast<CSceneGame*>(mScene);

	if (Scene)
	{
		int	CountX = Maze->GetCountX();

		int	Index = Pos.Y * CountX + Pos.X;

		CTrap* Trap = Scene->FindTrap(Index);

		if (Trap)
		{
			Maze->SetTileType(ETileType::Road, Pos);
			Scene->EraseTrap(Index);
			Trap->Destroy();
		}
	}
}
