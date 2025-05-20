#pragma once

#include <iostream>
#include <time.h>

// 동적 할당 후 안전하게 메모리를 지우기 위해 define으로 선언
#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p = nullptr;}

// 플레이어 직업 정보
enum class EPlayerJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

// 아이템 종류
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

// 아이템 정보
// 아이템 정보가 플레이어 정보보다 위에 있어야 함
// 플레이어가 아이템 포인터를 사용하여 아이템 장착을 할 거기 때문
struct FItem
{
	char		Name[32] = {};
	EItemType::Type ItemType = EItemType::Weapon;
	int			Option = 0;
	int			Price = 0;
	int			Sell = 0;
	int			Upgrade = 0;
};

// 아이템 장착
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

// 플레이어 정보
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

// 몬스터 정보
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

	// 플레이어가 몬스터를 잡았을 때 획득할 수 있는 경험치와 돈
	int			Exp = 0;
	int			Gold = 0;
};

// 인벤토리 최대 용량 -> define으로 잡는 것이 일반적
#define INVENTORY_MAX 10
// 강화 최대 레벨
#define ITEM_UPGRADE_MAX 20

// 인벤토리 정보
struct FInventory
{
	FItem* ItemList[INVENTORY_MAX] = {};
	int		Count = 0;
};

// 생성한 정보를 다른 곳에서도 공유하여 사용할 수 있도록 extern 해줌
extern FPlayerInfo* gPlayer;
extern FInventory* gInventory;
extern FItem* gItemList;
extern int gItemListCount;

// 직업별로 다르게 세팅 되어야 하는 능력치
struct FPlayerEditorInfo
{
	int			Attack = 0;
	int			Defense = 0;
	int			HP = 0;
	int			MP = 0;
};

// 난이도별로 다르게 세팅 되어야 하는 몬스터 능력치
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