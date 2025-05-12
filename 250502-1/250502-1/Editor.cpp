
#include <iostream>
#include "GameInfo.h"

// ������ ���� �÷��̾� �⺻ ���� ����
// ���� ���� ���� �� �׽�Ʈ�� �� �ֵ���, ���� �����ʹ� ���Ͽ� ������

// Editor �޴�
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

// ���� ���� �Լ�
void Save(FPlayerEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "PlayerInfo.pli", "wb");

	if (!FileStream)
		return;

	fwrite(Info, sizeof(FPlayerEditorInfo), 3, FileStream);

	fclose(FileStream);
}

// ���� �б� �Լ�
void Load(FPlayerEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "PlayerInfo.pli", "rb");

	if (!FileStream)
		return;

	fread(Info, sizeof(FPlayerEditorInfo), 3, FileStream);

	fclose(FileStream);
}

// ���� ���� �Լ�
void Modify(FPlayerEditorInfo* Info)
{
	// ���� ����
	printf("1. ���\n");
	printf("2. �ü�\n");
	printf("3. ������\n");

	printf("������ ������ �����ϼ��� : ");
	int Input = 0;
	scanf_s("%d", &Input);

	if (Input <= 0 || Input >= 4)
		return;

	// �ɷ�ġ ����
	int Index = Input - 1;

	printf("���ݷ� : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("���� : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("ü�� : ");
	scanf_s("%d", &Info[Index].HP);

	printf("���� : ");
	scanf_s("%d", &Info[Index].MP);

	// �Է��� ������ ���Ͽ� ����
	Save(Info);
}

int main()
{
	// 3�� ���� (���, �ü�, ������)
	FPlayerEditorInfo JobInfo[3] = {};

	while (true)
	{
		system("cls");

		printf("1. ���� ����\n");
		printf("2. ���� ����\n");
		printf("3. �ҷ�����\n");
		printf("4. ���\n");
		printf("5. ����\n");

		printf("�޴��� �����ϼ��� : ");
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
				printf("���ݷ� : %d\n", JobInfo[i].Attack);
				printf("���� : %d\n", JobInfo[i].Defense);
				printf("ü�� : %d\n", JobInfo[i].HP);
				printf("���� : %d\n", JobInfo[i].MP);
				printf("==============\n");
			}
			system("pause");
			break;
		case EEditorMenu::Exit:
			// ������ ����� �� �ڵ� ���̺�
			Save(JobInfo);
			return 0;
		}

	}

	return 0;
}