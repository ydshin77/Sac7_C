
#include "GameInfo.h"
#include "GameManager.h"

int main()
{
	srand(time(0));
	rand();

	if (GameInit() == false)
	{
		GameDestroy();
		return 0;
	}

	Run();

	GameDestroy();
}
