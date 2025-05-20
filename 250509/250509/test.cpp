#include <iostream>

class CPlayer
{
public:
	// ������
	CPlayer() :
		// �̴ϼȶ����� ��� (����� ���ÿ� �ʱ�ȭ)
		mAttack(10),
		mDefense(20)
	{
		// mAttack ������ ������ �� �� 50 ����
		mAttack = 50;
		printf("CPlayer ������\n");
	}
	// ������ �����ε�
	CPlayer(const char* Name) :
		mAttack(30),
		mDefense(40)
	{
		printf("CPlayer const char* ������\n");
	}
	// �Ҹ���
	~CPlayer()
	{
		printf("CPlayer �Ҹ���\n");
	}

public:
	char	mName[32] = {};
	int		mAttack = 0;

private:
	int		mDefense = 0;

public:
	void Output()
	{
		printf("���ݷ� : %d\n", mAttack);
	}
};

int main()
{
	CPlayer Player1, Player2("�̸�");
	
	Player1.mAttack = 20;
	// ��� : 20
	Player1.Output();

	Player2.mAttack = 300;
	// ��� : 300
	Player2.Output();

	printf("Player Size = %d\n", sizeof(CPlayer));

	return 0;
}