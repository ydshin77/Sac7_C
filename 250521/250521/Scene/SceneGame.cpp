#include "SceneGame.h"
#include "../Stage/Stage.h"
#include "../Object/Block1.h"
#include "../Object/Block2.h"
#include "../Object/Block3.h"
#include "../Object/Block4.h"
#include "../Object/Block5.h"
#include "../Object/Block6.h"
#include "../Object/Block7.h"

CSceneGame::CSceneGame()
{
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::SetStageNumber(int StageNumber)
{
    mStageNumber = StageNumber;
}

bool CSceneGame::Init()
{
    return true;
}

bool CSceneGame::Begin()
{
    mStage = new CStage;

    if (!mStage->Init(mStageNumber))
    {
        SAFE_DELETE(mStage);
        return false;
    }

    int Width = STAGE_WIDTH + 3;
    int Height = STAGE_HEIGHT + 1;

    mOutputBuffer = new char[Width * Height];

    memset(mOutputBuffer, 0, Width * Height);

    BlockDestroy();

    return true;
}

void CSceneGame::Run()
{
    CScene::Run();
}

void CSceneGame::BlockDestroy()
{
    int BlockNumber = rand() % 7 + 1;

    switch (BlockNumber)
    {
    case 1:
        mCurrentBlock = CreateObj<CBlock1>(0, 0);
        break;
    case 2:
        mCurrentBlock = CreateObj<CBlock2>(0, 0);
        break;
    case 3:
        mCurrentBlock = CreateObj<CBlock3>(0, 0);
        break;
    case 4:
        mCurrentBlock = CreateObj<CBlock4>(0, 0);
        break;
    case 5:
        mCurrentBlock = CreateObj<CBlock5>(0, 0);
        break;
    case 6:
        mCurrentBlock = CreateObj<CBlock6>(0, 0);
        break;
    case 7:
        mCurrentBlock = CreateObj<CBlock7>(0, 0);
        break;
    }
}
