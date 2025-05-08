
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
	printf("1. ���\n");
	printf("2. �ü�\n");
	printf("3. ������\n");
	printf("������ ������ �����ϼ��� : ");
	int		Input;
	scanf_s("%d", &Input);

	if (Input <= 0 || Input >= 4)
		return;

	int	Index = Input - 1;

	printf("���ݷ� : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("���� : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("ü�� : ");
	scanf_s("%d", &Info[Index].HP);

	printf("���� : ");
	scanf_s("%d", &Info[Index].MP);

	Save(Info);
}

int main()
{
	FPlayerEditorInfo	JobInfo[3] = {};


	while (true)
	{
		system("cls");
		printf("1. ��������\n");
		printf("2. ��������\n");
		printf("3. �ҷ�����\n");
		printf("4. ���\n");
		printf("5. ����\n");
		printf("�޴��� �����ϼ��� : ");
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
				printf("���ݷ� : %d\n", JobInfo[i].Attack);
				printf("���� : %d\n", JobInfo[i].Defense);
				printf("ü�� : %d\n", JobInfo[i].HP);
				printf("���� : %d\n", JobInfo[i].MP);
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