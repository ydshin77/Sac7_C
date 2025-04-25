
#include <iostream>
#include <time.h>

// 가위, 바위, 보가 1, 2, 3로 정해놓음 > 가독성이 떨어지고 나중에 까먹을 가능성 농후
// => const int, 열거형 등을 사용하여 가독성 높이기

/*
열거형 : 상수에 이름을 부여해주는 기능, 기본적으로 4바이트(int형)
열거형은 사용자 정의 변수 타입으로도 사용 가능
열거형의 이름은 사용자 정의 변수 타입, 열거형 안의 목록은 상수가 됨
열거형 안의 목록은 기본으로 0부터 1씩 차례로 증가하게 됨
열거형 안의 목록은 원한다면 기본 값을 변경할 수도 있음
main 함수 안에 작성도 가능하지만, 코드 블록을 벗어나면 사용을 못하기 때문에 보통 전역 변수로 사용
가위바위보의 rock이 아니라 돌맹이를 표현하고 싶음.. 근데 이름이 중복되서 사용을 못함
-> 네임스페이스로 묶어서 열거형 사용 / enum class라는 문법 사용
*/
enum ESRP : char {		// : char를 통해 1바이트로 변경 가능 (기본값은 4바이트) -> 열거형의 타입 지정 가능
	Scissor = 1, // Rock과 Paper는 2, 3이 됨 -> 지정한 수부터 1씩 증가
	Rock,
	Paper
};
enum class ESRP2 : unsigned char {
	Scissor2 = 1,
	Rock2,
	Paper2
};
namespace ESRP3 {
	enum Type {
		Scissor = 1, // ESPR3:Scissor로 하면 정수와의 계산 가능
		Rock,
		Paper
	};
}

void main() {

	srand(time(0));
	rand();

	// 플레이어의 가위, 바위, 보 값을 저장하기 위한 변수를 선언
	// 가위 : 1, 바위 : 2, 보 : 3
	int Player = 0;

	printf("1. 가위\n2. 바위\n3. 보\n");
	printf("선택 : ");
	scanf_s("%d", &Player);

	// 선택한 값이 1 ~ 3 사이의 값이 아닐 경우 게임을 종료함
	// return은 소속되어 있는 함수를 빠져나가는 기능
	// main을 빠져나가게 되면 프로그램이 종료됨
	if (Player < 1 || Player > 3)
		return;

	// AI가 가위(1), 바위(2), 보(3) 중 하나를 선택하게 함
	int AI = rand() % 3 + 1;

	/*
	switch문 : 분기 처리의 한 종류 -> 어떤 값일지 찾을 때 쓰는 것으로 한정되어 있음, if문은 더 다양하게 사용
	switch (값) {
		case 상수:
			동작할 코드
			break;			// switch문을 빠져나가는 역할
		case 상수:
			동작할 코드		// break가 없다면 밑에 case까지 동작함
		case 상수:
			동작할 코드
			break;
		default:			// if문의 else와 같은 역할
			동작할 코드
			break;
	}
	*/

	if (AI == 1)
		printf("AI : 가위\n");
	else if (AI == 2)
		printf("AI : 바위\n");
	else
		printf("AI : 보\n");

	switch (AI)		// 보통 열거형과 switch문 같이 씀, tab과 enter 누르면 자동완성
					// namespace에 있는 열거형은 자동완성 안됨
	{
	case Scissor:	// namespace에 있는 자동완성은 타입이 int가 아니기 switch의 값이나 case의 상수에 넣을 수 없음
					// ESRP2 Srp2 = ESRP2::Scissor2; 이런 식으로 switch문 위에 정의해놓으면 사용 가능
		// case 안에서 변수 선언과 동시에 초기화를 하면 오류가 발생함
		// -> int Number3 = 100;
		// 변수 선언 후 초기화를 하던가, 변수 선언 부분을 코드블럭으로 묶거나 해야 됨
		//int Number3;
		//Number3 = 100;
		printf("AI : 가위\n");
		break;
	case Rock:
	{
		/*int Number4 = 500;*/
		printf("AI : 바위\n");
	}
		break;
	case Paper:
		//int Number3; // Number3은 switch문의 코드블럭 안에서 선언되었기 때문에 재정의 오류 발생
		//Number3 = 200;
		printf("AI : 보\n");
		break;
	}

	// 플레이어와 AI의 값을 이용하여 결과 출력

	// 플레이어가 승리했을 경우
	if (Player == ESRP3::Scissor && AI == 3 ||	// 네임스페이스 ESRP3을 사용하여 가독성을 높일 수 있음
		Player == 2 && AI == 1 ||
		Player == 3 && AI == 2)
		printf("Player 승리!\n");

	// 플레이어가 승리했을 경우
	else if (AI == 1 && Player == 3 ||
		AI == 2 && Player == 1 ||
		AI == 3 && Player == 2)
		printf("AI 승리!\n");

	else
		printf("비김\n");

	// 위의 코드 간소화 방법 : Player와 AI의 차를 이용
	int Result = Player - AI;

	if (Result == 1 || Result == -1)
		printf("Player 승리\n");
	else if (Result == 0)
		printf("비김\n");
	else
		printf("AI 승리\n");

	printf("%d\n", ESRP2::Rock2);		// enum class를 사용하면 ESRP2::를 사용해서 변수 중복을 막아줄 수 있음
	printf("%d\n", ESRP2::Scissor2);
	printf("%d\n", ESRP2::Paper2);

	int SRPNumber = Scissor;
	// RSPNumber = ERSP2::Scissor2;		-> 정수 간의 계산(비교, 연산, 대입 등)을 할 때 사용할 수 없다는 게 네임스페이스를 사용한 열거형의 단점
	// RSPNumner = 2 - ERSP2::Scissor2;	-> 열거형 두 종류를 조건에 맞춰 사용, 열거형은 굉장히 많이 사용됨

	

}