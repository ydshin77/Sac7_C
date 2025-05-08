
#include <iostream>
#include "GameInfo.h"

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

void Save(FPlayerEditorInfo* Info)
{
	FILE* File = nullptr;

	fopen_s(&File, "PlayerInfo.pli", "wb");

	if (!File)
		return;

	fwrite(Info, sizeof(FPlayerEditorInfo), 3, File);

	fclose(File);
}

void Load(FPlayerEditorInfo* Info)
{
	FILE* File = nullptr;

	fopen_s(&File, "PlayerInfo.pli", "rb");

	if (!File)
		return;

	fread(Info, sizeof(FPlayerEditorInfo), 3, File);

	fclose(File);
}

void Modify(FPlayerEditorInfo* Info)
{
	printf("1. 기사\n");
	printf("2. 궁수\n");
	printf("3. 마법사\n");
	printf("수정할 직업을 선택하세요 : ");
	int		Input;
	scanf_s("%d", &Input);

	if (Input <= 0 || Input >= 4)
		return;

	int	Index = Input - 1;

	printf("공격력 : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("방어력 : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("체력 : ");
	scanf_s("%d", &Info[Index].HP);

	printf("마나 : ");
	scanf_s("%d", &Info[Index].MP);

	Save(Info);
}

int main()
{
	FPlayerEditorInfo	JobInfo[3] = {};


	while (true)
	{
		system("cls");
		printf("1. 직업수정\n");
		printf("2. 직업삭제\n");
		printf("3. 불러오기\n");
		printf("4. 출력\n");
		printf("5. 종료\n");
		printf("메뉴를 선택하세요 : ");
		int	Input = 0;
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
			}

			system("pause");
			break;
		case EEditorMenu::Exit:
			Save(JobInfo);
			return 0;
		}
	}

	return 0;
}