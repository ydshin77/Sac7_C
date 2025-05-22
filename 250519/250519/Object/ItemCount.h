#pragma once

#include "Item.h"

class CItemCount :
    public CItem
{
public:
	CItemCount();
	virtual ~CItemCount();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* Buffer);

protected:
	virtual void ItemGain();
};

