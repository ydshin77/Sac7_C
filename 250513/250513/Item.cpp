#include "Item.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& Item)
{
    *this = Item;
}

CItem::~CItem()
{
}

bool CItem::Init(FILE* File)
{
    fread(mName, sizeof(char), 32, File);
    fread(&mItemType, sizeof(EItemType::Type), 1, File);
    fread(&mOption, sizeof(int), 1, File);
    fread(&mPrice, sizeof(int), 1, File);
    fread(&mSell, sizeof(int), 1, File);
    fread(&mUpgrade, sizeof(int), 1, File);

    return true;
}

void CItem::Output()
{
	printf("�̸� : %s", mName);

	if (mUpgrade > 0)
		printf(" + %d", mUpgrade);

	printf("\t���� : ");

	switch (mItemType)
	{
	case EItemType::Weapon:
		printf("����\n");
		printf("���ݷ� : %d\n", mOption);
		break;
	case EItemType::Armor:
		printf("��\n");
		printf("���� : %d\n", mOption);
		break;
	}

	printf("�������Ű��� : %d\t�����ǸŰ��� : %d\n",
		mPrice, mSell);
}

CItem* CItem::Clone()
{
    return new CItem(*this);
}
