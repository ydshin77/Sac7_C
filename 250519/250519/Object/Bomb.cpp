#include "Bomb.h"
#include "../Maze/Maze.h"
#include "../Scene/Scene.h"
#include "Player.h"

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

			// ��
			Pos.Y -= i;
			if (Pos.Y >= 0)
			{
				Type = Maze->GetTileType(Pos);

				if (Type == ETileType::Wall)
				{
					Maze->SetTileType(ETileType::Road, Pos);
				}
			}

			// �Ʒ�
			Pos = mPos;
			Pos.Y += i;
			if (Pos.Y < TileCountY)
			{
				Type = Maze->GetTileType(Pos);

				if (Type == ETileType::Wall)
				{
					Maze->SetTileType(ETileType::Road, Pos);
				}
			}

			// ����
			Pos = mPos;
			Pos.X -= i;
			if (Pos.X >= 0)
			{
				Type = Maze->GetTileType(Pos);

				if (Type == ETileType::Wall)
				{
					Maze->SetTileType(ETileType::Road, Pos);
				}
			}

			// ������
			Pos = mPos;
			Pos.X += i;
			if (Pos.X < TileCountX)
			{
				Type = Maze->GetTileType(Pos);

				if (Type == ETileType::Wall)
				{
					Maze->SetTileType(ETileType::Road, Pos);
				}
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
