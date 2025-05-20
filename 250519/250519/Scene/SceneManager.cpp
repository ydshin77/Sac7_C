#include "SceneManager.h"
#include "SceneMazeMenu.h"

CSceneManager* CSceneManager::mInst = nullptr;

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(mScene);
}

bool CSceneManager::Init()
{
	mScene = new CSceneMazeMenu;

	if (!mScene->Init())
		return false;

	return true;
}

void CSceneManager::Run()
{
	mScene->Run();

	if (mNextScene)
	{
		system("cls");

		SAFE_DELETE(mScene);

		mScene = mNextScene;

		mNextScene = nullptr;
	}
}

CSceneManager* CSceneManager::GetInst()
{
	if (!mInst)
		mInst = new CSceneManager;

	return mInst;
}

void CSceneManager::DestroyInst()
{
	SAFE_DELETE(mInst);
}
