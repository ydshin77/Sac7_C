
#include <iostream>
// RTTI를 이용해 타입을 가지고 올 수 있게 하는 헤더
#include <typeinfo>

/*
- 상속
클래스는 부모와 자식의 관계를 형성할 수 있음
자식 클래스는 부모 클래스의 멤버를 포함하여 생성하게 됨

다중 상속 가능 (여러 개의 클래스)
부모 클래스의 자식 클래스를 상속받을 수 있음

- 상속 구조에서 생성자와 소멸자의 호출 순서 (꼭 암기!!)
생성자 : 부모 -> 자식
소멸자 : 자식 -> 부모

: 뒤에 접근지정자 사용 가능 (public, private, protected)
private 상속을 받게 되면 클래스 외부에서는 부모의 멤버에 접근 불가능, 내부에서는 접근 가능

- private
: 클래스 외부에서 접근 불가능, 클래스 내부에서는 접근 가능
: 자식 클래스의 내부에서도 접근이 불가능

- protected
: 클래스 외부에서 접근 불가능, 클래스 내부에서는 접근 가능
: 자식클래스의 내부에서는 접근 가능 (private과의 차이점)

- RTTI(Run Time Type Information)
: 실시간으로 타입 정보를 얻을 수 있게 해주는 기능

- 다형성
: 상속 관계에 있는 클래스 사이에 서로 형변환이 가능한 성질을 말함

- 업캐스팅
: 자식 -> 부모 형변환

- 다운캐스팅
: 부모 -> 자식 형변환
: 메모리 용량 관련으로 다운캐스팅 사용시 주의해야함

- 상속의 장점
: 클래스의 재사용성이 좋아짐
	> 공통적인 멤버를 부모에 두고, 각 자식의 특징만 자식 클래스의 멤버로 만들어서 사용
: 다형성을 이용하여 부모 타입으로의 형변환이 가능하기 때문에,
  부모 타입을 관리하는 하나의 목록으로 여러 자식 클래스의 객체들을 관리할 수 있음
	 
*/

class CParent
{
public:
	CParent()
	{
		printf("CParent 생성자\n");
	}

	/*
	- 가상함수 (어떤 원리로 동작하는지 꼭 알기!!)
	소멸자나 일반 클래스 멤버함수 앞에 virtual 키워드를 붙여주면 해당 함수는 가상함수가 됨
	가상함수를 가지고 있는 클래스는 가상함수테이블을 가지게 됨
	부모에 가상함수가 있는 자식클래스도 가상함수테이블을 가지게 됨
	클래스별 가상함수테이블이 생성됨
	가상함수를 가지고 있는 클래스를 이용해서 객체를 생성하면
	__vfptr 이라는 포인터 변수를 자동으로 가지게 됨
	이 포인터 변수는 해당 클래스의 가상함수테이블의 메모리 주소를 가지게 됨
	
	가상함수 테이블은 가상함수의 주소를 담고 있음
	가상함수를 호출하게 되면 먼저 해당 함수의 주소를 가상함수테이블을 참조하여 얻어오고,
	그 주소를 이용하여 함수를 호출해주는 방식임
	
	다형성, 가상함수, 다이나믹캐스트 > 시험/면접문제필수!!
	왜호출되느냐, vfptr이 왜있느냐

	빈 클래스 1바이트 , 가상함수가 있는 클래스 8바이트 > 이거도 필수!!
	*/
	~CParent()
	{
		printf("CParent 소멸자\n");
	}

public:
	int mA = 10;
	
private:
	int mB = 20;
	
protected:
	int mZ = 30;

public:
	virtual void Output()
	{
		mZ = 1123;
		printf("CParent Output Function\n");
	}

	virtual void OutputOverride()
	{
	}

	// 추상클래스 : 순수가상함수를 가지고 있는 클래스를 추상클래스 라고 한다.
	// 추상클래스는 객체 생성이 불가능하다.
	// 만약 순수가상함수를 가지고 있는 클래스를 상속받는 자식클래스에서 순수가상함수의
	// 재정의가 없다면 자식클래스도 추상클래스가 된다.
	// 순수가상함수는 자식클래스에서 무조건 재정의 해야 한다.
	virtual void OutputPure() = 0;
	// 함수 뒤에 abstract를 붙여서 순수가상함수를 만들 수 있다.
	virtual void OutputPure1()	abstract
	{
	}

	void Output1()
	{
		printf("CParent Output1 Function\n");
	}
};

class CChild :
	public CParent
{
public:
	CChild()
	{
		mA = 500;
		//mB = 400;
		mZ = 600;
		printf("CChild 생성자\n");
	}

	~CChild()
	{
		printf("CChild 소멸자\n");
	}

public:
	int	mC = 30;

public:
	// 함수 재정의(함수 오버라이딩). 부모클래스의 함수를 완전히 동일한 형태로
	// 자식클래스에 재정의 하는것을 말한다.
	// final 키워드는 이 클래스의 자식클래스에서 더이상 이 함수를 재정의 할 수
	// 없다는 의미이다.
	void Output()	final
	{
		printf("CChild Output Function\n");
	}

	virtual void OutputPure()
	{
	}

	virtual void OutputPure1()
	{
	}

	// override는 명시적으로 이 함수는 부모의 함수를 재정의 한 함수로 인식시켜서
	// 부모에 없는 함수를 만들게 되면 에러가 발생한다.
	/*void OutputOverride()	override
	{
	}

	void Output3()	override
	{
	}*/

};

