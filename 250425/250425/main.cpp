
#include <iostream>

// 시간에 관련된 기능을 제공
#include <time.h>

void main()
{
	/*
	srand() : 난수를 초기화하는 함수, seed값을 넣어줘야 함
	srand() 없이 rand()만 사용하면 난수표에서 동일한 순서대로 출력하기 때문에 완전한 난수 출력이 불가함
	time(0) : 현재 시간을 초 단위로 반환하는 함수, seed값으로 사용하기 위해서 사용
	rand() : 난수를 만들어줌, short 타입이라 0 ~ 32767까지의 수를 만들어줌
	*/
	srand(time(0));
	rand(); // 첫 번째 rand 값은 계속 초가 늘어나서 완전 난수가 안되기 때문에 하나를 먼저 버림
	
	/*
	코드 블록 안에 변수 선언할 때 주의해야 함

	int Number = 200;
	{ Number = 100; }
	std::cout << Number;

	{ int Number1 = 100; }
	std::cout << Number1;
	*/

	/*
	분기문 : 여러 조건 중 하나를 선택해서 동작시키는 방식 -> if문과 switch문
	
	if (조건식) {
		동작할 코드
	}
	조건식이 true일 경우 {} (코드블록) 안에 있는 코드가 동작하고, false일 경우에는 건너뜀
	
	else : 반드시 if문 아래에 사용해야 하며, else if보다 아래에 있어야 함
	혼자 사용이 불가능하며, if문 1개에 한 개의 else만 사용이 가능함
	if문의 조건식이 false일 경우 else문이 동작함
	else {
		동작할 코드
	}

	else if : 반드시 if문 아래에 사용해야 하며, else보다는 위에 있어야 함
	혼자 사용이 불가능하며, if문 1개에 여러 개의 else if 사용이 가능함
	else if (조건식) {
		동작할 코드
	}
	*/

	if (false) {
		printf("if문 조건식이 true입니다.\n");
	}
	else {
		printf("if문 조건식이 false입니다.\n");
	}

	/*
	보스 체력에 따라 행동이 달라져야 할 때를 가정해보자.
	보스 체력이 20보다 작을 경우
	보스 체력이 21 ~ 50 사이일 경우
	보스 체력이 51 ~ 70 사이일 경우
	71 이상일 경우
	*/
	int BossHP = 57;
	/*if (BossHP >= 71) {
		printf("보스 체력이 71 이상입니다.\n");
	}
	else if (BossHP >= 51 && BossHP <= 70) {
		printf("보스 체력이 51 ~ 70 사이입니다.\n");
	}
	else if (BossHP >= 21 && BossHP <= 50) {
		printf("보스 체력이 21 ~ 50 사이입니다.\n");
	}
	else {
		printf("보스 체력이 20 이하입니다.\n");
	}*/

	if (BossHP >= 71) {
		printf("보스 체력이 71 이상입니다.\n");
	}
	else if (BossHP >= 51) {	// 71보다 큰 수는 첫 번째 if문에서 걸러질 거기 때문에 51보다 큰 조건만 쓰면 됨
		printf("보스 체력이 51 ~ 70 사이입니다.\n");
	}
	else if (BossHP >= 21) {
		printf("보스 체력이 21 ~ 50 사이입니다.\n");
	}
	else {
		printf("보스 체력이 20 이하입니다.\n");
	}

	/*
	조건식 안에 변수를 선언하는 것은 지양해야 함
	if (int Num1 = 500) { }
	*/

	printf("Rand : %d\n", rand());
	printf("Rand : %d\n", rand());
	printf("Rand : %d\n", rand());
	printf("Rand : %d\n", rand());

	// 0 ~ 100 사이의 난수가 나와야 한다면?
	// -> 나머지 활용
	printf("Rand : %d\n", rand() % 101);
	printf("Rand : %d\n", rand() % 101);
	printf("Rand : %d\n", rand() % 101);

	// 100 ~ 400 사이의 난수가 나와야 한다면?
	// -> 난수 % (구간값 + 1) + 최솟값
	// 최솟값 : 100 / 최댓값 : 400 / 구간값 : 300
	printf("Rand : %d\n", rand() % 301 + 100);
	printf("Rand : %d\n", rand() % 301 + 100);
	printf("Rand : %d\n", rand() % 301 + 100);

	// 200 ~ 400 사이의 난수? -> 난수 % 201 + 200

	// 0 ~ 100 사이의 소수점 두 번째자리까지 확률을 구하고 싶다면?
	printf("Rand : %.2f\n", rand() % 10001 / 100.f);
	printf("Rand : %.2f\n", rand() % 10001 / 100.f);
	printf("Rand : %.2f\n", rand() % 10001 / 100.f);

	// 0 ~ 100 사이의 소수점 네 번째자리까지 확률을 구하고 싶다면?
	float Result = rand() % 101;
	// rand() % 10001 : 0 ~ 10000 사이의 값이 나옴
	// 0 ~ 10000 사이의 값을 10000.f로 나누게 되면 0 ~ 1 사이의 소수점 네 번째자리까지 구하게 됨
	float Percent = rand() % 10001 / 10000.f;
	Result += Percent;
	printf("Rand : %.4f\n", Result);

	// 온라인게임에서는 서버가 있기 때문에 서버에서 확률 계산 후 클라이언트에 전달
	// 클라이언트에서 확률 계산을 하면 해킹이 가능하기 때문에 서버에서 계산 후 클라이언트에 전달하는 것이 좋음
	// 싱글 게임에선 이런 식으로 계산함
	
	// scanf_s : 콘솔창에서 입력 받을 때 사용하는 함수
	// %d를 하면 정수를 입력 받겠다는 의미
	int Grade = 0;
	printf("등급을 입력하세요 : ");
	scanf_s("%d", &Grade);
	// std::cin >> Grade; -> C++ 스타일의 입력 방식

	/*
	등급이 0 ~ 3 사이면 100% 성공
	등급이 4 ~ 6 사이면 50% 성공
	등급이 7 ~ 9 사이면 10% 성공
	등급이 10 ~ 12 사이면 1% 성공
	등급이 13 이상일 경우 0.05% 성공
	20% 확률로 등급 두 개 증가
	*/
	Percent = rand() % 10001 / 100.f;
	float Percent1 = rand() % 10001 / 100.f;

	printf("Percent : %.2f\n", Percent);
	printf("Percent1 : %.2f\n", Percent1);

	if (0 <= Grade && Grade <= 3) {
		if (Percent1 <= 20.f) {
			Grade += 2;
		}
		else {
			Grade++;
		}
		// ++Grade; 둘 다 1 증가 -> 전치와 후치 차이점은 포인터 때 추가 설명
		printf("강화 성공 : %d\n", Grade);
	}
	else if (Grade <= 6) {
		if (Percent <= 50.f) {
			if (Percent1 <= 20.f) {
				Grade += 2;
			}
			else {
				Grade++;
			}
			printf("강화 성공 : %d\n", Grade);
		}
		else {
			printf("강화 실패 : %d\n", Grade);
		}
	}
	else if (Grade <= 9) {
		if (Percent <= 10.f) {
			if (Percent1 <= 20.f) {
				Grade += 2;
			}
			else {
				Grade++;
			}
			printf("강화 성공 : %d\n", Grade);
		}
		else {
			printf("강화 실패 : %d\n", Grade);
		}
	}
	else if (Grade <= 12) {
		if (Percent <= 1.f) {
			if (Percent1 <= 20.f) {
				Grade += 2;
			}
			else {
				Grade++;
			}
			printf("강화 성공 : %d\n", Grade);
		}
		else {
			printf("강화 실패 : %d\n", Grade);
		}
	}
	else if (Grade >= 13) {
		if (Percent <= 0.05f) {
			if (Percent1 <= 20.f) {
				Grade += 2;
			}
			else {
				Grade++;
			}
			printf("강화 성공 : %d\n", Grade);
		}
		else {
			printf("강화 실패 : %d\n", Grade);
		}
	}
	else {
		printf("잘못된 등급입니다.");
	}
	// 반복되는 구문이 너무 많음 -> 나중에 함수로 만들어서 최적화하면 됨

	/*
	문제) 치명타 확률을 정하고, 치명타 확률 안에 들어오면
	최소공격력 ~ 최대공격력 사이의 최종 공격력을 구해서
	치명타 계수를 적용하여 데미지를 구하기
	*/
	float RandomCritical = rand() % 10001 / 100.f;		// 치명타 확률
	printf("치명타 확률 %.2f퍼에 ", RandomCritical);
	
	// 최소 공격력 : 1000, 최대 공격력 : 30000, 구간: 29000
	int MinPower = 1000, MaxPower = 30000;
	int RandomPower = rand() % 29001 + MinPower;		// 랜덤 공격력
	printf("내 공격력은 %d이다..!\n", RandomPower);
	int ResultDemage = 0;								// 최종 데미지
	
	/*
	치명타 확률이 90 이상이면 데미지 2배
	치명타 확률이 70 ~ 90 사이면 데미지 1.5배
	치명타 확률이 50 ~ 70 사이면 데미지 1.3배
	치명타 확률이 30 ~ 50 사이면 데미지 1.1배
	그 밑은 치명타가 터지지 않음
	*/
	if (RandomCritical >= 90) {
		ResultDemage = RandomPower * 2.f;
		printf("%d딜 넣기!!\n", ResultDemage);
	}
	else if (RandomCritical >= 70) {
		ResultDemage = RandomPower * 1.5f;
		printf("%d딜 넣기!!\n", ResultDemage);
	}
	else if (RandomCritical >= 50) {
		ResultDemage = RandomPower * 1.3f;
		printf("%d딜 넣기!!\n", ResultDemage);
	}
	else if (RandomCritical >= 30) {
		ResultDemage = RandomPower * 1.1f;
		printf("%d딜 넣기!!\n", ResultDemage);
	}
	else {
		printf("이게 안터지네.. 에잇 %d딜 노마이..\n", RandomPower);
	}

	// -------- 이 밑에는 강사님 작성한 코드

	int AttackMin = 300;
	int AttackMax = 700;

	// 최소 공격력 - 최대 공격력 사이의 최종 공격력 구하기
	int Attack = rand() % (AttackMax - AttackMin + 1) + AttackMin;

	Percent = rand() % 10001 / 100.f;	// 치명타 확률

	float Critical = 65.37f;			// 치명타 성공 기준

	// if문 안의 코드가 1줄일 경우 코드 블록을 생략할 수 있음
	if (Percent <= Critical)
		Attack *= 1.5f;

	printf("Attack = %d\n", Attack);
}