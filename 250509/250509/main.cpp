
#include <iostream>

struct FPlayer
{
	char	Name[32] = {};
	int		Attack = 0;
};

/*
�ν��Ͻ� : ���� �޸𸮿� �Ҵ�Ǵ� ����
-> Ŭ���� �Ǵ� ����ü�� ������� ������� ��ü

�������̽� : Ŭ������ �����ؾ� �� ���۵��� ���� Ʋ (�Լ� ���� ����)
-> � Ŭ������ �� �������̽��� ����ϸ� �ݵ�� �����ؾ� ��

��ü
: ��� ��ü�� ��ü��� �� �� ����
: ���α׷��ֿ����� Ŭ����, ����ü ���� �̿��Ͽ� ������ ������ ����
-> �޸� �ּҸ� ��� �ִ� ������ ������ ����

��ü���� ���α׷��� (OOP)
: ��ü�� �����Ͽ� �ϳ��� �ϼ��� ���α׷��� ����� ����� ����
: �������� �� �������� ���鿡�� ������, �Ѱ谡 ��Ȯ��

������Ʈ : ��ü�� �ٸ��ֱ� ���� ��ǰ

������Ʈ���� ���α׷���
: ���� �ǰ� �ִ� ���� ��κ��� ���� �������� ���� �� ����� ������
: �𸮾� ������ ��ü���� + ������Ʈ����

Ŭ����
: ��ü���� ���α׷����� �������ֱ� ���� ����
: ��ü�� ����� ���� ������ ��, Ŭ������ ��ü�� �ƴ�

class Ŭ�����̸�
{
	�������
	����Լ�
};

�Ϲ� Ŭ������ ���� ��쿣 Ŭ���� �̸� �տ� C�� ����
�𸮾� �������� A, U. 2������ ����
A : Actor
U : UObject

ĸ��ȭ : ���� ��������� ����Լ��� ����ִ� ����� ������

����ȭ : ����� ���� ������ ������ �� ����

- Ŭ���� ���� : Ŭ������ ����Լ� �� (�ڵ�� ����)
- Ŭ���� �ܺ� : Ŭ������ �ɹ��Լ� ���� �ƴ� ��� ��
- public
: Ŭ���� ���ο� �ܺο� ��� ������
: ����ü�� �ƹ� �͵� �ٿ����� ���� ��� �⺻���� public
- private
: Ŭ���� ���ο����� ������ ����������, �ܺο����� ������ �Ұ�����
: Ŭ������ �ƹ� �͵� �ٿ����� ���� ��� �⺻���� private
- protected : ����� �� �ٽ� ����

��Ӽ� : ����� �� �ٽ� ����
������ : ����� �� �ٽ� ����

Ŭ������ �޸� ũ��� ��������� ũ��� ������
��, ����� ����ϸ鼭 �����Լ��� ����� ��� �ٸ��� ����
����Լ��� Ŭ������ �̿��Ͽ� ������ ��ü�� �޸� ũ�⿡ ������ ���� ����
*/

