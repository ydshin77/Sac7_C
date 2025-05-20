#include <iostream>

class CPlayer
{
public:
	// 생성자
	CPlayer() :
		// 이니셜라이저 사용 (선언과 동시에 초기화)
		mAttack(10),
		mDefense(20)
	{
		// mAttack 변수가 선언이 된 후 50 대입
		mAttack = 50;
		printf("CPlayer 생성자\n");
	}
	// 생성자 오버로딩
	CPlayer(const char* Name) :
		mAttack(30),
		mDefense(40)
	{
		printf("CPlayer const char* 생성자\n");
	}
	// 소멸자
	~CPlayer()
	{
		printf("CPlayer 소멸자\n");
	}

public:
	char	mName[32] = {};
	int		mAttack = 0;

private:
	int		mDefense = 0;

public:
	void Output()
	{
		printf("공격력 : %d\n", mAttack);
	}
};

int main()
{
	CPlayer Player1, Player2("이름");
	
	Player1.mAttack = 20;
	// 출력 : 20
	Player1.Output();

	Player2.mAttack = 300;
	// 출력 : 300
	Player2.Output();

	printf("Player Size = %d\n", sizeof(CPlayer));

	return 0;
}