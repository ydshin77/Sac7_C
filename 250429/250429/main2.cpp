
#include <iostream>
#include <time.h>

/*
구조체 : 다양한 타입의 변수를 하나로 묶어서 사용할 수 있게 해주는 사용자 정의 변수 타입 (열거형과 유사)

struct 구조체명
{
	변수 선언
};

언리얼엔진에선 정보들을 가지고 있는 구조체 이름 앞에 F가 붙고, 열거형은 E가 붙음
또 다른 구조체도 변수로 가질 수 있음
불특정한 모임(몬스터, 아이템 등), 정보들을 묶어서 사용할 때 자주 씀
멤버변수 활용 가능..

구조체 멤버맞춤 및 크기 내용 숙지 필수***
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
	// 아무런 변수도 없다면 1바이트 -> 선언을 했으니 메모리 할당을 해야 되는데 0바이트는 말이 안됨 -> 최소단위인 1바이트 할당
	// 구조체, 클래스 모두 마찬가지
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
	// 구조체 선언 뒤에 = {} 을 해주면 구조체 전체를 0으로 초기화 함
	FPlayerInfo Info = {};

	FPlayerInfo Info1 = { "Player1" };
	
	// 구조체를 배열 타입으로도 사용 가능
	FPlayerInfo InfoArray[10] = {};

	FItem Inventory[20] = {};

	InfoArray[0].Attack = 300;

	// 구조체 타입의 변수에 .을 붙여 멤버변수에 접근할 수 있음
	Info.Attack = 500;

	// sizeof(변수 타입 혹은 변수)를 해주면 해당 타입의 바이트 수를 반환
	// (int) 를 해주어 int 타입으로 형변환 해줌 -> 형변환 : 잠깐 이 타입으로 인식 시킴
	printf("FTest Size : %d\n", (int)sizeof(FTest));

	/*
	// 문자열의 끝은 항상 0으로 되어 있어야 함 -> 문자열을 읽을 땐 0이 나올 때까지 출력함
	// 배열이 32개짜리면 실제로 31개만 저장이 가능함 -> 마지막 하나는 null(0)이 들어가야 하기 때문
	char Name[32] = {};
	Name[0] = 'a';
	Name[1] = 'b';
	Name[2] = 'c';
	// Name[3] = 0;

	// %s : 문자열을 받아옴
	printf("%s", Name);
	*/


}