class CPlayer
{
	/*
	�����ڿ� �Ҹ���
	: Ŭ���� �̸��� ���� �̸��� �Լ���
	: ��ȯ Ÿ�� ���� �̸��� ���ڸ����� ������
	: �����ڴ� �����ε��� ����������, �Ҹ��ڴ� ���� ���� ���¸� ����

	������ : �� Ŭ������ �̿��ؼ� ��ü�� ������ �� �ڵ����� ȣ���� �Ǵ� �Լ�
	�Ҹ��� : �� Ŭ������ �̿��ؼ� ������ ��ü�� �޸𸮿��� ���ŵ� �� �ڵ����� ȣ���� �Ǵ� �Լ�
	*/

public:
	// ������
	// �̴ϼȶ������� �̿��ؼ� ��������� ���� ����� ���ÿ� �ʱ�ȭ�� �� ����
	CPlayer() :
		mAttack(20),
		mDefense(10),
		mName("apple")
	{
		// �Ʒ��� mAttack ������ ������ �� �Ŀ� 50�� ������
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

	/*
	* �߿�!
	��������� -> �ӽð�ü ���� �Ұ�
	: �ٸ� ��ü�� ������ ���ο� ��ü�� ���� �� �����
	: �������� ���ڷ� const Ŭ����Ÿ��& Ÿ���� �����

	���� ����� ��������, �������� 2������ ����
	�������� : Ŭ������ �����͸� �״�� ������
	��������(deep copy) : Ŭ������ �����Ҵ�� �����Ͱ� ���� ��� �Ȱ��� ũ���� ������ ������ְ� �����͸� �����ϴ� ���
	: �Ϲ� �����ʹ� ��������� ���� �״�� ������

	�̵������� -> �ӽð�ü ���� ����
	: �ٸ� ��ü�� ������ �ִ� ������ ���ο� ��ü�� �Ű��ָ鼭 ��ü�� ���� �� �����
	: Ŭ����Ÿ��&&

	&&
	: ���� Ÿ�Կ� && �� ������ rvalue reference (������ ����)��� ��
	: �ӽð��� ������ �� �ְ� ���ִ� Ÿ��
	*/

	CPlayer(const CPlayer& Ref)// :
		//mAttack(Ref.mAttack),
		//mDefense(Ref.mDefense)
		//mName(Ref.mName) -> mName�� const char* Ÿ���̶� �ȵ�
	{
		// ��� ��������� ���� �״�� ������
		// �������簡 �Ͼ
		*this = Ref;
	}

	// �Ҹ���
	~CPlayer()
	{
		printf("CPlayer �Ҹ���\n");
	}

public:
	// �� �Ʒ��� �ٸ� �������� Ű���带 ������ ������ ��� public�� ��

	// Ŭ������ ��������� m�� ���� -> ���������� ���̹� �浹 ����
	char	mName[32] = {};
	int		mAttack = 0;

private:
	int		mDefense = 0;

public:
	// Ŭ������ �Ϲ� ����Լ� ����(�Ϲݸ���Լ�, ������, �Ҹ���)������ this�� ����� �� ����
	// this�� �ڱ� �ڽ��� �޸� �ּ�
	// Player1.Output() �̷� ������ Ŭ������ ����Լ��� ȣ���� ���� ��ü�� �̿��ؼ� ȣ���ϰ� ��
	// Player1.Output()���� ȣ���ϸ� ȣ���ϴ� ���� this�� Player1�� �ּҸ� ������ ��
	// Pleyer2.Output()���� ȣ���ϸ� ȣ���ϴ� ���� this�� Player2�� �ּҸ� ������ ��
	// ����Լ� ���ο��� Ŭ���� ��������� ����ϰ� �Ǹ� �տ� this-> ǥ�ð� �����Ȱ�
	void Output()
	{
		printf("Name = %s\n", mName);
		printf("this = %p\n", this);
		printf("���ݷ� : %d\n", mAttack);
		printf("���� : %d\n", this->mDefense);
		// this�� ������ �ƴϱ� ������ this�� �ּҸ� ����ϴ� ���� �Ұ���
		// printf("this Addr = %p\n", &this);
	}

	void OutputTest()
	{
		printf("OutputTest Function\n");
	}
};

class CCopyTest
{
public:
	CCopyTest()
	{
		mArray = new int[10];

		// �޸𸮸� ���ϴ� ������ ä���� �� ���
		// ��, ä��� ������ ����Ʈ ������ ���� ä����
		// * �߿�
		// 1�������� �޸𸮸� 2�������� ������ 3�������� ũ�⸸ŭ ä����
		memset(mArray, 0, sizeof(int) * 10);
		printf("CCopyTest ������\n");
	}

