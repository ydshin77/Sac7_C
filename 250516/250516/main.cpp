
#include <iostream>

/*
동적할당을 사용할 때 생길 수 있는 문제점
1. 메모리 단편화
2. 메모리 릭
3. 댕글링 포인터의 잘못된 접근.

외부단편화 : 동적으로 메모리를 할당과 해제를 하는 과정에서 할당된 메모리의 중간에
작은 메모리가 여러개 만들어지게 되어 비어있는 공간의 용량은 충분하지만 하나의 큰 메모리를
할당할 수 있는 공간은 부족한 상황.

내부단편화 : 할당된 메모리 중에서 실제로 사용되지 않는 부분이 낭비되는 상황.
구조체나 클래스의 메모리 패딩 상황.

메모리 단편화 해결방법
1. 메모리 풀 : 내부.외부 모두 해결 가능. 메모리를 미리 할당해두고 필요할 때 미리 할당해둔 메모리를 가져와서 사용하고
사용이 완료된 메모리는 다시 풀에 반환해주어 재사용할 수 있게 해주는것을 말한다.
2. 페이징 기법 : 가상메모리 사용. 외부단편화 해결 방법. 가상메모리를 같은 크기의 블록
으로 나눈 것을 페이지라고 하고 메모리를 페이지와 같은 크기로 나눈 것을 프레임이라고
한다.
사용하지 않는 프레임을 페이지에 옮기고 필요한 메모리를 페이지 단위로 프레임에 옮겨주는
기법.
3. 세그멘테이션 기법 : 내부단편화 해결.
가상메모리를 서로 다른 크기로 분할해서 메모리를 할당하여 실제 메모리 주소로 변환하여
사용하는 기법.

댕글링포인터 해결방법 : 스마트 포인터 사용.
레퍼런스 카운트를 이용하여 참조하는 카운트가 없을 경우 메모리를 제거하는 방식.

c++에서 제공하는 스마트포인터는 std namespace 안에 들어가 있다.
c++의 스마트 포인터 종류
std::unique_ptr : 하나의 스마트 포인터만 소유한다.
단독소유. 복사도 안된다. 속도가 빠르다.
std::shared_ptr : 여러 객체가 하나의 공간을 공유하는 경우.
레퍼런스 카운트를 이용하여 참조하는 횟수를 만들고 레퍼런스 카운트가 0이 되면
메모리를 제거하는 방식이다.
속도가 느리다.
std::weak_ptr : shared_ptr의 비소유 참조. 레퍼런스 카운트를 증가시키지 않음.
속도가 빠르다.
*/

int main()
{
	// std::make_unique : unique_ptr을 생성해주는 함수이다.
	std::unique_ptr<int>	Ptr = std::make_unique<int>(10);
	//std::unique_ptr<int>	Copy = Ptr;
	// Ptr의 메모리, 값 을 Move로 옮겨준다.
	std::unique_ptr<int>	Move = std::move(Ptr);

	printf("%d\n", *Move);

	int* Number = new int;
	*Number = 500;
	std::shared_ptr<int>	SPtr(Number);
	std::shared_ptr<int>	SPtr2 = SPtr;

	std::shared_ptr<int>	SPtr1 = std::make_shared<int>(123);

	printf("%d\n", *SPtr);
	printf("%d\n", *SPtr1);
	printf("%d\n", *SPtr2);

	// 참조카운트가 증가하지 않는다.
	std::weak_ptr<int>	WPtr = SPtr;

	// 유효성 확인 후 사용해야 한다.
	if (WPtr.expired())
	{
		std::shared_ptr<int>	SPtrLock = WPtr.lock();
		//printf("%d\n", *WPtr);
		printf("%d\n", *SPtrLock);
	}

	return 0;
}
