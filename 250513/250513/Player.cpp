#include "Player.h"
#include "ObjectManager.h"
#include "Item.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	for (int i = 0; i < EEquip::End; ++i)
	{
		SAFE_DELETE(mEquipItem[i]);
	}
}

bool CPlayer::Init()
{
    // �������� ������ �о�´�.
    FPlayerEditorInfo	JobInfo[3] = {};

    FILE* File = nullptr;

    fopen_s(&File, "PlayerInfo.pli", "rb");

    if (!File)
        return false;

    fread(JobInfo, sizeof(FPlayerEditorInfo), 3, File);

    fclose(File);

    // �÷��̾� �̸��� �Է��ϰ� ������ �����Ѵ�.
    printf("�̸� : ");
    scanf_s("%s", mName, 31);

    printf("1. ���\n");
    printf("2. �ü�\n");
    printf("3. ������\n");
    printf("������ �����ϼ��� : ");
    int	Input = 0;
    scanf_s("%d", &Input);

    if (Input <= (int)EPlayerJob::None ||
        Input >= (int)EPlayerJob::End)
        return false;

    mJob = (EPlayerJob)Input;

    mAttack = JobInfo[Input - 1].Attack;
    mDefense = JobInfo[Input - 1].Defense;
    mHPMax = JobInfo[Input - 1].HP;
    mHP = mHPMax;
    mMPMax = JobInfo[Input - 1].MP;
    mMP = mMPMax;

	return true;
}

bool CPlayer::Init(const char* Name, EPlayerJob Job,
	const FPlayerEditorInfo& JobInfo)
{
    strcpy_s(mName, Name);

    mJob = Job;

    mAttack = JobInfo.Attack;
    mDefense = JobInfo.Defense;
    mHPMax = JobInfo.HP;
    mHP = mHPMax;
    mMPMax = JobInfo.MP;
    mMP = mMPMax;

	return true;
}

void CPlayer::Output()
{
	printf("�̸� : %s\t���� : ", mName);

	switch (mJob)
	{
	case EPlayerJob::Knight:
		printf("���\n");
		break;
	case EPlayerJob::Archer:
		printf("�ü�\n");
		break;
	case EPlayerJob::Magicion:
		printf("������\n");
		break;
	}

	int	LevelExp = CObjectManager::GetInst()->GetLevelExp(mLevel);

	printf("���� : %d\t����ġ : %d / %d\n", mLevel,
		mExp, LevelExp);

	printf("���ݷ� : %d", mAttack);

	if (mEquipItem[EEquip::Weapon])
		printf(" + %d", mEquipItem[EEquip::Weapon]->GetOption());

	printf("\t���� : %d", mDefense);

	if (mEquipItem[EEquip::Armor])
		printf(" + %d", mEquipItem[EEquip::Armor]->GetOption());

	printf("\n");

	printf("ü�� : %d / %d\t���� : %d / %d\n",
		mHP, mHPMax,
		mMP, mMPMax);
	printf("��� : %d\n", mGold);

	printf("�������� : ");

	if (mEquipItem[EEquip::Weapon])
		printf("%s\t", mEquipItem[EEquip::Weapon]->GetName());

	else
		printf("����\t");

	printf("������ : ");

	if (mEquipItem[EEquip::Armor])
		printf("%s\n", mEquipItem[EEquip::Armor]->GetName());

	else
		printf("����\n");
}

void CPlayer::LevelUp()
{
	int	LevelExp = CObjectManager::GetInst()->GetLevelExp(mLevel);

	if (mExp >= LevelExp)
	{
		mExp -= LevelExp;

		++mLevel;

		mAttack = (int)(mAttack * 1.1f);
		mDefense = (int)(mDefense * 1.1f);
		mHPMax = (int)(mHPMax * 1.1f);
		mMPMax = (int)(mMPMax * 1.1f);

		mHP = mHPMax;
		mMP = mMPMax;

		printf("������ �ö����ϴ�.\n");
	}
}
