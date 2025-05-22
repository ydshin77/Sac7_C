#pragma once

#include "../GameInfo.h"

class CStage;
class CGameObject;
class CScene
{
public:
	CScene();
	virtual ~CScene();

protected:
	CStage* mStage = nullptr;
	char* mOutputBuffer = nullptr;
	std::list<CGameObject*>	mObjList;

	LARGE_INTEGER	mSecond;
	LARGE_INTEGER	mTime;
	float			mDeltaTime = 0.f;

public:
	CStage* GetStage()	const
	{
		return mStage;
	}

public:
	virtual bool Init();
	virtual bool Begin();
	virtual void Run();

private:
	void Update();
	void Output();

protected:
	virtual void BlockDestroy();

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

