
#include <iostream>
#include <time.h>

void main()
{
	srand(time(0));
	rand();

	// 1 ~ 10 ������ ���ڸ� 2���� ������ �ִ� 20��¥�� �迭 ����
	int Number[20] = {};

	for (int i = 0; i < 10; ++i)
	{
		Number[i] = i + 1;
		Number[i + 10] = i + 1;
	}

	// ���� �������� ����
	for (int i = 0; i < 100; ++i)
	{
		int Index1 = rand() % 20;
		int Index2 = rand() % 20;

		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}

	// Open�� ī�尡 ���ȴ��� �����ϴ� �迭
	bool Open[20] = {};
	// ������ �Է��� ���� �����ϴ� ����
	int PrevOpenIndex = -1;

	while (true)
	{
		// �迭�� ���ڸ� ���� 10��, ���� 2�ٷ� ���
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				// Open���� true���߸� ���ڰ� ������
				// false�� * ���
				if (Open[i * 10 + j])
					printf("%d\t", Number[i * 10 + j]);
				else
					printf("*\t");
			}
			printf("\n");
		}
		
		// ���� �Է¹���
		int Input = 0;
		printf("0 ~ 19 ������ ���ڸ� �Է����ּ��� (20�� ���� ����) : ");
		scanf_s("%d", &Input);

		if (Input == 20)
			break;
		else if (Input < 0 || Input > 19)
		{
			printf("�߸��� ���� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���\n");
			continue;
		}

		// �̹� ���µǾ� �ִ� ī��� �ٽ� �Է¹ް� ��
		if (Open[Input])
			continue;

		// �ùٸ� ���� �Է��ߴٸ� Open ���� true�� ����
		Open[Input] = true;

		// PrevOpenIndex�� -1�̶�� ù ��° ī�带 �����ϴ� ��
		if (PrevOpenIndex == -1)
		{
			// Open ���� true�� ������ ������ �ε����� ���ڰ� ���µ�
			PrevOpenIndex = Input;
			continue;
		}

		// 2��° ī�带 �����ϸ� ���� ���� ��
		// ���� �ʴٸ� Open ���� false�� �ٲ�� *�� ��µǰ�
		// ���ٸ� Open ���� ��� true�� ������ ����ؼ� ���ڷ� ��µ�
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
			// Open�� ��� true�� �ƴ϶�� ��� ���� ���� �ƴ�
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