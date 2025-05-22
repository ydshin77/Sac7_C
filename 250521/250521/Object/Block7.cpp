#include "Block7.h"

CBlock7::CBlock7()
{
}

CBlock7::~CBlock7()
{
}

bool CBlock7::Init()
{
    /*
    ....
    .*..
    ***.
    ....
    */
    mSideIndexMin = 0;
    mSideIndexMax = 2;
    mFloorIndex = 2;
    mBlockIndex[0] = 5;
    mBlockIndex[1] = 8;
    mBlockIndex[2] = 9;
    mBlockIndex[3] = 10;

    mBlock[5] = '*';
    mBlock[8] = '*';
    mBlock[9] = '*';
    mBlock[10] = '*';

    return true;
}

void CBlock7::Update(float DeltaTime)
{
    CBlock::Update(DeltaTime);
}

void CBlock7::Output(char* OutputBuffer)
{
    CBlock::Output(OutputBuffer);
}
