#pragma once

#include "Block.h"

class CBlock3 :
    public CBlock
{
public:
	CBlock3();
	virtual ~CBlock3();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
};

