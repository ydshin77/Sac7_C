#include "Block5.h"

CBlock5::CBlock5()
{
}

CBlock5::~CBlock5()
{
}

bool CBlock5::Init()
{
    /*
    ....
    .**.
    ..**
    ....
    */
    mSideIndexMin = 1;
    mSideIndexMax = 3;
    mFloorIndex = 2;
    mBlockIndex[0] = 5;
    mBlockIndex[1] = 6;
    mBlockIndex[2] = 10;
    mBlockIndex[3] = 11;

    mBlock[5] = '*';
    mBlock[6] = '*';
    mBlock[10] = '*';
    mBlock[11] = '*';

    return true;
}

void CBlock5::Update(float DeltaTime)
{
    CBlock::Update(DeltaTime);
}

void CBlock5::Output(char* OutputBuffer)
{
    CBlock::Output(OutputBuffer);
}
