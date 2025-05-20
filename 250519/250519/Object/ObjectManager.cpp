#include "ObjectManager.h"

CObjectManager* CObjectManager::mInst = nullptr;

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	return true;
}

CObjectManager* CObjectManager::GetInst()
{
	if (!mInst)
		mInst = new CObjectManager;

	return mInst;
}

void CObjectManager::DestroyInst()
{
	SAFE_DELETE(mInst);
}
