#pragma once

#include "GameObject.h"

class CPlayer;
class CItem :
    public CGameObject
{
public:
	CItem();
	virtual ~CItem();

protected:
	EItemType	mItemType;
	CPlayer* mPlayer = nullptr;

public:
	void SetPlayer(CPlayer* Player)
	{
		mPlayer = Player;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* Buffer);

protected:
	virtual void ItemGain() = 0;
};

