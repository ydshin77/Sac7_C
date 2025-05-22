#pragma once

#include "../GameInfo.h"

class CScene;
class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager();

private:
	CScene* mScene = nullptr;
	CScene* mNextScene = nullptr;

public:
	bool Init();
	void Run();

public:
	template <typename T>
	T* CreateNextScene()
	{
		T* Scene = new T;

		if (!Scene->Init())
		{
			SAFE_DELETE(Scene);
			return nullptr;
		}

		mNextScene = (CScene*)Scene;

		return Scene;
	}

private:
	static CSceneManager* mInst;

public:
	static CSceneManager* GetInst();
	static void DestroyInst();
};

