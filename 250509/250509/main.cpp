
#include <iostream>

struct FPlayer
{
	char	Name[32] = {};
	int		Attack = 0;
};

/*
인스턴스 : 실제 메모리에 할당되는 변수
-> 클래스 또는 구조체를 기반으로 만들어진 실체

인터페이스 : 클래스가 구현해야 할 동작들을 명세한 틀 (함수 선언만 존재)
-> 어떤 클래스가 이 인터페이스를 상속하면 반드시 구현해야 함

객체
: 모든 물체를 객체라고 할 수 있음
: 프로그래밍에서는 클래스, 구조체 등을 이용하여 생성한 변수를 말함
-> 메모리 주소를 담고 있는 포인터 변수는 제외

객체지향 프로그래밍 (OOP)
: 객체를 조립하여 하나의 완성된 프로그램을 만드는 방식을 말함
: 유지보수 및 관리적인 측면에선 좋으나, 한계가 명확함

컴포넌트 : 객체를 꾸며주기 위한 부품

컴포넌트지향 프로그래밍
: 서비스 되고 있는 거의 대부분의 게임 엔진들은 보통 이 방법을 지원함
: 언리얼 엔진도 객체지향 + 컴포넌트지향

클래스
: 객체지향 프로그래밍을 지원해주기 위한 수단
: 객체를 만들기 위한 수단일 뿐, 클래스가 객체는 아님

class 클래스이름
{
	멤버변수
	멤버함수
};

일반 클래스를 만들 경우엔 클래스 이름 앞에 C를 붙임
언리얼 엔진에선 A, U. 2가지를 붙임
A : Actor
U : UObject

캡슐화 : 여러 멤버변수나 멤버함수를 모아주는 기능을 제공함

은닉화 : 멤버의 공개 수준을 설정할 수 있음

- 클래스 내부 : 클래스의 멤버함수 안 (코드블럭 내부)
- 클래스 외부 : 클래스의 맴버함수 안이 아닌 모든 곳
- public
: 클래스 내부와 외부에 모두 공개함
: 구조체는 아무 것도 붙여주지 않을 경우 기본으로 public
- private
: 클래스 내부에서는 접근이 가능하지만, 외부에서는 접근이 불가능함
: 클래스는 아무 것도 붙여주지 않을 경우 기본으로 private
- protected : 상속할 때 다시 설명

상속성 : 상속할 때 다시 설명
다형성 : 상속할 때 다시 설명

클래스의 메모리 크기는 멤버변수의 크기와 동일함
단, 상속을 사용하면서 가상함수를 사용할 경우 다르게 나옴
멤버함수는 클래스를 이용하여 생성한 객체의 메모리 크기에 영향을 주지 않음
*/

