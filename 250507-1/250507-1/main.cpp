
#include "GameInfo.h"
#include "GameManager.h"

int main()
{
	// 게임 초기화에 실패했으면 게임 종료
	if (!GameInit())
	{
		GameDestroy();
		return 0;
	}

	// 게임 초기화에 성공했으면 게임 실행
	Run();

	GameDestroy();

	return 0;
}