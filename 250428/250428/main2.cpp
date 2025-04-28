
#include <iostream>
#include <time.h>

void main() {

	srand(time(0));
	rand();

	// 1 ~ 45 ������ ���ڸ� ��Ƴ��� ���� ������ ����
	int Number[45] = {};

	// 1 ~ 45 ������ ���� ����
	for (int i = 0; i < 45; ++i) {
		Number[i] = i + 1;
	}

	// ���� ���� �Է� �޾� ���� ����ŭ 6���� ������ ��ȣ�� ����
	int GameCount = 0;
	printf("���� ���� �Է����ּ��� : ");
	scanf_s("%d", &GameCount);
	printf("\n");

	// 6���� ��÷ ��ȣ�� ���ʽ� ��ȣ 1���� �̸� ����
	
	// ���� ����
	for (int i = 0; i < 100; ++i) {
		// ������ �ε��� 2���� ����
		int Index1 = rand() % 45;
		int Index2 = rand() % 45;

		// ���� ���� �ٲ� ���� ���� �˰��� ���
		// Temp�� Index1���� ���� ����
		// Index1���� ���� Index2���� ������ ����
		// �̸� �����ص� Index1���� ���� Index2���� ������ ����
		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}

	// 6���� ���� ����
	for (int i = 0; i < 5; ++i) {
		for (int j = i + 1; j < 6; ++j) {
			if (Number[i] > Number[j]) {
				int	Temp = Number[i];
				Number[i] = Number[j];
				Number[j] = Temp;
			}
		}
	}

	int Result[7] = {};
	for (int i = 0; i < 7; ++i) {
		Result[i] = Number[i];
	}

	printf("��÷ ��ȣ : \n");

	for (int i = 0; i < 6; ++i) {
		printf("%d\t", Result[i]);
	}

	printf("/\t%d\n", Result[6]);
	printf("\n");

	for (int Game = 0; Game < GameCount; ++Game) {
		for (int i = 0; i < 100; ++i) {
			int Index1 = rand() % 45;
			int Index2 = rand() % 45;

			int Temp = Number[Index1];
			Number[Index1] = Number[Index2];
			Number[Index2] = Temp;
		}

		// 6���� ���� ����
		for (int i = 0; i < 5; ++i) {
			for (int j = i + 1; j < 6; ++j) {
				if (Number[i] > Number[j]) {
					int	Temp = Number[i];
					Number[i] = Number[j];
					Number[j] = Temp;
				}
			}
		}

		for (int i = 0; i < 6; ++i) {
			// \t : Tab 1 ���ִ� ��
			printf("%d\t", Number[i]);
		}

		// ��÷ ��ȣ�� ���� 3���� ���ٸ� 5��, 4���� ���ٸ� 4��, 5���� ���ٸ� 3��
		// 5���� ���� ���ʽ� ��ȣ 1���� ���ٸ� 2��, 6���� ���ٸ� 1���� ���
		// �� ���� ������ �����ϴ� ���� ����
		int Pair = 0;

		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 6; ++j) {
				// ���� ���ڰ� ���� ��� Pair�� 1 �����ϰ� ���� ���ڸ� �˻�
				if (Result[i] == Number[j]) {
					++Pair;
					break;
				}
			}
		}

		switch (Pair) {
		case 3:
			printf(" : 5��\n");
			break;
		case 4:
			printf(" : 4��\n");
			break;
		case 5:
			// ���ʽ� ��ȣ�� �ִ��� ��
			bool Second;
			Second = false;
			for (int i = 0; i < 6; ++i) {
				if (Result[6] == Number[i]) {
					Second = true;
					break;
				}
			}
			if (Second)
				printf(" : 2��\n");
			else
				printf(" : 3��\n");
		case 6:
			printf(" : 1��\n");
			break;
		default:
			printf(" : ��\n");
			break;
		}

		// printf("\n");

	}	

}