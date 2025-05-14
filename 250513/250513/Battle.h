#pragma once

#include "GameInfo.h"

class CBattle
{
public:
	CBattle();
	~CBattle();

public:
	bool Init(EMapMenu Map);
	void Run();
};

