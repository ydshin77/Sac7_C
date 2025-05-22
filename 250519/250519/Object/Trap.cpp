#include "Trap.h"
#include "../Maze/Maze.h"
#include "Player.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneMazeMenu.h"

CTrap::CTrap()
{
}

CTrap::~CTrap()
{
}

bool CTrap::Init()
{
    return true;
}

void CTrap::Update(float DeltaTime)
{
    COORD   PlayerPos = mPlayer->GetPos();

    if (PlayerPos.X == mPos.X &&
        PlayerPos.Y == mPos.Y)
    {
        CSceneManager::GetInst()->CreateNextScene<CSceneMazeMenu>();
    }
}

void CTrap::Output(char* Buffer)
{
	int	CountX = mScene->GetMaze()->GetCountX() + 1;

	Buffer[mPos.Y * CountX + mPos.X] = '+';
}
