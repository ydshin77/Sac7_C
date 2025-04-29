
#include <iostream>
#include <time.h>

/*
1 ~ 25 ������ ���ڸ� �����ϱ� ���� �迭 25��¥���� ����
1 ~ 25 ������ ���ڸ� ���� ������
while���� �̿��Ͽ� ���ѷ����� ���� 5x5�� ����ϰ� ���ڸ� �Է¹���
�Է� ���� ���ڰ� 0�̶�� ������ �����ϰ� 1 ~ 25 ������ ���ڶ��
�ش� ���ڸ� ã�Ƽ� *�� �����
�� ���� ��� *�� �ٲ�� �� ī��Ʈ�� ����
���� 5��, ���� 5��, �밢�� 2�ٿ� ���� �ϼ��� ���� üũ�Ͽ�
5�� �̻��̸� ���� ����
*/

void main() {

	

	srand(time(0));
	rand();

	// 1 ~ 10 ���� ���ڸ� 2���� ������ �ִ� 20��¥�� �迭�� ����� ����
	// Open�� ī�尡 ���ȴ��� �����ϴ� �迭
	int Number[20] = {};
	bool Open[20] = {};

	for (int i = 0; i < 10; ++i)
	{
		Number[i] = i + 1;
		Number[i + 10] = i + 1;
	}

	for (int i = 0; i < 100; ++i)
	{
		int Index1 = rand() % 20;
		int Index2 = rand() % 20;

		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}

	int PrevOpenIndex = -1;

	while (true) {
		// �迭�� ���ڸ� ���� 10��, ���� 2�ٷ� ���
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (Open[i * 10 + j])
					printf("%d\t", Number[i * 10 + j]);
				else
					printf("*\t");
			}
			printf("\n");
		}

		// 0 ~ 20 ������ ���ڸ� �Է� ����
		// �Է� ���� ���ڰ� 20�� ��� break�� �̿��� while���� ��������
		int Input = 0;
		printf("0 ~ 19 ������ ���ڸ� �Է����ּ��� (20�� ���� ����) : ");
		scanf_s("%d", &Input);

		if (Input == 20)
			break;
		// 0 ~ 19 ������ ���� �ƴ� ��� �ٽ� ����ϰ� �Է� �ް� ��
		else if (Input < 0 || Input > 19)
			continue;
		// �̹� ���µǾ� �ִ� ī���� �ٽ� �Է¹ް� ��
		if (Open[Input])
			continue;

		Open[Input] = true;

		// ī�� 2���� �����ϸ� 2���� ī�尡 ���� ���� ������ ���Ͽ�
		// ���� ���̸� ��� ���µ� ���¸� �����ϰ�
		// �ٸ� ���̸� �� ī�带 Ŭ���� ���·� ����
		// PrevOpenIndex�� -1�̶�� ù ��° ī�带 �����ϴ� ��

		if (PrevOpenIndex == -1)
		{
			PrevOpenIndex = Input;
			continue;
		}

		// 2��° ī�带 �����ϸ� ���� �� ��
		if (Number[PrevOpenIndex] != Number[Input])
		{
			Open[PrevOpenIndex] = false;
			Open[Input] = false;
		}
		PrevOpenIndex = -1;

		// ���� �� ������ ���� ����
		bool AllOpen = true;
		for (int i = 0; i < 20; ++i)
		{
			if (!Open[i])
			{
				AllOpen = false;
				break;
			}
		}
		if (AllOpen)
		{
			printf("\n��� ī�带 ���߼̳׿�! ������ �����ҰԿ�");
			break;
		}

	}

}