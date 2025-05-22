#include "Block2.h"

CBlock2::CBlock2()
{
}

CBlock2::~CBlock2()
{
}

bool CBlock2::Init()
{
    /*
    ....
    ***.
    ..*.
    ....
    */
    mSideIndexMin = 0;
    mSideIndexMax = 2;
    mFloorIndex = 2;
    mBlockIndex[0] = 4;
    mBlockIndex[1] = 5;
    mBlockIndex[2] = 6;
    mBlockIndex[3] = 10;

    mBlock[4] = '*';
    mBlock[5] = '*';
    mBlock[6] = '*';
    mBlock[10] = '*';

    return true;
}

void CBlock2::Update(float DeltaTime)
{
    CBlock::Update(DeltaTime);
}

void CBlock2::Output(char* OutputBuffer)
{
    CBlock::Output(OutputBuffer);
}
