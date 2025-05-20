#pragma once

#include <iostream>
#include <time.h>

// ���� �Ҵ� �� �����ϰ� �޸𸮸� ����� ���� define���� ����
#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p = nullptr;}

// �÷��̾� ���� ����
enum class EPlayerJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

// ������ ����
namespace EItemType
{
	enum Type
	{
		None = -1,
		Weapon,
		Armor,
		End
	};
}

// ������ ����
// ������ ������ �÷��̾� �������� ���� �־�� ��
// �÷��̾ ������ �����͸� ����Ͽ� ������ ������ �� �ű� ����
struct FItem
{
	char		Name[32] = {};
	EItemType::Type ItemType = EItemType::Weapon;
	int			Option = 0;
	int			Price = 0;
	int			Sell = 0;
	int			Upgrade = 0;
};

// ������ ����
namespace EEquip
{
	enum Type
	{
		None = -1,
		Weapon,
		Armor,
		End
	};
}

// �÷��̾� ����
struct FPlayerInfo
{
	char		Name[32] = {};
	EPlayerJob	Job = EPlayerJob::None;
	int			Attack = 0;
	int			Defense = 0;
	int			HP = 0;
	int			HPMax = 0;
	int			MP = 0;
	int			MPMax = 0;
	int			Level = 1;
	int			Exp = 0;
	int			Gold = 10000;
	FItem*		EquipItem[EEquip::End] = {};
};

// ���� ����
struct FMonsterInfo
{
	char		Name[32] = {};
	int			Attack = 0;
	int			Defense = 0;
	int			HP = 0;
	int			HPMax = 0;
	int			MP = 0;
	int			MPMax = 0;
	int			Level = 1;

	// �÷��̾ ���͸� ����� �� ȹ���� �� �ִ� ����ġ�� ��
	int			Exp = 0;
	int			Gold = 0;
};

// �κ��丮 �ִ� �뷮 -> define���� ��� ���� �Ϲ���
#define INVENTORY_MAX 10
// ��ȭ �ִ� ����
#define ITEM_UPGRADE_MAX 20

// �κ��丮 ����
struct FInventory
{
	FItem* ItemList[INVENTORY_MAX] = {};
	int		Count = 0;
};

// ������ ������ �ٸ� �������� �����Ͽ� ����� �� �ֵ��� extern ����
extern FPlayerInfo* gPlayer;
extern FInventory* gInventory;
extern FItem* gItemList;
extern int gItemListCount;

// �������� �ٸ��� ���� �Ǿ�� �ϴ� �ɷ�ġ
struct FPlayerEditorInfo
{
	int			Attack = 0;
	int			Defense = 0;
	int			HP = 0;
	int			MP = 0;
};

// ���̵����� �ٸ��� ���� �Ǿ�� �ϴ� ���� �ɷ�ġ
struct FMonsterEditorInfo
{
	char		Name[32] = {};
	int			Attack = 0;
	int			Defense = 0;
	int			HP = 0;
	int			MP = 0;
	int			Level = 1;
	int			Exp = 0;
	int			Gold = 0;
};