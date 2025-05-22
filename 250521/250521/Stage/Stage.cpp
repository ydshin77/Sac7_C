#include "Stage.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

EBlockType CStage::GetBlock(const COORD& Pos)
{
    return GetBlock(Pos.X, Pos.Y);
}

EBlockType CStage::GetBlock(int x, int y)
{
    if (y >= STAGE_HEIGHT)
        return EBlockType::Block;

    else if (y < 0)
        return EBlockType::Empty;

    return mBlockList[y * STAGE_WIDTH + x];
}

void CStage::SetBlock(EBlockType Type, const COORD& Pos)
{
    SetBlock(Type, Pos.X, Pos.Y);
}

void CStage::SetBlock(EBlockType Type, int x, int y)
{
    if (y < 0)
        return;

    mBlockList[y * STAGE_WIDTH + x] = Type;

    switch (Type)
    {
    case EBlockType::Empty:
        mBlockOutputList[y * (STAGE_WIDTH + 3) + (x + 1)] = ' ';
        break;
    case EBlockType::Block:
        mBlockOutputList[y * (STAGE_WIDTH + 3) + (x + 1)] = '*';
        break;
    }
}

void CStage::LineDrop(int y)
{
    memcpy(&mBlockList[y * STAGE_WIDTH],
        &mBlockList[(y - 1) * STAGE_WIDTH],
        sizeof(EBlockType) * STAGE_WIDTH);

    memcpy(&mBlockOutputList[y * (STAGE_WIDTH + 3) + 1],
        &mBlockOutputList[(y - 1) * (STAGE_WIDTH + 3) + 1],
        STAGE_WIDTH + 3);
}

void CStage::ClearLine(int y)
{
    for (int i = 0; i < STAGE_WIDTH; ++i)
    {
        mBlockList[y * STAGE_WIDTH + i] = EBlockType::Empty;
        mBlockOutputList[y * (STAGE_WIDTH + 3) + (i + 1)] = ' ';
    }
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

    char    Line[11] = {};

    mBlockList.reserve(STAGE_WIDTH * STAGE_HEIGHT);

    for (int i = 0; i < STAGE_HEIGHT; ++i)
    {
        fgets(Line, 11, File);

        mBlockOutputList.push_back('*');

        for (int j = 0; j < STAGE_WIDTH; ++j)
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

        mBlockOutputList.push_back('*');
        mBlockOutputList.push_back('\n');
    }

    for (int i = 0; i < STAGE_WIDTH + 2; ++i)
    {
        mBlockOutputList.push_back('*');
    }


    fclose(File);


    return true;
}

void CStage::Output(char* Buffer)
{
    size_t Count = mBlockOutputList.size();

    memcpy(Buffer, &mBlockOutputList[0], Count);
}
