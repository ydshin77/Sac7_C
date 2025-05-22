#include "SceneGame.h"
#include "../Object/Player.h"
#include "../Maze/Maze.h"
#include "../Object/Trap.h"

CSceneGame::CSceneGame()
{
}

CSceneGame::~CSceneGame()
{
}

CTrap* CSceneGame::FindTrap(int Index)
{
    std::unordered_map<int, CTrap*>::iterator iter =
        mTrapMap.find(Index);

    // find�� �̿��Ͽ� ã���� iterator�� end�� ���� �ش� Ű��
    // ���ٴ� �ǹ��̴�.
    if (iter == mTrapMap.end())
        return nullptr;

    // iter->first : Ű��
    // iter->second : value��
    return iter->second;
}

void CSceneGame::EraseTrap(int Index)
{
    mTrapMap.erase(Index);
}

void CSceneGame::SetMaze(CMaze* Maze)
{
    CScene::SetMaze(Maze);

    mStartPos = mMaze->GetStartPos();
    mExitPos = mMaze->GetExitPos();

    mPlayer->SetPos(mStartPos);

    // Trap�� �����Ѵ�.
    int TrapCount = mMaze->GetTrapCount();

    for (int i = 0; i < TrapCount; ++i)
    {
        COORD   Pos = mMaze->GetTrapPos(i);

        CTrap* Trap = CreateObj<CTrap>(Pos.X, Pos.Y);

        Trap->SetPlayer(mPlayer);

        int CountX = mMaze->GetCountX();

        int Index = Pos.Y * CountX + Pos.X;

        mTrapMap.insert(std::make_pair(Index, Trap));
    }
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

    MoveCursor(23, 2);

    printf("Score : %d", mScore);
}
