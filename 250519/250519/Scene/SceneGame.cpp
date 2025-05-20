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
    // �÷��̾� ����
    mPlayer = CreateObj<CPlayer>(0, 0);


    return true;
}

void CSceneGame::Run()
{
    // �θ� Ŭ������ Run�Լ��� ȣ���Ѵ�.
    CScene::Run();
}
