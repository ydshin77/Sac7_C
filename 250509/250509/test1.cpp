#include <iostream>

class CSingleton
{
private:
	// 생성자와 소멸자를 private으로 선언
	// 외부에서 new, delete, 객체 생성을 못하게 하기 위해서
	CSingleton() {}
	~CSingleton() {}

private:
	// 클래스에 단 하나만 존재하는 인스턴스를 가르킬 포인터
	// 정적 멤버이기 때문에 클래스 전체에서 공유됨 -> 외부 정의 필수
	static CSingleton* mInst;

public:
	// 내부 포인터(mInst)가 nullptr이면 new로 하나만 생성
	// 이미 존재하면 그걸 반환함
	static CSingleton* GetInst()
	{
		if (mInst == nullptr)
			// 힙에 CSingleton 객체를 생성하고 그 주소를 mInst에 반환
			mInst = new CSingleton;

		return mInst;
	}

	// 동적 할당한 인스턴스(mInst) 제거
	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}

};

CSingleton* CSingleton::mInst = nullptr;

int main()
{
	// GetInst()를 여러 번 호출해도 같은 출력값 반환
	// -> 객체가 단 한 번만 생성됐다는 뜻
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());
	printf("Inst = %p\n", CSingleton::GetInst());

	// 프로그램 종료 전 동적 할당한 메모리 제거 (메모리 릭 방지)
	CSingleton::DestroyInst();

	// 출력 : 1
	printf("%d", sizeof(CSingleton));

	return 0;
}