#include "SceneGame.h"
#include "../Stage/Stage.h"

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
    CStage* Stage = new CStage;

    if (!Stage->Init(mStageNumber))
    {
        SAFE_DELETE(Stage);
        return false;
    }

    mStage = Stage;

    return true;
}

void CSceneGame::Run()
{
    CScene::Run();
}
