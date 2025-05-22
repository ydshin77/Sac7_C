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

    // find를 이용하여 찾아준 iterator가 end일 경우는 해당 키가
    // 없다는 의미이다.
    if (iter == mTrapMap.end())
        return nullptr;

    // iter->first : 키값
    // iter->second : value값
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

    // Trap을 생성한다.
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
    // 플레이어 생성
    mPlayer = CreateObj<CPlayer>(0, 0);



    return true;
}

void CSceneGame::Run()
{
    // 부모 클래스의 Run함수를 호출한다.
    CScene::Run();

    MoveCursor(23, 2);

    printf("Score : %d", mScore);
}
