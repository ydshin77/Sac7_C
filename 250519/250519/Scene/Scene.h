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

	LARGE_INTEGER	mSecond;
	LARGE_INTEGER	mTime;
	float			mDeltaTime = 0.f;

public:
	CMaze* GetMaze()	const
	{
		return mMaze;
	}

public:
	virtual void SetMaze(CMaze* Maze);

public:
	virtual bool Init();
	virtual void Run();

private:
	void Update();
	void Output();

public:
	template <typename T>
	T* CreateObj(int x, int y)
	{
		T* Obj = new T;

		Obj->SetPos(x, y);
		Obj->SetScene(this);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		mObjList.push_back(Obj);

		return Obj;
	}
};

