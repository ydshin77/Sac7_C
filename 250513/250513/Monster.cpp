#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(const CMonster& Monster)
{
    *this = Monster;
}

CMonster::~CMonster()
{
}

bool CMonster::Init(const FMonsterEditorInfo& Info)
{
    strcpy_s(mName, Info.Name);
    mAttack = Info.Attack;
    mDefense = Info.Defense;
    mHP = Info.HP;
    mHPMax = Info.HP;
    mMP = Info.MP;
    mMPMax = Info.MP;
    mLevel = Info.Level;
    mExp = Info.Exp;
    mGold = Info.Gold;

    return true;
}

void CMonster::Output()
{
    printf("�̸� : %s\t���� : %d\n", mName,
        mLevel);

    printf("ȹ�����ġ : %d\tȹ���� : %d\n", mExp,
        mGold);
    printf("���ݷ� : %d\t���� : %d\n", mAttack,
        mDefense);
    printf("ü�� : %d / %d\t���� : %d / %d\n",
        mHP, mHPMax,
        mMP, mMPMax);
}

CMonster* CMonster::Clone()
{
    // new CMonster�� �ؼ� ���ο� ��ü�� �����.
    // �̶� *this�� ���־ �� �Լ��� ȣ���� ��ü�� ���ڷ� �����Ͽ�
    // ��������ڿ��� �״�� �����͸� �����ϰ� ������ ��ü�� �ּҸ�
    // ��ȯ���ش�.
    return new CMonster(*this);
}
