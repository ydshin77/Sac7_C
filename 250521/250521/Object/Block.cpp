#include "Block.h"
#include "../Stage/Stage.h"
#include "../Scene/SceneMainMenu.h"
#include "../Scene/SceneManager.h"

CBlock::CBlock()
{
}

CBlock::~CBlock()
{
}

bool CBlock::Init()
{
    return true;
}

void CBlock::Update(float DeltaTime)
{
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        mPosX -= mSideSpeed * DeltaTime;
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        mPosX += mSideSpeed * DeltaTime;
    }

    if (abs(mPosX) >= 1.f)
    {
        mPos.X += (int)mPosX;


        if (mPos.X + mSideIndexMin < 0)
            ++mPos.X;

        else if (mPos.X + mSideIndexMax >= STAGE_WIDTH)
            mPos.X = STAGE_WIDTH - 1 - mSideIndexMax;

        else
        {
            for (int i = 0; i < 4; ++i)
            {
                int IndexX = mBlockIndex[i] % 4 + mPos.X;
                int IndexY = mPos.Y - (3 - mBlockIndex[i] / 4);

                EBlockType  Block =
                    mScene->GetStage()->GetBlock(IndexX, IndexY);

                if (Block == EBlockType::Block)
                {
                    if (mPosX > 0.f)
                    {
                        --mPos.X;
                    }

                    else
                    {
                        ++mPos.X;
                    }
                }
            }

        }

        mPosX -= (int)mPosX;
    }

    mPosY += mDownSpeed * DeltaTime;

    if (mPosY >= 1.f)
    {
        bool    MoveStop = false;

        for (int i = 0; i < 4; ++i)
        {
            // 블록인 인덱스를 이용해서 X, Y 인덱스를 구한다.
            int IndexX = mBlockIndex[i] % 4;
            int IndexY = 3 - mBlockIndex[i] / 4;

            // 현재 위치의 아래가 블록인지 비어있는지 체크한다.
            EBlockType BlockType =
                mScene->GetStage()->GetBlock(mPos.X + IndexX, 
                    mPos.Y - IndexY + 1);

            if (BlockType == EBlockType::Block)
            {
                MoveStop = true;
            }
        }

        if (!MoveStop)
        {
            mPos.Y += (int)mPosY;
            mPosY -= (int)mPosY;
        }

        else
        {
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (mBlock[i * 4 + j] != 0)
                    {
                        int y = mPos.Y - (3 - i);

                        if (y < 0)
                        {
                            CSceneManager::GetInst()->CreateNextScene<CSceneMainMenu>();
                            return;
                        }

                        mScene->GetStage()->SetBlock(EBlockType::Block,
                            mPos.X + j, y);
                    }
                }
            }

            ClearLine();

            Destroy();
            return;
        }
    }

    static bool Space = false;

    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        Space = true;
    }

    else if (Space)
    {
        Space = false;
        for (int i = 0; i < 4; ++i)
        {
            // 블록인 인덱스를 이용해서 X, Y 인덱스를 구한다.
            int IndexX = mBlockIndex[i] % 4;
            int IndexY = 3 - mBlockIndex[i] / 4;

            if (IndexY == 3 - mFloorIndex)
            {
                int     BlockIndex = -1;

                for (int j = mPos.Y - IndexY; j < STAGE_HEIGHT; ++j)
                {
                    EBlockType BlockType =
                        mScene->GetStage()->GetBlock(mPos.X + IndexX,
                            j);

                    if (BlockType == EBlockType::Block)
                    {
                        BlockIndex = j;
                        break;
                    }
                }

                if (BlockIndex != -1)
                {
                    mPos.Y = BlockIndex - (mFloorIndex - 2);
                    ChagneBlock();
                    ClearLine();
                    Destroy();
                    return;
                }

                else
                {
                    mPos.Y = STAGE_HEIGHT - 1;
                    mPos.Y += (3 - mFloorIndex);
                    ChagneBlock();
                    ClearLine();
                    Destroy();
                    return;
                }
            }

            else
            {
                // 현재 인덱스의 한칸 아래가 블록인지를 체크한다.
                int DownIndex = mBlockIndex[i] / 4 + 1;
                if (mBlock[DownIndex * 4 + IndexX] == '*')
                    continue;

                int     BlockIndex = -1;

                // 바닥인덱스와의 차이를 구한다.
                int CurY = mFloorIndex - mBlockIndex[i] / 4;
                

                for (int j = mPos.Y - IndexY; j < STAGE_HEIGHT - CurY; ++j)
                {
                    EBlockType BlockType =
                        mScene->GetStage()->GetBlock(mPos.X + IndexX,
                            j);

                    if (BlockType == EBlockType::Block)
                    {
                        BlockIndex = j;
                        break;
                    }
                }

                if (BlockIndex != -1)
                {
                    mPos.Y = BlockIndex + (IndexY - 1);
                    ChagneBlock();
                    ClearLine();
                    Destroy();
                    return;
                }
            }
        }
    }
}

void CBlock::Output(char* OutputBuffer)
{
    int OutputCountX = STAGE_WIDTH + 3;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (mBlock[i * 4 + j] != 0)
            {
                int PosX = mPos.X + j;
                int PosY = mPos.Y - (3 - i);

                if (PosY >= 0)
                {
                    OutputBuffer[PosY * OutputCountX + PosX + 1] = '*';
                }
            }
        }
    }
}

void CBlock::ChagneBlock()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (mBlock[i * 4 + j] != 0)
            {
                int y = mPos.Y - (3 - i);

                if (y < 0)
                {
                    CSceneManager::GetInst()->CreateNextScene<CSceneMainMenu>();
                    return;
                }

                else if (y >= STAGE_HEIGHT)
                    return;

                mScene->GetStage()->SetBlock(EBlockType::Block,
                    mPos.X + j, y);
            }
        }
    }
}

void CBlock::ClearLine()
{
    // 이 블록의 Y값을 기준으로 위 추가 3줄까지만 지워질 가능성이
    // 존재한다.
    for (int i = 0; i < 4; ++i)
    {
        int y = mPos.Y - 1 - (3 - i);

        if (y >= STAGE_HEIGHT)
            continue;

        bool    LineClear = true;

        for (int j = 0; j < STAGE_WIDTH; ++j)
        {
            EBlockType  Block = mScene->GetStage()->GetBlock(j, y);

            if (Block == EBlockType::Empty)
            {
                LineClear = false;
                break;
            }
        }

        if (LineClear)
        {
            for (int j = y; j > 0; --j)
            {
                mScene->GetStage()->LineDrop(j);
            }

            mScene->GetStage()->ClearLine(0);
        }
    }
}
