#include "Scene.h"
#include "../Maze/Maze.h"
#include "../Object/GameObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
    std::list<CGameObject*>::iterator   iter;
    std::list<CGameObject*>::iterator   iterEnd = mObjList.end();

    for (iter = mObjList.begin(); iter != iterEnd; ++iter)
    {
        SAFE_DELETE((*iter));
    }

    SAFE_DELETE(mMaze);

    if (mOutputBuffer)
    {
        delete[] mOutputBuffer;
    }
}

void CScene::SetMaze(CMaze* Maze)
{
    mMaze = Maze;

    int MazeOutputCount = mMaze->GetOutputCount();

    mOutputBuffer = new char[MazeOutputCount + 1];

    mOutputBuffer[MazeOutputCount] = 0;
}

bool CScene::Init()
{
    return true;
}

void CScene::Run()
{
    // �Ź� ����� ���� ��ġ�� �����Ͽ� ����Ѵ�.
    MoveCursor(0, 0);

    if (mMaze)
    {
        mMaze->Output(mOutputBuffer);
    }



    printf("%s", mOutputBuffer);
}
