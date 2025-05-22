#include "Player.h"
#include "../Maze/Maze.h"
#include "../Scene/SceneMazeMenu.h"
#include "../Scene/SceneManager.h"
#include "Bomb.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	return true;
}

void CPlayer::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		mPosX -= mMoveSpeed * DeltaTime;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		mPosX += mMoveSpeed * DeltaTime;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		mPosY -= mMoveSpeed * DeltaTime;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		mPosY += mMoveSpeed * DeltaTime;
	}

	if (abs((int)mPosX) >= 1)
	{
		mPos.X += (int)mPosX;

		int	CountX = mScene->GetMaze()->GetCountX();

		if (mPos.X < 0)
			mPos.X = 0;

		else if (mPos.X >= CountX)
			mPos.X = CountX - 1;

		// 벽인지 체크한다.
		ETileType	Tile = mScene->GetMaze()->GetTileType(mPos);

		if (Tile == ETileType::Wall)
		{
			mPos.X -= (int)mPosX;
			mPosX = 0.f;
		}

		else
			mPosX -= (int)mPosX;
	}

	if (abs((int)mPosY) >= 1)
	{
		mPos.Y += (int)mPosY;

		int	CountY = mScene->GetMaze()->GetCountY();

		if (mPos.Y < 0)
			mPos.Y = 0;

		else if (mPos.Y >= CountY)
			mPos.Y = CountY - 1;

		// 벽인지 체크한다.
		ETileType	Tile = mScene->GetMaze()->GetTileType(mPos);

		if (Tile == ETileType::Wall)
		{
			mPos.Y -= (int)mPosY;
			mPosY = 0.f;
		}

		else
			mPosY -= (int)mPosY;;
	}

	ETileType	Tile = mScene->GetMaze()->GetTileType(mPos);

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		// 현재 위치가 폭탄이 아닐 경우 설치한다.
		if (Tile == ETileType::Road && mBombCount < mBombCountMax)
		{
			CBomb* Bomb = mScene->CreateObj<CBomb>(mPos.X, mPos.Y);

			Bomb->SetPlayer(this);
			Bomb->SetPower(mBombPower);

			++mBombCount;

			mScene->GetMaze()->SetTileType(ETileType::Bomb,
				mPos);
		}
	}



	if (Tile == ETileType::Exit)
	{
		CSceneManager::GetInst()->CreateNextScene<CSceneMazeMenu>();
	}
}

void CPlayer::Output(char* Buffer)
{
	int	CountX = mScene->GetMaze()->GetCountX() + 1;
	
	Buffer[mPos.Y * CountX + mPos.X] = '$';
}
