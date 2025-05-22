#include "Block3.h"

CBlock3::CBlock3()
{
}

CBlock3::~CBlock3()
{
}

bool CBlock3::Init()
{
    /*
    ....
    .***
    .*..
    ....
    */
    mSideIndexMin = 1;
    mSideIndexMax = 3;
    mFloorIndex = 2;
    mBlockIndex[0] = 5;
    mBlockIndex[1] = 6;
    mBlockIndex[2] = 7;
    mBlockIndex[3] = 9;

    mBlock[5] = '*';
    mBlock[6] = '*';
    mBlock[7] = '*';
    mBlock[9] = '*';

    return true;
}

void CBlock3::Update(float DeltaTime)
{
    CBlock::Update(DeltaTime);
}

void CBlock3::Output(char* OutputBuffer)
{
    CBlock::Output(OutputBuffer);
}
