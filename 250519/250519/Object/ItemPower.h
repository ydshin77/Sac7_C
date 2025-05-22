#pragma once

#include "Item.h"

class CItemPower :
    public CItem
{
public:
	CItemPower();
	virtual ~CItemPower();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* Buffer);

protected:
	virtual void ItemGain();
};

