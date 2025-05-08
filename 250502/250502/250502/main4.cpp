
#include "GameInfo.h"
#include "TestFunction.h"
#include "GameManager.h"

int main()
{
	if (GameInit() == false)
	{
		GameDestroy();
		return 0;
	}

	Run();

	GameDestroy();

	/*int* Num = new int;

	if (Num) { delete Num; Num = nullptr; }
	SAFE_DELETE(Num);

	if (Num) { delete Num; Num = nullptr; }
	SAFE_DELETE(Num);*/

	// 메모리를 제거한다.
	//delete Num;

	// Num은 위에서 지운 메모리 주소를 그대로 가지고 있다.
	// 그러므로 아래는 지운 메모리를 다시 지우게 된다.
	// 지원진 메모리의 주소를 가지고 있는 포인터를 댕글링 포인터라고 한다.
	//delete Num;

	Output();

	return 0;
}
