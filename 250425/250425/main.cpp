
#include <iostream>

// �ð��� ���õ� ����� ����
#include <time.h>

void main()
{
	/*
	srand() : ������ �ʱ�ȭ�ϴ� �Լ�, seed���� �־���� ��
	srand() ���� rand()�� ����ϸ� ����ǥ���� ������ ������� ����ϱ� ������ ������ ���� ����� �Ұ���
	time(0) : ���� �ð��� �� ������ ��ȯ�ϴ� �Լ�, seed������ ����ϱ� ���ؼ� ���
	rand() : ������ �������, short Ÿ���̶� 0 ~ 32767������ ���� �������
	*/
	srand(time(0));
	rand(); // ù ��° rand ���� ��� �ʰ� �þ�� ���� ������ �ȵǱ� ������ �ϳ��� ���� ����
	
	/*
	�ڵ� ��� �ȿ� ���� ������ �� �����ؾ� ��

	int Number = 200;
	{ Number = 100; }
	std::cout << Number;

	{ int Number1 = 100; }
	std::cout << Number1;
	*/

	/*
	�б⹮ : ���� ���� �� �ϳ��� �����ؼ� ���۽�Ű�� ��� -> if���� switch��
	
	if (���ǽ�) {
		������ �ڵ�
	}
	���ǽ��� true�� ��� {} (�ڵ���) �ȿ� �ִ� �ڵ尡 �����ϰ�, false�� ��쿡�� �ǳʶ�
	
	else : �ݵ�� if�� �Ʒ��� ����ؾ� �ϸ�, else if���� �Ʒ��� �־�� ��
	ȥ�� ����� �Ұ����ϸ�, if�� 1���� �� ���� else�� ����� ������
	if���� ���ǽ��� false�� ��� else���� ������
	else {
		������ �ڵ�
	}

	else if : �ݵ�� if�� �Ʒ��� ����ؾ� �ϸ�, else���ٴ� ���� �־�� ��
	ȥ�� ����� �Ұ����ϸ�, if�� 1���� ���� ���� else if ����� ������
	else if (���ǽ�) {
		������ �ڵ�
	}
	*/

	if (false) {
		printf("if�� ���ǽ��� true�Դϴ�.\n");
	}
	else {
		printf("if�� ���ǽ��� false�Դϴ�.\n");
	}

	/*
	���� ü�¿� ���� �ൿ�� �޶����� �� ���� �����غ���.
	���� ü���� 20���� ���� ���
	���� ü���� 21 ~ 50 ������ ���
	���� ü���� 51 ~ 70 ������ ���
	71 �̻��� ���
	*/
	int BossHP = 57;
	/*if (BossHP >= 71) {
		printf("���� ü���� 71 �̻��Դϴ�.\n");
	}
	else if (BossHP >= 51 && BossHP <= 70) {
		printf("���� ü���� 51 ~ 70 �����Դϴ�.\n");
	}
	else if (BossHP >= 21 && BossHP <= 50) {
		printf("���� ü���� 21 ~ 50 �����Դϴ�.\n");
	}
	else {
		printf("���� ü���� 20 �����Դϴ�.\n");
	}*/

	if (BossHP >= 71) {
		printf("���� ü���� 71 �̻��Դϴ�.\n");
	}
	else if (BossHP >= 51) {	// 71���� ū ���� ù ��° if������ �ɷ��� �ű� ������ 51���� ū ���Ǹ� ���� ��
		printf("���� ü���� 51 ~ 70 �����Դϴ�.\n");
	}
	else if (BossHP >= 21) {
		printf("���� ü���� 21 ~ 50 �����Դϴ�.\n");
	}
	else {
		printf("���� ü���� 20 �����Դϴ�.\n");
	}

	/*
	���ǽ� �ȿ� ������ �����ϴ� ���� �����ؾ� ��
	if (int Num1 = 500) { }
	*/

	printf("Rand : %d\n", rand());
	printf("Rand : %d\n", rand());
	printf("Rand : %d\n", rand());
	printf("Rand : %d\n", rand());

	// 0 ~ 100 ������ ������ ���;� �Ѵٸ�?
	// -> ������ Ȱ��
	printf("Rand : %d\n", rand() % 101);
	printf("Rand : %d\n", rand() % 101);
	printf("Rand : %d\n", rand() % 101);

	// 100 ~ 400 ������ ������ ���;� �Ѵٸ�?
	// -> ���� % (������ + 1) + �ּڰ�
	// �ּڰ� : 100 / �ִ� : 400 / ������ : 300
	printf("Rand : %d\n", rand() % 301 + 100);
	printf("Rand : %d\n", rand() % 301 + 100);
	printf("Rand : %d\n", rand() % 301 + 100);

	// 200 ~ 400 ������ ����? -> ���� % 201 + 200

	// 0 ~ 100 ������ �Ҽ��� �� ��°�ڸ����� Ȯ���� ���ϰ� �ʹٸ�?
	printf("Rand : %.2f\n", rand() % 10001 / 100.f);
	printf("Rand : %.2f\n", rand() % 10001 / 100.f);
	printf("Rand : %.2f\n", rand() % 10001 / 100.f);

	// 0 ~ 100 ������ �Ҽ��� �� ��°�ڸ����� Ȯ���� ���ϰ� �ʹٸ�?
	float Result = rand() % 101;
	// rand() % 10001 : 0 ~ 10000 ������ ���� ����
	// 0 ~ 10000 ������ ���� 10000.f�� ������ �Ǹ� 0 ~ 1 ������ �Ҽ��� �� ��°�ڸ����� ���ϰ� ��
	float Percent = rand() % 10001 / 10000.f;
	Result += Percent;
	printf("Rand : %.4f\n", Result);

	// �¶��ΰ��ӿ����� ������ �ֱ� ������ �������� Ȯ�� ��� �� Ŭ���̾�Ʈ�� ����
	// Ŭ���̾�Ʈ���� Ȯ�� ����� �ϸ� ��ŷ�� �����ϱ� ������ �������� ��� �� Ŭ���̾�Ʈ�� �����ϴ� ���� ����
	// �̱� ���ӿ��� �̷� ������ �����
	
	// scanf_s : �ܼ�â���� �Է� ���� �� ����ϴ� �Լ�
	// %d�� �ϸ� ������ �Է� �ްڴٴ� �ǹ�
	int Grade = 0;
	printf("����� �Է��ϼ��� : ");
	scanf_s("%d", &Grade);
	// std::cin >> Grade; -> C++ ��Ÿ���� �Է� ���

	/*
	����� 0 ~ 3 ���̸� 100% ����
	����� 4 ~ 6 ���̸� 50% ����
	����� 7 ~ 9 ���̸� 10% ����
	����� 10 ~ 12 ���̸� 1% ����
	����� 13 �̻��� ��� 0.05% ����
	20% Ȯ���� ��� �� �� ����
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
		// ++Grade; �� �� 1 ���� -> ��ġ�� ��ġ �������� ������ �� �߰� ����
		printf("��ȭ ���� : %d\n", Grade);
	}
	else if (Grade <= 6) {
		if (Percent <= 50.f) {
			if (Percent1 <= 20.f) {
				Grade += 2;
			}
			else {
				Grade++;
			}
			printf("��ȭ ���� : %d\n", Grade);
		}
		else {
			printf("��ȭ ���� : %d\n", Grade);
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
			printf("��ȭ ���� : %d\n", Grade);
		}
		else {
			printf("��ȭ ���� : %d\n", Grade);
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
			printf("��ȭ ���� : %d\n", Grade);
		}
		else {
			printf("��ȭ ���� : %d\n", Grade);
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
			printf("��ȭ ���� : %d\n", Grade);
		}
		else {
			printf("��ȭ ���� : %d\n", Grade);
		}
	}
	else {
		printf("�߸��� ����Դϴ�.");
	}
	// �ݺ��Ǵ� ������ �ʹ� ���� -> ���߿� �Լ��� ���� ����ȭ�ϸ� ��

	/*
	����) ġ��Ÿ Ȯ���� ���ϰ�, ġ��Ÿ Ȯ�� �ȿ� ������
	�ּҰ��ݷ� ~ �ִ���ݷ� ������ ���� ���ݷ��� ���ؼ�
	ġ��Ÿ ����� �����Ͽ� �������� ���ϱ�
	*/
	float RandomCritical = rand() % 10001 / 100.f;		// ġ��Ÿ Ȯ��
	printf("ġ��Ÿ Ȯ�� %.2f�ۿ� ", RandomCritical);
	
	// �ּ� ���ݷ� : 1000, �ִ� ���ݷ� : 30000, ����: 29000
	int MinPower = 1000, MaxPower = 30000;
	int RandomPower = rand() % 29001 + MinPower;		// ���� ���ݷ�
	printf("�� ���ݷ��� %d�̴�..!\n", RandomPower);
	int ResultDemage = 0;								// ���� ������
	
	/*
	ġ��Ÿ Ȯ���� 90 �̻��̸� ������ 2��
	ġ��Ÿ Ȯ���� 70 ~ 90 ���̸� ������ 1.5��
	ġ��Ÿ Ȯ���� 50 ~ 70 ���̸� ������ 1.3��
	ġ��Ÿ Ȯ���� 30 ~ 50 ���̸� ������ 1.1��
	�� ���� ġ��Ÿ�� ������ ����
	*/
	if (RandomCritical >= 90) {
		ResultDemage = RandomPower * 2.f;
		printf("%d�� �ֱ�!!\n", ResultDemage);
	}
	else if (RandomCritical >= 70) {
		ResultDemage = RandomPower * 1.5f;
		printf("%d�� �ֱ�!!\n", ResultDemage);
	}
	else if (RandomCritical >= 50) {
		ResultDemage = RandomPower * 1.3f;
		printf("%d�� �ֱ�!!\n", ResultDemage);
	}
	else if (RandomCritical >= 30) {
		ResultDemage = RandomPower * 1.1f;
		printf("%d�� �ֱ�!!\n", ResultDemage);
	}
	else {
		printf("�̰� ��������.. ���� %d�� �븶��..\n", RandomPower);
	}

	// -------- �� �ؿ��� ����� �ۼ��� �ڵ�

	int AttackMin = 300;
	int AttackMax = 700;

	// �ּ� ���ݷ� - �ִ� ���ݷ� ������ ���� ���ݷ� ���ϱ�
	int Attack = rand() % (AttackMax - AttackMin + 1) + AttackMin;

	Percent = rand() % 10001 / 100.f;	// ġ��Ÿ Ȯ��

	float Critical = 65.37f;			// ġ��Ÿ ���� ����

	// if�� ���� �ڵ尡 1���� ��� �ڵ� ����� ������ �� ����
	if (Percent <= Critical)
		Attack *= 1.5f;

	printf("Attack = %d\n", Attack);
}