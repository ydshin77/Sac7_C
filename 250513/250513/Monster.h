#pragma once

#include "GameInfo.h"

class CMonster
{
public:
	CMonster();
	CMonster(const CMonster& Monster);
	~CMonster();

private:
	char	mName[32] = {};
	int		mAttack = 0;
	int		mDefense = 0;
	int		mHP = 0;
	int		mHPMax = 0;
	int		mMP = 0;
	int		mMPMax = 0;
	int		mLevel = 1;

	// �Ʒ� ������ �÷��̾ ���͸� ����� �� ȹ���� �� �ִ� ����ġ��
	// ���̴�.
	int		mExp = 0;
	int		mGold = 0;

public:
	int GetAttack()	const
	{
		return mAttack;
	}

	int GetDefense()	const
	{
		return mDefense;
	}

	// ����Ÿ���� bool�� ������ �׾����� ��Ҵ��� ��ȯ�ϱ� ���ؼ��̴�.
	bool Damage(int Dmg)
	{
		mHP -= Dmg;

		return mHP > 0;
	}

	int GetExp()	const
	{
		return mExp;
	}

	int GetGold()	const
	{
		return mGold;
	}

public:
	bool Init(const FMonsterEditorInfo& Info);
	void Output();
	// �ڱ� �ڽ��� ������ ���ο� ��ü�� ������ش�.
	CMonster* Clone();
};

