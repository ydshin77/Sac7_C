
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

	// �޸𸮸� �����Ѵ�.
	//delete Num;

	// Num�� ������ ���� �޸� �ּҸ� �״�� ������ �ִ�.
	// �׷��Ƿ� �Ʒ��� ���� �޸𸮸� �ٽ� ����� �ȴ�.
	// ������ �޸��� �ּҸ� ������ �ִ� �����͸� ��۸� �����Ͷ�� �Ѵ�.
	//delete Num;

	Output();

	return 0;
}
