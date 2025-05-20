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
	// 미로 리스트 파일을 읽어온다.
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

		// 읽어온 파일 이름의 마지막이 개행문자일 경우 0으로
		// 채워준다.
		int	Length = strlen(Line);

		if (Line[Length - 1] == '\n')
			Line[Length - 1] = 0;

		// 미로 생성
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
	// vector에 추가된 수
	size_t Size = mMazeList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		printf("%d. %s\n", (int)(i + 1), mMazeList[i]->GetName());
	}

	printf("%d. 종료\n", (int)(Size + 1));

	int	Input = 0;
	printf("미로를 선택하세요 : ");
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
