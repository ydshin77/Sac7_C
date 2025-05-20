#include "SceneMazeMenu.h"
#include "../Maze/MazeManager.h"
#include "../Maze/Maze.h"
#include "../GameManager.h"
#include "SceneGame.h"
#include "SceneManager.h"

CSceneMazeMenu::CSceneMazeMenu()
{
}

CSceneMazeMenu::~CSceneMazeMenu()
{
}

bool CSceneMazeMenu::Init()
{
    return true;
}

void CSceneMazeMenu::Run()
{
    int Input = CMazeManager::GetInst()->OutputMenu();

	int	MazeCount = CMazeManager::GetInst()->GetMazeCount();

	if (Input == MazeCount + 1)
	{
		CGameManager::GetInst()->Exit();
		return;
	}

	else if (Input == 0)
		return;

	CSceneGame* NextScene = 
		CSceneManager::GetInst()->CreateNextScene<CSceneGame>();

	CMaze* Maze = CMazeManager::GetInst()->CloneMaze(Input - 1);

	NextScene->SetMaze(Maze);
}
