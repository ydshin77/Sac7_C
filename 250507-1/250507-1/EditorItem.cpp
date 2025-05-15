
#include <iostream>
#include "GameInfo.h"

// 상점 아이템 기본 정보 설정
// 보통은 아이템 정보 파일, 상점에서 파는 아이템 목록 파일. 이렇게 두 개 생성
// 여기서는 상점 목록에 아이템 정보까지 넣어서 실습함

// EditorItem 메뉴
namespace EEditorItemMenu
{
	enum Type
	{
		None,
		Create,
		Delete,
		Modify,
		Load,
		Output,
		Exit,
		End
	};
}

// 파일 쓰기 함수
void Save(FPlayerEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "PlayerInfo.pli", "wb");

	if (!FileStream)
		return;

	fwrite(Info, sizeof(FPlayerEditorInfo), 3, FileStream);

	fclose(FileStream);
}

// 파일 읽기 함수
void Load(FPlayerEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "PlayerInfo.pli", "rb");

	if (!FileStream)
		return;

	fread(Info, sizeof(FPlayerEditorInfo), 3, FileStream);

	fclose(FileStream);
}

// 아이템 정보 수정 함수
void Modify(FPlayerEditorInfo* Info)
{
	// 직업 선택
	printf("1. 기사\n");
	printf("2. 궁수\n");
	printf("3. 마법사\n");

	printf("수정할 직업을 선택하세요 : ");
	int Input = 0;
	scanf_s("%d", &Input);

	if (Input <= 0 || Input >= 4)
		return;

	// 능력치 수정
	int Index = Input - 1;

	printf("공격력 : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("방어력 : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("체력 : ");
	scanf_s("%d", &Info[Index].HP);

	printf("마나 : ");
	scanf_s("%d", &Info[Index].MP);

	// 입력한 내용을 파일에 저장
	Save(Info);
}

// 아이템 생성 함수
// 인자에 FItem** ItemArray라고 쓸 경우, 배열이 새로 생성되었을 때 배열의 주소가
// 인자의 이중 포인터에만 저장되고 메인의 이중 포인터에는 저장되지 않음
// => 이중 포인터 레퍼런스로 사용해야 메인의 이중 포인터에도 새로운 배열의 주소가 저장됨
// Capacity와 Count 값이 변경될 수 있으니 레퍼런스 사용 (단순 값 변경이 목적이면 포인터보다 레퍼런스 사용)
void Create(FItem**& ItemArray, int& Capacity, int& Count)
{
	// 배열이 꽉 찼는지 확인하고, 꽉 찼다면 배열 공간을 늘려줌
	if (Capacity == Count)
	{
		// 배열 공간을 2배로 늘려줌
		Capacity *= 2;

		// 늘려준 공간 수만큼 배열을 새로 생성
		FItem** NewArray = new FItem* [Capacity];

		// 기존 배열에 있는 정보를 새로운 배열에 넣어줌
		for (int i = 0; i < Count; ++i)
		{
			NewArray[i] = ItemArray[i];
		}

		// 기존 배열 제거
		SAFE_DELETE_ARRAY(ItemArray);

		// 기존 배열의 주소를 새로운 배열의 주소로 갱신
		ItemArray = NewArray;
	}

	system("cls");

	printf("1. 무기\n");
	printf("2. 방어구\n");

	printf("추가할 아이템 종류를 선택하세요 : ");
	int ItemType = 0;
	scanf_s("%d", &ItemType);

	if (ItemType <= EItemType::None || ItemType >= EItemType::End)
		return;

	// 아이템 생성
	FItem* Item = new FItem;

	// int를 열거형 안에 넣을 때는 형변환을 해주어야 함
	Item->ItemType = (EItemType::Type)ItemType;

	printf("이름 : ");
	scanf_s("%s", Item->Name, 31);

	switch (Item->ItemType)
	{
	case EItemType::Weapon:
		printf("공격력 : ");
		break;
	case EItemType::Armor:
		printf("방어력 : ");
		break;
	}
	scanf_s("%d", &Item->Option);

	printf("상점 구매 가격 : ");
	scanf_s("%d", &Item->Price);

	printf("상점 판매 가격 : ");
	scanf_s("%d", &Item->Sell);

	ItemArray[Count] = Item;
	++Count;
}

int main()
{
	// 전체 배열 크기
	int ItemCapacity = 2;

	// 배열에 추가된 아이템 개수
	int ItemCount = 0;

	// 아이템 종류가 늘어날 수도 있으니 가변 배열로 생성
	// 방법 1. 이중 포인터 사용 -> 메모리 주소를 저장하는 배열 세 개 생성
	FItem** ItemArray = new FItem* [ItemCapacity];

	// 방법 2. 포인터 사용		-> 아이템 정보를 저장하는 배열 세 개 생성
	//FItem* ItemArray = new FItem[ItemCapacity];

	while (true)
	{
		system("cls");

		printf("1. 아이템 추가\n");
		printf("2. 아이템 삭제\n");
		printf("3. 아이템 수정\n");
		printf("4. 불러오기\n");
		printf("5. 출력\n");
		printf("6. 종료\n");

		printf("메뉴를 선택하세요 : ");
		int Input = 0;
		scanf_s("%d", &Input);

		switch (Input)
		{
		case EEditorItemMenu::Create:
			Create(ItemArray, ItemCapacity, ItemCount);
			break;
		case EEditorItemMenu::Delete:
			break;
		case EEditorItemMenu::Modify:
			break;
		case EEditorItemMenu::Load:
			Load(JobInfo);
			break;
		case EEditorItemMenu::Output:
			for (int i = 0; i < 3; ++i)
			{
				printf("공격력 : %d\n", JobInfo[i].Attack);
				printf("방어력 : %d\n", JobInfo[i].Defense);
				printf("체력 : %d\n", JobInfo[i].HP);
				printf("마나 : %d\n", JobInfo[i].MP);
				printf("==============\n");
			}
			system("pause");
			break;
		case EEditorItemMenu::Exit:
			// 게임이 종료될 때 자동 세이브
			Save(JobInfo);

			// 동적 배열 제거
			SAFE_DELETE_ARRAY(ItemArray);

			return 0;
		}

	}

	return 0;
}