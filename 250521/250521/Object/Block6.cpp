#include "Block6.h"

CBlock6::CBlock6()
{
}

CBlock6::~CBlock6()
{
}

bool CBlock6::Init()
{
    /*
    ....
    .**.
    **..
    ....
    */
    mSideIndexMin = 0;
    mSideIndexMax = 2;
    mFloorIndex = 2;
    mBlockIndex[0] = 5;
    mBlockIndex[1] = 6;
    mBlockIndex[2] = 8;
    mBlockIndex[3] = 9;

    mBlock[5] = '*';
    mBlock[6] = '*';
    mBlock[8] = '*';
    mBlock[9] = '*';

    return true;
}

void CBlock6::Update(float DeltaTime)
{
    CBlock::Update(DeltaTime);
}

void CBlock6::Output(char* OutputBuffer)
{
    CBlock::Output(OutputBuffer);
}
