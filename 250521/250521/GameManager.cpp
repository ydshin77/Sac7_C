#include "GameManager.h"
#include "Scene/SceneManager.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CSceneManager::DestroyInst();
}

bool CGameManager::Init()
{
	if (!CSceneManager::GetInst()->Init())
		return false;

	return true;
}

void CGameManager::Run()
{
	while (mLoop)
	{
		CSceneManager::GetInst()->Run();
	}
}

CGameManager* CGameManager::GetInst()
{
	if (!mInst)
		mInst = new CGameManager;

	return mInst;
}

void CGameManager::DestroyInst()
{
	SAFE_DELETE(mInst);
}
