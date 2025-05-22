#pragma once

#include "Block.h"

class CBlock7 :
    public CBlock
{
public:
	CBlock7();
	virtual ~CBlock7();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
};

