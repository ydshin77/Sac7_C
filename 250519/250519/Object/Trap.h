#pragma once

#include "GameObject.h"

class CPlayer;
class CTrap :
    public CGameObject
{
public:
	CTrap();
	virtual ~CTrap();

protected:
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
};

