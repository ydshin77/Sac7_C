#pragma once

#include "Block.h"

class CBlock1 :
    public CBlock
{
public:
	CBlock1();
	virtual ~CBlock1();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
};

