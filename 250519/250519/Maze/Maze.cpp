#include "Maze.h"

CMaze::CMaze()
{
}

CMaze::CMaze(const CMaze& Copy)
{
	*this = Copy;
}

CMaze::~CMaze()
{
}

bool CMaze::Init(const char* FileName)
{
	FILE* File = nullptr;

	fopen_s(&File, FileName, "rt");


	if (!File)
		return false;

	char	Line[256] = {};

	fgets(Line, 256, File);

	char* Context = nullptr;

	char* Result = strtok_s(Line, ",", &Context);

	mCountX = atoi(Result);
	mCountY = atoi(Context);

	// reserve : 동적배열의 크기를 원하는 크기만큼 생성해둔다.
	mTileList.reserve(mCountX * mCountY + mCountY);

	for (int i = 0; i < mCountY; ++i)
	{
		fgets(Line, 256, File);

		for (int j = 0; j < mCountX; ++j)
		{
			mTileList.push_back((ETileType)Line[j]);

			switch ((ETileType)Line[j])
			{
			case ETileType::Road:
				mTileOutputList.push_back(' ');
				break;
			case ETileType::Wall:
				mTileOutputList.push_back('*');
				break;
			case ETileType::Start:
				mTileOutputList.push_back('!');
				break;
			case ETileType::Exit:
				mTileOutputList.push_back('#');
				break;
			}
		}

		mTileOutputList.push_back('\n');
	}

	fclose(File);

	strcpy_s(mName, FileName);

	Result = strtok_s(mName, ".", &Context);

	return true;
}

void CMaze::Output(char* Buffer)
{
	memcpy(Buffer, &mTileOutputList[0], mCountX * mCountY + mCountY);
}

CMaze* CMaze::Clone()
{
	return new CMaze(*this);
}
