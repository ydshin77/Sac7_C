#pragma once

#include "Item.h"

class CItemMoveSpeed :
    public CItem
{
public:
	CItemMoveSpeed();
	virtual ~CItemMoveSpeed();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* Buffer);

protected:
	virtual void ItemGain();
};

