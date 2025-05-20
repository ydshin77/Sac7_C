#pragma once

#include "../GameInfo.h"

class CGameObject;
class CMaze;
class CScene
{
public:
	CScene();
	virtual ~CScene();

protected:
	CMaze* mMaze = nullptr;
	std::list<CGameObject*>	mObjList;
	char* mOutputBuffer = nullptr;

public:
	void SetMaze(CMaze* Maze);

public:
	virtual bool Init();
	virtual void Run();

public:
	template <typename T>
	T* CreateObj(int x, int y)
	{
		T* Obj = new T;

		Obj->SetPos(x, y);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		mObjList.push_back(Obj);

		return Obj;
	}
};

