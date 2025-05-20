#include "MazeManager.h"
#include "Maze.h"

CMazeManager* CMazeManager::mInst = nullptr;

CMazeManager::CMazeManager()
{
}

CMazeManager::~CMazeManager()
{
}

CMaze* CMazeManager::CloneMaze(int Index)
{
	return mMazeList[Index]->Clone();
}

int CMazeManager::GetTileCount(int Index) const
{
	return mMazeList[Index]->GetCount();
}

int CMazeManager::GetTileOutputCount(int Index) const
{
	return mMazeList[Index]->GetOutputCount();
}

int CMazeManager::GetCountY(int Index) const
{
	return mMazeList[Index]->GetCountY();
}

bool CMazeManager::Init()
{
	// �̷� ����Ʈ ������ �о�´�.
	FILE* File = nullptr;

	fopen_s(&File, "MazeList.txt", "rt");

	if (!File)
		return false;

	char	Line[128] = {};

	fgets(Line, 128, File);

	int	MazeCount = atoi(Line);

	for (int i = 0; i < MazeCount; ++i)
	{
		fgets(Line, 128, File);

		// �о�� ���� �̸��� �������� ���๮���� ��� 0����
		// ä���ش�.
		int	Length = strlen(Line);

		if (Line[Length - 1] == '\n')
			Line[Length - 1] = 0;

		// �̷� ����
		CMaze* Maze = new CMaze;

		if (!Maze->Init(Line))
		{
			SAFE_DELETE(Maze);
			return false;
		}

		mMazeList.push_back(Maze);
	}

	fclose(File);

	return true;
}

int CMazeManager::OutputMenu()
{
	system("cls");
	// vector�� �߰��� ��
	size_t Size = mMazeList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		printf("%d. %s\n", (int)(i + 1), mMazeList[i]->GetName());
	}

	printf("%d. ����\n", (int)(Size + 1));

	int	Input = 0;
	printf("�̷θ� �����ϼ��� : ");
	scanf_s("%d", &Input);

	if (Input <= 0 || Input > Size + 1)
		return 0;

	return Input;
}

void CMazeManager::OutputMaze(int Index, char* Buffer)
{
	mMazeList[Index]->Output(Buffer);
}

CMazeManager* CMazeManager::GetInst()
{
	if (!mInst)
		mInst = new CMazeManager;

	return mInst;
}

void CMazeManager::DestroyInst()
{
	SAFE_DELETE(mInst);
}
