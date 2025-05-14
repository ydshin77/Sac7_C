#include "Battle.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"

namespace EBattleMenu
{
	enum Type
	{
		None,
		Attack,
		Back,
		End
	};
}

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
}

bool CBattle::Init(EMapMenu Map)
{
	mMap = Map;

    return true;
}

EBattleResult CBattle::Battle(CPlayer* Player, CMonster* Monster)
{
	// �÷��̾ ���͸� �����Ѵ�.
	// ���� ���Ⱑ ���� ��� �߰� ���ݷ��� ����Ǿ�� �Ѵ�.
	int	Attack = Player->GetAttack();

	/*if (gPlayer->EquipItem[EEquip::Weapon])
		Attack += gPlayer->EquipItem[EEquip::Weapon]->Option;*/

	int	Damage = Attack - Monster->GetDefense();

	// �ּҵ������� 1�� �� �� �ְ� �Ѵ�.
	// ���׿����� : ������ ���ǽ��� true�� ��� : ������ ���� ��ȯ�ǰ�
	// false�� ��� : �������� ���� ��ȯ�ȴ�.
	Damage = Damage <= 0 ? 1 : Damage;
	/*if (Damage <= 0)
		Damage = 1;*/

	printf("Player�� Monster���� %d �������� �־����ϴ�.\n", Damage);

	if (!Monster->Damage(Damage))
	{
		// ����ġ�� ��带 �����ϰ� �Ѵ�.
		Player->AddExp(Monster->GetExp());
		Player->AddGold(Monster->GetGold());

		printf("Monster�� �׾����ϴ�.\n");

		// �κ��丮�� ������ ���� ��쿡�� �������� ȹ���� �� �ְ� �Ѵ�.
		//if (gInventory->Count < INVENTORY_MAX)
		//{
		//	// �������� ����� Ȯ���� ���Ѵ�.
		//	float	Percent = rand() % 10000 / 100.f;

		//	// 20% Ȯ���� �������� ȹ���Ѵ�.
		//	if (Percent < 20.f)
		//	{
		//		// � �������� ������� �����Ѵ�.
		//		int	DropIndex = rand() % gItemListCount;

		//		FItem* DropItem = new FItem;

		//		*DropItem = gItemList[DropIndex];

		//		// �κ��丮�� �� ������ ã�� �������� �־��ش�.
		//		for (int i = 0; i < INVENTORY_MAX; ++i)
		//		{
		//			if (!gInventory->ItemList[i])
		//			{
		//				gInventory->ItemList[i] = DropItem;
		//				++gInventory->Count;
		//				break;
		//			}
		//		}

		//		printf("%s �������� ȹ���Ͽ����ϴ�.\n",
		//			DropItem->Name);
		//		system("pause");
		//	}
		//}


		// ������ �ߴ��� Ȯ��.
		Player->LevelUp();

		system("pause");

		return EBattleResult::MonsterDeath;
	}

	// ���Ͱ� �÷��̾ �����Ѵ�.
	// �������� ���� ��� �߰� ������ �����Ѵ�.
	int	Defense = Player->GetDefense();

	/*if (gPlayer->EquipItem[EEquip::Armor])
		Defense += gPlayer->EquipItem[EEquip::Armor]->Option;*/

	Damage = Monster->GetAttack() - Defense;

	Damage = Damage <= 0 ? 1 : Damage;

	printf("Monster�� Player���� %d �������� �־����ϴ�.\n", Damage);

	if (!Player->Damage(Damage))
	{
		// �÷��̾ �׾��� ��� ����ġ�� ��带 10% ���ҽ�Ű��
		// ü�°� ������ �ִ�ġ�� �Ͽ� ��Ȱ��Ų��.
		Player->AddExp(Player->GetExp() * -0.1f);
		Player->AddGold(Player->GetGold() * -0.1f);

		Player->Restore();

		printf("Player�� �׾����ϴ�.\n");

		system("pause");

		return EBattleResult::PlayerDeath;
	}

	system("pause");

	return EBattleResult::None;
}

void CBattle::Run()
{
	CPlayer* Player = CObjectManager::GetInst()->GetPlayer();
	CMonster* Monster = CObjectManager::GetInst()->CloneMonster(mMap);

    while (true)
    {
		system("cls");
		printf("================ Player ================\n");
		Player->Output();

		printf("================ Monster ================\n");
		Monster->Output();

		// ���� �޴�
		printf("1. ����\n");
		printf("2. ��������\n");
		printf("�޴��� �����ϼ��� : ");
		int	Input;
		scanf_s("%d", &Input);

		switch (Input)
		{
		case EBattleMenu::Attack:
			if (Battle(Player, Monster) == EBattleResult::MonsterDeath)
			{
				//Monster->HP = Monster->HPMax;
				//Monster->MP = Monster->MPMax;
				// ���� ���͸� �����ϰ� �ٽ� �����Ѵ�.
				SAFE_DELETE(Monster);

				Monster = CObjectManager::GetInst()->CloneMonster(mMap);
			}
			break;
		case EBattleMenu::Back:
			// ���⼭ �޸� ���Ű� ���� ��� �޸� ���� ���� �ȴ�.
			SAFE_DELETE(Monster);
			return;
		}
    }
}
