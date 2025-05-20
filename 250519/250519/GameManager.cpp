#include "GameManager.h"
#include "Maze/MazeManager.h"
#include "Scene/SceneManager.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CSceneManager::DestroyInst();

	CMazeManager::DestroyInst();
}

bool CGameManager::Init()
{
	if (!CMazeManager::GetInst()->Init())
		return false;

	if (!CSceneManager::GetInst()->Init())
		return false;

	return true;
}

void CGameManager::RunGame(int MazeIndex)
{
}

void CGameManager::Run()
{
	while (mLoop)
	{
		CSceneManager::GetInst()->Run();
	}
	/*while (true)
	{
		int Input = CMazeManager::GetInst()->OutputMenu();

		int	MazeCount = CMazeManager::GetInst()->GetMazeCount();

		if (Input == MazeCount + 1)
			return;

		else if (Input == 0)
			continue;

		int	TileOutputCount = CMazeManager::GetInst()->GetTileOutputCount(Input - 1);

		int	CountY = CMazeManager::GetInst()->GetCountY(Input - 1);

		mOutputBuffer = new char[TileOutputCount + 1];

		mOutputBuffer[TileOutputCount] = 0;

		system("cls");

		RunGame(Input - 1);

		delete[] mOutputBuffer;
	}*/
}

CGameManager* CGameManager::GetInst()
{
	if (!mInst)
		mInst = new CGameManager;

	return mInst;
}

void CGameManager::DestroyInst()
{
	SAFE_DELETE(mInst);
}
