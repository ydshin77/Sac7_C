#include "Block1.h"
#include "../Scene/Scene.h"
#include "../Stage/Stage.h"

CBlock1::CBlock1()
{
}

CBlock1::~CBlock1()
{
}

bool CBlock1::Init()
{
    /*
    ..*.
    ..*.
    ..*.
    ..*.
    */
    mSideIndexMin = 2;
    mSideIndexMax = 2;
    mFloorIndex = 3;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (j == 2)
            {
                mBlockIndex[i] = i * 4 + j;
                mBlock[i * 4 + j] = '*';
            }

            else
                mBlock[i * 4 + j] = 0;
        }
    }

    return true;
}

void CBlock1::Update(float DeltaTime)
{
    CBlock::Update(DeltaTime);
}

void CBlock1::Output(char* OutputBuffer)
{
    CBlock::Output(OutputBuffer);
}
