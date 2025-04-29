
#include <iostream>
#include <time.h>

/*
����ü : �پ��� Ÿ���� ������ �ϳ��� ��� ����� �� �ְ� ���ִ� ����� ���� ���� Ÿ�� (�������� ����)

struct ����ü��
{
	���� ����
};

�𸮾������� �������� ������ �ִ� ����ü �̸� �տ� F�� �ٰ�, �������� E�� ����
�� �ٸ� ����ü�� ������ ���� �� ����
��Ư���� ����(����, ������ ��), �������� ��� ����� �� ���� ��
������� Ȱ�� ����..

����ü ������� �� ũ�� ���� ���� �ʼ�***
*/

enum class EPlayerJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion
};

struct FPlayerInfo
{
	char		Name[32] = {};
	EPlayerJob	Job = EPlayerJob::None;
	int			Attack = 0;
	int			Defense = 0;
	int			HP = 0;
	int			HPMax = 0;
	int			MP = 0;
	int			MPMax = 0;
	int			Level = 1;
	int			Exp = 0;
	int			Gold = 0;
};

struct FTest
{
	char		Test1;
};

struct FTest1
{
	int			Test1;
};

struct FTest2
{
	__int64		Test1;
};

struct FTest3
{
	char		Test1;
	char		Test3;
	int			Test2;
};

struct FTest4
{
	// �ƹ��� ������ ���ٸ� 1����Ʈ -> ������ ������ �޸� �Ҵ��� �ؾ� �Ǵµ� 0����Ʈ�� ���� �ȵ� -> �ּҴ����� 1����Ʈ �Ҵ�
	// ����ü, Ŭ���� ��� ��������
};

enum class EItemType : unsigned char
{
	Weapon,
	Armor
};

struct FItem
{
	char		Name[32] = {};
	EItemType	Type = EItemType::Weapon;
	int			Option = 0;
	int			Price = 0;
	int			Sell = 0;
};

void main()
{
	// ����ü ���� �ڿ� = {} �� ���ָ� ����ü ��ü�� 0���� �ʱ�ȭ ��
	FPlayerInfo Info = {};

	FPlayerInfo Info1 = { "Player1" };
	
	// ����ü�� �迭 Ÿ�����ε� ��� ����
	FPlayerInfo InfoArray[10] = {};

	FItem Inventory[20] = {};

	InfoArray[0].Attack = 300;

	// ����ü Ÿ���� ������ .�� �ٿ� ��������� ������ �� ����
	Info.Attack = 500;

	// sizeof(���� Ÿ�� Ȥ�� ����)�� ���ָ� �ش� Ÿ���� ����Ʈ ���� ��ȯ
	// (int) �� ���־� int Ÿ������ ����ȯ ���� -> ����ȯ : ��� �� Ÿ������ �ν� ��Ŵ
	printf("FTest Size : %d\n", (int)sizeof(FTest));

	/*
	// ���ڿ��� ���� �׻� 0���� �Ǿ� �־�� �� -> ���ڿ��� ���� �� 0�� ���� ������ �����
	// �迭�� 32��¥���� ������ 31���� ������ ������ -> ������ �ϳ��� null(0)�� ���� �ϱ� ����
	char Name[32] = {};
	Name[0] = 'a';
	Name[1] = 'b';
	Name[2] = 'c';
	// Name[3] = 0;

	// %s : ���ڿ��� �޾ƿ�
	printf("%s", Name);
	*/


}