	CCopyTest(const CCopyTest& Ref)
	{
		//*this = Ref;
		mNumber = Ref.mNumber;
		printf("CCopyTest ���������\n");

		// �����Ҵ�� �����͸� �Ҹ��ڿ��� �����ϰ� �����Ƿ� ���� ���縦 �̿��ؼ� ó����
		mArray = new int[10];
		
		
		// �޸𸮸� ������ �� ���. memory copy
		// 1�������� �ּҿ� 2�������� �ּҷκ��� 3�����ڿ� ���� ����Ʈ ����ŭ�� ��������
		memcpy(mArray, Ref.mArray, sizeof(int) * 10);

		/*for (int i = 0; i < 10; ++i)
		{
			mArray[i] = Ref.mArray[i];
		}*/
	}

	// �̵� ������
	CCopyTest(CCopyTest&& Ref)
	{
		printf("CCopyTest �̵�������\n");
		mNumber = Ref.mNumber;
		mArray = Ref.mArray;
		Ref.mArray = nullptr;
	}

	~CCopyTest()
	{
		// �Ҹ��ڿ����� ��ü�� ������ �۾�
		printf("CCopyTest �Ҹ���\n");
		if (mArray != nullptr)
			delete[] mArray;
	}

public:
	int	mNumber = 0;
	int* mArray = nullptr;
};

void OutputPlayer(FPlayer* Player)
{
	printf("���ݷ� : %d\n", Player->Attack);
}

void TestRValue(CCopyTest Copy)
{

}

int main()
{
	//// Player�� FPlayer ����ü�� �ν��Ͻ�
	//FPlayer Player;
	//Player.Attack = 10;

	//OutputPlayer(&Player);

	//CPlayer Player1, Player2("�̸�");

	//printf("Player1 = %p\n", &Player1);
	//printf("Player2 = %p\n", &Player2);

	//// Output ����Լ��� Player1�� Player2 ��� ������ �ּ��� �Լ��� ����ϰ� ��
	//// �׷��� ����Լ����� ��Ȯ�ϰ� Player1�� Player2�� ��������� ���� �ν��ϰ� ����� �� ����
	//Player1.mAttack = 100;
	//Player1.Output();

	//// ��������� ��ȣ��
	//CPlayer PlayerCopy(Player1);

	//Player2.mAttack = 300;
	//Player2.Output();

	//CPlayer* Player3 = nullptr;
	//// *�߿�!
	//// �����߻�
	////Player3->Output();
	//// nullptr�� ��������, ��������� ������ ���ϱ� ������ ������ �߻����� ����
	//Player3->OutputTest();

	//// printf("Player Size = %d\n", sizeof(CPlayer));

	//// Number�� lvalue
	//int Number = 10;

	//// Number + 10 : rvalue
	//// Number + 10�� �� ����� �����ϱ� ���� �ӽ� �������(��������)�� �����
	//// �ű⿡ ����� ������ �Ŀ� lvalue(Result)�� �������� -> �����ϰ� ��ȯ
	//int Result = Number + 10;

	//// �ӽ� �������ʹ� ������ ��ȯ�ؾ� �Ǳ� ������ ������ �Ұ���
	//// int& Ref = Number + 10;
	//
	//// rvalue ���� ����
	//int&& Ref = Number + 10;

	//// CPlayer Player4 = CPlayer();

	//system("cls");

	//CCopyTest Test;
	//CCopyTest TestCopy(Test);


	//// 1����Ʈ ������ ���� ä��� ��
	//// int�� 4����Ʈ �̹Ƿ� 1����Ʈ ������ 1�� ä��� �Ǹ�
	//// 0000 0001 0000 0001 0000 0001 0000 0001
	//memset(&Number, 0, sizeof(int));
	//printf("Number = %d\n", Number);

	system("cls");

	//CCopyTest	Test1(CCopyTest());
	//TestRValue(CCopyTest());
	CCopyTest	Test1 = std::move(CCopyTest());
	//CCopyTest	Test2 = std::move(Test1);

	printf("-----------------\n");

	return 0;
}