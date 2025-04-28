
#include <iostream>

void main() {

	/*
	for(초기값; 조건식; 증감값) {
		동작할 코드
	}
	*/

	// 1 ~ 100까지 숫자 중 3과 5의 공배수만 출력하는 for문을 만들어보시오.
	for (int i = 1; i <= 100; ++i) {
		if (i % 3 == 0 && i % 5 == 0) {
			printf("3과 5의 공배수: %d\n", i);
		}
	}

	// 중첩 for문 : for문 안에 또 다른 for문이 들어가는 형태
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 10; ++j) {
			printf("i = %d / j = %d\n", i, j);
		}
	}

	/*
	i와 j의 값을 이용하여 0 ~ 49 까지 출력되는 printf를 만들어보시오.
	i : 0 ~ 4 / j : 0 ~ 9
	i = 0, j = 0 ~ 9 -> 출력 = 0 ~ 9
	i = 1, j = 0 ~ 9 -> 출력 = 10 ~ 19
	타일맵(그리드 형태의 게임)을 만들 때 많이 사용
	-> 세로 번호 * 가로 개수 + 가로 번호
	*/
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 10; ++j) {
			printf("%d\n", i * 10 + j);
		}
	}

	// 구구단 2단 ~ 9단까지 출력하기
	for (int i = 2; i <= 9; ++i) {
		printf("%d단\n", i);
		for (int j = 1; j <= 9; ++j) {
			printf("%d X %d = %d\n", i, j, i * j);
		}
	}

	// 숫자를 입력받아 2단부터 입력 받은 단까지 출력하기
	int Dan = 0;
	printf("출력할 단 수를 입력하세요 : ");
	scanf_s("%d", &Dan);
	// if문과 같은 예외처리 필수 (2보다 작거나 너무 큰 수 입력 방지)
	if (Dan <= 20) {
		for (int i = 2; i <= Dan; ++i) {
			printf("%d단\n", i);
			for (int j = 1; j <= 9; ++j) {
				printf("%d X %d = %d\n", i, j, i * j);
			}
		}
	}

	/*
	*
	**
	***
	****
	*****
	5줄로 구성됨
	*은 1 ~ 5까지 각 줄마다 증가함
	줄 번호마다 1씩 증가함
	*/
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j <= i; ++j) {
			printf("*");
		}
		// 한 줄 출력이 끝났다면 개행
		printf("\n");
	}

	/*
	*****
	****
	***
	**
	*
	5줄로 구성됨
	*은 5 ~ 1까지 각 줄마다 감소함
	*/
	for (int i = 0; i < 5; ++i) {
		// i = 0 5번 / i = 1 4번 / i = 2 3번
		for (int j = i; j < 5; ++j)
		{
			printf("*");
		}
		printf("\n");
	}

	/*
	    *
	   ***
	  *****
	 *******
	*********
	5줄로 구성됨
	*은 1, 3, 5, 7, 9로 세로가 1줄씩 증가할 때마다 2개씩 추가됨
	공백도 출력을 해야 함, 공백은 4, 3, 2, 1, 0개로 1씩 감소함
	*/
	for (int i = 0; i < 5; ++i) {
		for (int j = i + 1; j < 5; j = ++j) {
			printf(" ");
		}
		// i = 0 + 1 1 / i = 1 + 2 3 / i = 2 + 3 5 / i = 3 + 4 7
		// 0 * 2 + 1 = 1 / 1 * 2 + 1 = 3
		for (int j = 0; j < i * 2 + 1; ++j) {
			printf("*");
		}
		printf("\n");
	}

	/*
	while문

	while (조건식) {
		동작할 코드
	}

	조건식이 true일 경우 코드가 동작하고, false일 경우 while문을 빠져나옴
	
	무한 루프 돌릴 때 많이 사용 (ex. 게임 -> 종료할 땐 break를 통해 빠져나옴)
	while (true) {
		동작할 코드
	}

	int Number = 0;
	while (Number < 5) {
		continue;	// ++Number까지 안가게 되어 흐름 제어에 더 신경써야 됨 -> for문을 더 많이 쓰는 이유
		++Number;
	}
	*/
	
	/*
	do while문

	do {
		동작할 코드
	} while (조건식) ;

	처음 한 번은 코드가 동작하고 그 뒤에 조건식을 체크하여, true이면 반복하고 false이면 빠져나감
	while문과 차이점 : 처음 한 번을 동작하느냐 마느냐, while문은 조건이 false면 실행조차 안함
	*/
	while (false) {
		printf("while true\n");
	}

	do {
		printf("do while true\n");
	} while (false);

	// 별을 이용하여 만든 형태를 while문을 이용하여 만들어보시오.
	int Num1 = 0, Num2 = 0;

	while (Num1 < 5) {
		Num2 = 0;
		while (Num2 <= Num1) {
			printf("*");
			++Num2;
		}
		printf("\n");
		++Num1;
	}

	Num1 = 0, Num2 = 0;
	while (Num1 < 5) {
		Num2 = Num1;
		// i = 0 5번 i = 1 4번 i = 2 3번
		while (Num2 < 5) {
			printf("*");
			++Num2;
		}
		printf("\n");
		++Num1;
	}

	Num1 = 0, Num2 = 0;
	while (Num1 < 5) {
		Num2 = Num1 + 1;
		while (Num2 < 5) {
			printf(" ");
			++Num2;
		}
		Num2 = 0;
		// i = 0 + 1 1 / i = 1 + 2 3 / i = 2 + 3 5 / i = 3 + 4 7
		// 0 * 2 + 1 = 1 / 1 * 2 + 1 = 3
		while (Num2 < Num1 * 2 + 1) {
			printf("*");
			++Num2;
		}
		printf("\n");
		++Num1;
	}


}