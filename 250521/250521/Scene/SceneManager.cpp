#include "SceneManager.h"
#include "SceneMainMenu.h"

CSceneManager* CSceneManager::mInst = nullptr;

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(mScene);
	SAFE_DELETE(mNextScene);
}

bool CSceneManager::Init()
{
	mScene = new CSceneMainMenu;

	if (!mScene->Init())
		return false;

	if (!mScene->Begin())
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

		mScene->Begin();
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