class CChild1 :
	public CParent
{
public:
	CChild1()
	{
		printf("CChild1 생성자\n");
	}

	~CChild1()
	{
		printf("CChild1 소멸자\n");
	}

public:
	int mD = 30;
	int mE = 40;

public:
	// 함수 재정의(함수 오버라이딩). 부모클래스의 함수를 완전히 동일한 형태로
	// 자식클래스에 재정의 하는것을 말한다.
	/*void Output()
	{
		printf("CChild1 Output Function\n");
	}*/

	virtual void OutputPure()
	{
	}

	virtual void OutputPure1()
	{
	}

};

class CChildChild :
	public CChild
{
public:
	CChildChild()
	{
		printf("CChildChild 생성자\n");
	}

	~CChildChild()
	{
		printf("CChildChild 소멸자\n");
	}

public:
	int mD = 40;

public:
	// 함수 재정의(함수 오버라이딩). 부모클래스의 함수를 완전히 동일한 형태로
	// 자식클래스에 재정의 하는것을 말한다.
	/*void Output()
	{
		printf("CChildChild Output Function\n");
	}*/

};

// 클래스를 생성할 때 클래스 이름 뒤에 abstract 를 붙여주면 해당 클래스는
// 추상클래스가 된다.
class CEmpty	abstract
{
public:
	CEmpty()
	{
	}

	~CEmpty()
	{
	}

public:
	int	mA;
};

// 클래스 뒤에 final 키워드를 붙여주면 더이상 상속할 수 없는 클래스가 된다.
class CEmpty1 final
{
public:
	CEmpty1()
	{
	}

	virtual ~CEmpty1()
	{
	}

public:
	int	mA;
};

//class CEmpty2 : public CEmpty1
//{
//};


int main()
{
	// CChild 타입의 객체를 생성하고 그 주소를 CParent 포인터 타입의 변수에
	// 담아둔다.
	CParent* Parent11[2];

	Parent11[0] = new CChild;
	Parent11[1] = new CChild1;

	CChild1* Child11 = dynamic_cast<CChild1*>(Parent11[0]);

	Parent11[0]->Output();
	Parent11[1]->Output();

	// CParent 포인터 타입에 있는 주소를 제거한다.
	delete Parent11[0];
	delete Parent11[1];

	system("cls");

	printf("Empty Size : %d\n", sizeof(CEmpty));
	printf("Empty1 Size : %d\n", sizeof(CEmpty1));
	//CParent	parent, parent1;
	//CChild	child, child1;
	/*CChild	child;

	child.Output();
	child.Output1();*/

	return 0;

	//CParent	Parent;
	//CChild		Child;
	//CChildChild		ChildChild;

	//Child.Output();
	//Child.mA = 120;
	//Child.mB = 130;
	//Child.mZ = 1111;
	// typeid(변수 혹은 타입) 을 넣어주면 type_info 타입의 객체를 얻어온다. -> RTTI 이용
	//type_info
	//typeid(Child).;
	// 출력 : class CChild
	//printf("TypeName : %s\n", typeid(Child).name());

	CChild Child;

	CChild	Child;
	// Child객체를 CParent 포인터타입으로 업캐스팅 하였다.
	CParent* Parent = &Child;

	// Child1 포인터 타입으로 다운캐스팅 하였다.
	CChild1* Child1 = (CChild1*)Parent;

	// reinterpret의 예시
	int	Addr = (int)Child1;

	printf("메모리 : %p\n", &Child);
	printf("메모리 : %p\n", Parent);
	printf("메모리 : %p\n", Child1);


	/*
	C++의 형변환 (안정성보장)
	static_cast : 일반적인 타입 형변환. 대부분의 형변환에 속함
	const_cast : const 속성을 제거할 때 사용
	dynamic_cast : 런타임에 타입을 검사하여 형변환을 수행함 (RTTI 기능을 활용한 것)
	: 타입이 정상적이라면 형변환, 아니라면 nullptr을 반환
	reinterpret_cast : 비트 단위로 강제 형변환 (C언어스타일의형변환)
	*/

	//Addr = static_cast<int>(Child1);
	Addr = static_cast<int>(3.14f);

	const int cNumber = 500;

	//int* Addr2 = &cNumber;
	int* Addr1 = const_cast<int*>(&cNumber);

	CParent* Parent1 = dynamic_cast<CParent*>(&Child);

	printf("dynamic cast Parent1 = %p\n", Parent1);

	// 오류 발생 : 다형 클래스 형식이어야 함 -> 가상 함수 때 설명
	/*CChild1* dnChild1 = dynamic_cast<CChild1*>(Parent1);

	printf("dynamic cast Parent1 = %p\n", dnChild1);*/



	return 0;
}