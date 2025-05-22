#pragma once

#include "Block.h"

class CBlock4 :
    public CBlock
{
public:
	CBlock4();
	virtual ~CBlock4();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
};