class CPlayer
{
	/*
	생성자와 소멸자
	: 클래스 이름과 같은 이름의 함수임
	: 반환 타입 없이 이름과 인자만으로 선언함
	: 생성자는 오버로딩이 가능하지만, 소멸자는 인자 없는 형태만 존재

	생성자 : 이 클래스를 이용해서 객체를 생성할 때 자동으로 호출이 되는 함수
	소멸자 : 이 클래스를 이용해서 생선한 객체가 메모리에서 제거될 때 자동으로 호출이 되는 함수
	*/

public:
	// 생성자
	// 이니셜라이저를 이용해서 멤버변수의 값을 선언과 동시에 초기화할 수 있음
	CPlayer() :
		mAttack(20),
		mDefense(10),
		mName("apple")
	{
		// 아래는 mAttack 변수가 선언이 된 후에 50을 대입함
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

	/*
	* 중요!
	복사생성자 -> 임시객체 참조 불가
	: 다른 객체를 복사한 새로운 객체를 만들 때 사용함
	: 생성자의 인자로 const 클래스타입& 타입을 사용함

	복사 방법은 얕은복사, 깊은복사 2가지가 있음
	얕은복사 : 클래스의 데이터를 그대로 복사함
	깊은복사(deep copy) : 클래스에 동적할당된 데이터가 있을 경우 똑같은 크기의 공간을 만들어주고 데이터만 복사하는 방식
	: 일반 데이터는 얕은복사와 같이 그대로 복사함

	이동생성자 -> 임시객체 참조 가능
	: 다른 객체가 가지고 있는 내용을 새로운 객체로 옮겨주면서 객체를 만들 때 사용함
	: 클래스타입&&

	&&
	: 변수 타입에 && 가 붙으면 rvalue reference (우측값 참조)라고 함
	: 임시값을 참조할 수 있게 해주는 타입
	*/

	CPlayer(const CPlayer& Ref)// :
		//mAttack(Ref.mAttack),
		//mDefense(Ref.mDefense)
		//mName(Ref.mName) -> mName은 const char* 타입이라 안됨
	{
		// 모든 멤버변수의 값을 그대로 복사함
		// 얕은복사가 일어남
		*this = Ref;
	}

	// 소멸자
	~CPlayer()
	{
		printf("CPlayer 소멸자\n");
	}

public:
	// 이 아래로 다른 접근제어 키워드를 만나기 전까진 모두 public이 됨

	// 클래스의 멤버변수엔 m을 붙임 -> 지역변수와 네이밍 충돌 방지
	char	mName[32] = {};
	int		mAttack = 0;

private:
	int		mDefense = 0;

public:
	// 클래스의 일반 멤버함수 내부(일반멤버함수, 생성자, 소멸자)에서는 this를 사용할 수 있음
	// this는 자기 자신의 메모리 주소
	// Player1.Output() 이런 식으로 클래스의 멤버함수를 호출할 때는 객체를 이용해서 호출하게 됨
	// Player1.Output()으로 호출하면 호출하는 순간 this는 Player1의 주소를 가지게 됨
	// Pleyer2.Output()으로 호출하면 호출하는 순간 this는 Player2의 주소를 가지게 됨
	// 멤버함수 내부에서 클래스 멤버변수를 사용하게 되면 앞에 this-> 표시가 생략된것
	void Output()
	{
		printf("Name = %s\n", mName);
		printf("this = %p\n", this);
		printf("공격력 : %d\n", mAttack);
		printf("방어력 : %d\n", this->mDefense);
		// this는 변수가 아니기 때문에 this의 주소를 출력하는 것은 불가함
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

		// 메모리를 원하는 값으로 채워줄 때 사용
		// 단, 채우는 단위는 바이트 단위로 값을 채워줌
		// * 중요
		// 1번인자의 메모리를 2번인자의 값으로 3번인자의 크기만큼 채워줌
		memset(mArray, 0, sizeof(int) * 10);
		printf("CCopyTest 생성자\n");
	}

	CCopyTest(const CCopyTest& Ref)
	{
		//*this = Ref;
		mNumber = Ref.mNumber;
		printf("CCopyTest 복사생성자\n");

		// 동적할당된 데이터를 소멸자에서 제거하고 있으므로 깊은 복사를 이용해서 처리함
		mArray = new int[10];
		
		
		// 메모리를 복사할 때 사용. memory copy
		// 1번인자의 주소에 2번인자의 주소로부터 3번인자에 들어가는 바이트 수만큼을 복사해줌
		memcpy(mArray, Ref.mArray, sizeof(int) * 10);

		/*for (int i = 0; i < 10; ++i)
		{
			mArray[i] = Ref.mArray[i];
		}*/
	}

	// 이동 생성자
	CCopyTest(CCopyTest&& Ref)
	{
		printf("CCopyTest 이동생성자\n");
		mNumber = Ref.mNumber;
		mArray = Ref.mArray;
		Ref.mArray = nullptr;
	}

	~CCopyTest()
	{
		// 소멸자에서는 객체의 마무리 작업
		printf("CCopyTest 소멸자\n");
		if (mArray != nullptr)
			delete[] mArray;
	}

public:
	int	mNumber = 0;
	int* mArray = nullptr;
};

void OutputPlayer(FPlayer* Player)
{
	printf("공격력 : %d\n", Player->Attack);
}

void TestRValue(CCopyTest Copy)
{

}

int main()
{
	//// Player는 FPlayer 구조체의 인스턴스
	//FPlayer Player;
	//Player.Attack = 10;

	//OutputPlayer(&Player);

	//CPlayer Player1, Player2("이름");

	//printf("Player1 = %p\n", &Player1);
	//printf("Player2 = %p\n", &Player2);

	//// Output 멤버함수는 Player1과 Player2 모두 동일한 주소의 함수를 사용하게 됨
	//// 그런데 멤버함수에서 정확하게 Player1과 Player2의 멤버변수의 값을 인식하고 사용할 수 있음
	//Player1.mAttack = 100;
	//Player1.Output();

	//// 복사생성자 ㅣ호출
	//CPlayer PlayerCopy(Player1);

	//Player2.mAttack = 300;
	//Player2.Output();

	//CPlayer* Player3 = nullptr;
	//// *중요!
	//// 에러발생
	////Player3->Output();
	//// nullptr이 들어가있지만, 멤버변수에 접근을 안하기 때문에 에러가 발생하지 않음
	//Player3->OutputTest();

	//// printf("Player Size = %d\n", sizeof(CPlayer));

	//// Number는 lvalue
	//int Number = 10;

	//// Number + 10 : rvalue
	//// Number + 10을 한 결과를 저장하기 위한 임시 저장공간(레지스터)을 만들고
	//// 거기에 결과를 저장한 후에 lvalue(Result)에 대입해줌 -> 참조하고 반환
	//int Result = Number + 10;

	//// 임시 레지스터는 끝나면 반환해야 되기 때문에 참조가 불가함
	//// int& Ref = Number + 10;
	//
	//// rvalue 참조 가능
	//int&& Ref = Number + 10;

	//// CPlayer Player4 = CPlayer();

	//system("cls");

	//CCopyTest Test;
	//CCopyTest TestCopy(Test);


	//// 1바이트 단위로 값을 채우게 됨
	//// int는 4바이트 이므로 1바이트 단위로 1을 채우게 되면
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