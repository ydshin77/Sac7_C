#pragma once

#include "Block.h"

class CBlock6 :
    public CBlock
{
public:
	CBlock6();
	virtual ~CBlock6();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
};

