#include "Scene.h"
#include "../Stage/Stage.h"
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
    SAFE_DELETE(mStage);
    SAFE_DELETE_ARRAY(mOutputBuffer);
}

bool CScene::Init()
{
    return true;
}

bool CScene::Begin()
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

    for (iter = mObjList.begin(); iter != iterEnd;)
    {
        (*iter)->Update(mDeltaTime);

        if (!(*iter)->GetActive())
        {
            SAFE_DELETE((*iter));
            iter = mObjList.erase(iter);
            iterEnd = mObjList.end();
            BlockDestroy();
            continue;
        }

        ++iter;
    }
}

void CScene::Output()
{
    MoveCursor(0, 1);

    if (mStage)
        mStage->Output(mOutputBuffer);

    std::list<CGameObject*>::iterator   iter;
    std::list<CGameObject*>::iterator   iterEnd = mObjList.end();

    for (iter = mObjList.begin(); iter != iterEnd; ++iter)
    {
        (*iter)->Output(mOutputBuffer);
    }



    printf("%s", mOutputBuffer);
}

void CScene::BlockDestroy()
{
}
