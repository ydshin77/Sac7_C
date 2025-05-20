#include "SceneGame.h"
#include "../Object/Player.h"
#include "../Maze/Maze.h"

CSceneGame::CSceneGame()
{
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::SetMaze(CMaze* Maze)
{
    CScene::SetMaze(Maze);

    mStartPos = mMaze->GetStartPos();
    mExitPos = mMaze->GetExitPos();

    mPlayer->SetPos(mStartPos);
}

bool CSceneGame::Init()
{
    // 플레이어 생성
    mPlayer = CreateObj<CPlayer>(0, 0);


    return true;
}

void CSceneGame::Run()
{
    // 부모 클래스의 Run함수를 호출한다.
    CScene::Run();
}
