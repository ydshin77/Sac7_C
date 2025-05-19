
#include "GameInfo.h"
#include "GameManager.h"

int main()
{
	// ���� �ʱ�ȭ
	srand(time(0));
	rand();

	// ���� �ʱ�ȭ�� ���������� ���� ����
	if (!GameInit())
	{
		GameDestroy();
		return 0;
	}

	// ���� �ʱ�ȭ�� ���������� ���� ����
	Run();

	GameDestroy();

	return 0;
}