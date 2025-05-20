#include "Scene.h"
#include "../Maze/Maze.h"
#include "../Object/GameObject.h"

CScene::CScene()
{
    // 1초당 고해상도 타이머가 흘러야 하는 값
    QueryPerformanceFrequency(&mSecond);
    // 현재 고해상도 타이머의 값
    QueryPerformanceCounter(&mTime);
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
    Update();

    Output();
}

void CScene::Update()
{
    LARGE_INTEGER   Time;
    QueryPerformanceCounter(&Time);

    // DeltaTime = (현재값 - 이전값) / 초당값
    mDeltaTime = (Time.QuadPart - mTime.QuadPart) /
        (float)mSecond.QuadPart;

    mTime = Time;


    std::list<CGameObject*>::iterator   iter;
    std::list<CGameObject*>::iterator   iterEnd = mObjList.end();

    for (iter = mObjList.begin(); iter != iterEnd; ++iter)
    {
        (*iter)->Update(mDeltaTime);

        if (!(*iter)->GetActive())
        {
            SAFE_DELETE((*iter));
            iter = mObjList.erase(iter);
            iterEnd = mObjList.end();
            --iter;
        }
    }
}

void CScene::Output()
{
    // 매번 출력을 시작 위치로 지정하여 출력한다.
    MoveCursor(0, 0);

    if (mMaze)
    {
        mMaze->Output(mOutputBuffer);
    }

    std::list<CGameObject*>::iterator   iter;
    std::list<CGameObject*>::iterator   iterEnd = mObjList.end();

    for (iter = mObjList.begin(); iter != iterEnd; ++iter)
    {
        (*iter)->Output(mOutputBuffer);
    }


    printf("%s", mOutputBuffer);
}
