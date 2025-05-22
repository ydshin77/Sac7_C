#include "Stage.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init(int StageNumber)
{
    mStageNumber = StageNumber;

    char    FileName[64] = {};

    sprintf_s(FileName, "Stage%d.txt", mStageNumber);

    FILE* File = nullptr;

    fopen_s(&File, FileName, "rt");

    if (!File)
        return false;

    char    Line[10] = {};

    mBlockList.reserve(STAGE_WIDTH * STAGE_HEIGHT);

    for (int i = 0; i < STAGE_HEIGHT; ++i)
    {
        fgets(Line, 10, File);

        for (int j = 0; j < 9; ++j)
        {
            mBlockList.push_back((EBlockType)Line[j]);

            switch ((EBlockType)Line[j])
            {
            case EBlockType::Empty:
                mBlockOutputList.push_back(' ');
                break;
            case EBlockType::Block:
                mBlockOutputList.push_back('*');
                break;
            }
        }
    }


    fclose(File);


    return true;
}

void CStage::Output(char* Buffer)
{
}
