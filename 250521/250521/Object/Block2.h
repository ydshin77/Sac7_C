#pragma once

#include "Block.h"

class CBlock2 :
    public CBlock
{
public:
	CBlock2();
	virtual ~CBlock2();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
};

