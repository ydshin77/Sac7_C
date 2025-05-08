// �� ��������� ���� ������ include�� �Ǵ��� 1���� ó���ǵ���
// �����Ϸ����� �˷��ִ� ������ �Ѵ�.
#pragma once

#include <iostream>
#include <time.h>

//#define	AA		10
#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }


//static int	gNumber = 12;

enum class EPlayerJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

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

struct FItem
{
	char	Name[32] = {};
	EItemType::Type	ItemType = EItemType::Weapon;
	int		Option = 0;
	int		Price = 0;
	int		Sell = 0;
	int		Upgrade = 0;
};

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

struct FPlayerInfo
{
	char	Name[32] = {};
	EPlayerJob	Job = EPlayerJob::None;
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		HPMax = 0;
	int		MP = 0;
	int		MPMax = 0;
	int		Level = 1;
	int		Exp = 0;
	int		Gold = 10000;

	FItem* EquipItem[EEquip::End] = {};
};

struct FMonsterInfo
{
	char	Name[32] = {};
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		HPMax = 0;
	int		MP = 0;
	int		MPMax = 0;
	int		Level = 1;

	// �Ʒ� ������ �÷��̾ ���͸� ����� �� ȹ���� �� �ִ� ����ġ��
	// ���̴�.
	int		Exp = 0;
	int		Gold = 0;
};

#define	INVENTORY_MAX	10
#define	ITEM_UPGRADE_MAX	20

struct FInventory
{
	FItem* ItemList[INVENTORY_MAX] = {};
	int		Count = 0;
};


// �� ���������� cpp���� ���� ������ �ȴ�.
static int	gNumber = 100;

// extern�� �̹� ��������ִ� ���������� �� ��������� include �ϸ�
// �ٸ� ������ �����ؼ� ����� �� �ְ� ���ִ� ����̴�.
extern FPlayerInfo* gPlayer;
extern FInventory* gInventory;
extern FItem* gItemList;
extern int gItemListCount;

struct FPlayerEditorInfo
{
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		MP = 0;
};

struct FMonsterEditorInfo
{
	char	Name[32] = {};
	int		Attack = 0;
	int		Defense = 0;
	int		HP = 0;
	int		MP = 0;
	int		Level = 1;
	int		Exp = 0;
	int		Gold = 0;
};
