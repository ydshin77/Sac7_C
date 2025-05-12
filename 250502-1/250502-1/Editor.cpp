
#include <iostream>
#include "GameInfo.h"

// 직업에 따른 플레이어 기본 정보 설정
// 값을 쉽게 수정 및 테스트할 수 있도록, 보통 데이터는 파일에 저장함

// Editor 메뉴
namespace EEditorMenu
{
	enum Type
	{
		None,
		Modify,
		Delete,
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

// 직업 수정 함수
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

int main()
{
	// 3개 생성 (기사, 궁수, 마법사)
	FPlayerEditorInfo JobInfo[3] = {};

	while (true)
	{
		system("cls");

		printf("1. 직업 수정\n");
		printf("2. 직업 삭제\n");
		printf("3. 불러오기\n");
		printf("4. 출력\n");
		printf("5. 종료\n");

		printf("메뉴를 선택하세요 : ");
		int Input = 0;
		scanf_s("%d", &Input);

		switch (Input)
		{
		case EEditorMenu::Modify:
			Modify(JobInfo);
			break;
		case EEditorMenu::Delete:
			break;
		case EEditorMenu::Load:
			Load(JobInfo);
			break;
		case EEditorMenu::Output:
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
		case EEditorMenu::Exit:
			// 게임이 종료될 때 자동 세이브
			Save(JobInfo);
			return 0;
		}

	}

	return 0;
}