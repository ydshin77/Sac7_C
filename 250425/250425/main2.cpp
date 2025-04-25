
#include <iostream>
#include <time.h>

enum ESRP {
	Scissor = 1,
	Rock,
	Paper,
	Out
};

void main() {

	/*
	반복문 : 원하는 코드를 원하는 수만큼 반복해서 동작시켜줄 때 사용하는 문법
	3가지 문법 지원 > for, while, do while
	실제 모든 소프트웨어의 동작 방식 : 무한 루프 안에서 동작시키고, 끌 때는 main을 나가게 하여 종료

	for (초기값; 조건식; 증감값) {
			동작할 코드
	}
	초기값 : for문이 시작할 때 한 번만 동작함
	조건식 : for문이 시작할 때부터 반복되는 동안 매번 동작함
	증감값 : for문이 시작하고 1번 동작한 이후부터 매번 동작함

	조건식이 true이면 코드 동작, false이면 for문을 빠져나감
	for문의 실행 순서
	초기값 -> 조건식 체크(true) -> 코드 -> 증감값 -> 조건식 체크(true) 
	-> 코드 -> 증감값 -> .... -> 조건(false) -> 빠져나감
	*/

	// i = 0 실행 -> 0 < 10 -> 코드 -> 1 -> 1 < 10 -> 코드 ㅓ->
	// .... 2, 3, 4, 5, 6, 7, 8, 9 -> 10 < 10
	// break : for문을 빠져나감
	// continue : for문의 증감값으로 실행 흐름을 이용
	for (int i = 0; i < 10; ++i){
		if (i == 5)
			break;			// break로 내가 원하는 상황에 빠져나올 수 있음
			//continue;			// continue는 증감값으로 실행 흐름을 이용
		printf("i = %d\n", i);			
	}

	// 3의 배수 출력하기 - 1
	for (int i = 0; i < 100; ++i) {
		if(i % 3 == 0 && i > 0)
			printf("i = %d\n", i);
	}

	// 3의 배수 출력하기 - 2
	// 증감 자리에 i++, i--만 들어갈 거라는 고정관념 없애기
	for (int i = 3; i < 100; i += 3) {
		printf("i = %d\n", i);
	}

	/*Number보다 i가 시작부터 큼 -> 무한루프 (정확히 말하자면 i가 최대치까지 가면 다시 돌아오기때문에 그건 아님)
	int Number = -5;
	for (int i = 0; i > Number; ++i) {

	}*/

	//for (;;) {		// 조건이 아무 것도 없으면 무한 루프

	//}

	/*
	가위, 바위, 보 게임 개선.
	무한루프 안에서 가위바위보 게임이 진행됨
	4번 메뉴로 게임 종료 메뉴를 만들고, 4번 선택시 무한루프를 빠져나와 게임이 종료되게 만들어보자.
	*/
	
	srand(time(0));
	rand();

	for (;;) {
		int Player, AI, Result = 0;
		
		printf("1. 가위\n2.바위\n3.보\n4.종료\n");
		printf("선택 : ");
		scanf_s("%d", &Player);

		if (Player == 4) {
			printf("게임 종료\n");
			return;
		}
		// 정수가 아닌 문자열을 입력했을 땐 에러가 생김 -> input 에러로 처리함
		// 근데 나중에 언리얼엔진 배울 때는 iostream을 안쓰기 때문에 신경 쓸 필요 없음
		else if (Player < 1 || Player > 3) {
			printf("잘못된 선택입니다. 다시 고르세요.\n");
			continue;
		}

		AI = rand() % 3 + 1;
		switch (AI)
		{
		case Scissor:
			printf("AI : 가위\n");
			break;
		case Rock:
			printf("AI : 바위\n");
			break;
		case Paper:
			printf("AI : 보\n");
			break;
		}

		Result = Player - AI;
		if (Result == 1 || Result == -2)
			printf("Player 승리! 한판 더하시죠\n");
		else if (Result == 0)
			printf("비김! 한판 더하시죠\n");
		else
			printf("AI 승리! 한판 더하시죠\n");

	}
	
}