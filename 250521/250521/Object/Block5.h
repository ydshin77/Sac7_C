#pragma once

#include "Block.h"

class CBlock5 :
    public CBlock
{
public:
	CBlock5();
	virtual ~CBlock5();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
};

