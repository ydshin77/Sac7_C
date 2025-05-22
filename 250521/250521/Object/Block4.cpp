#include "Block4.h"

CBlock4::CBlock4()
{
}

CBlock4::~CBlock4()
{
}

bool CBlock4::Init()
{
    /*
    ....
    .**.
    .**.
    ....
    */
    mSideIndexMin = 1;
    mSideIndexMax = 2;
    mFloorIndex = 2;
    mBlockIndex[0] = 5;
    mBlockIndex[1] = 6;
    mBlockIndex[2] = 9;
    mBlockIndex[3] = 10;

    mBlock[5] = '*';
    mBlock[6] = '*';
    mBlock[9] = '*';
    mBlock[10] = '*';

    return true;
}

void CBlock4::Update(float DeltaTime)
{
    CBlock::Update(DeltaTime);
}

void CBlock4::Output(char* OutputBuffer)
{
    CBlock::Output(OutputBuffer);
}
