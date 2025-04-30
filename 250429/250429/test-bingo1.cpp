
#include <iostream>
#include <time.h>

void main()
{
	srand(time(0));
	rand();

	// 25��¥�� �迭 ����
	int Number[25] = {};

	// 1 ~ 25 ������ �� �ֱ�
	for (int i = 0; i < 25; ++i)
	{
		Number[i] = i + 1;
	}

	// ���� ����
	for (int i = 0; i < 100; ++i)
	{
		int Index1 = rand() % 25;
		int Index2 = rand() % 25;
		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}

	// �Է� ���� �����ϴ� ����
	int Input = 0;
	// �ϼ��� ���� ���� �����ϴ� ����
	int LineCount = 0;

	while (true)
	{
		// system("DoS���� ���� ��ɾ�");
		// cls : �ܼ� ȭ���� �ؽ�Ʈ�� ��� ������
		system("cls");

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (Number[i * 5 + j] == -1)
					printf("*\t");
				else
					printf("%d\t", Number[i * 5 + j]);
			}
			printf("\n");
		}

		printf("�ϼ��� �� : %d\n", LineCount);

		// 5�� �̻��� �ϼ��ߴٸ� ���� ����
		if (LineCount >= 5)
		{
			printf("�����ϱ���! ������ �����մϴ�");
			break;
		}

		// ���� �Է� �ޱ�
		printf("0 ~ 25 ������ ���ڸ� �Է��ϼ��� (0�� ����) : ");
		scanf_s("%d", &Input);

		if (Input == 0)
			break;
		else if (Input < 0 || Input > 25)
		{
			printf("�߸��� ���ڸ� �Է��Ͽ����ϴ�\n");
			system("pause");
			continue;
		}

		// ã���� ������ �ε����� �����ϱ� ���� ����
		int FindIndex = -1;

		// �Է��� ���ڰ� �迭�� �ִ��� �Ǵ��ϱ� ���� ����
		// �⺻���� �� ã�Ҵٴ� �ǹ��� false�� �־�ΰ�, ã���� ��쿣 true�� �ٲ�
		bool Find = false;

		for (int i = 0; i < 25; ++i)
		{
			if (Number[i] == Input)
			{
				// �ε��� ����
				FindIndex = i;
				// �Է��� ���ڸ� ã������ true�� ����
				Find = true;
				// �ش� �ε����� ���� -1�� �ٲ� *�� ���
				Number[i] = -1;
				// ���� -1�� �ٲٸ� ���̻� ���� ����(Input)�� ���� ������ �ݺ� ����
				break;
			}
		}

		// Find ������ true��� �迭���� ���� ã�Ҵٴ� �ǹ� -> false�� ��ã�� ��
		// ��ã���� ��쿣 ó������ ���ư� �ٽ� ����ϰ� �Է��� �ް� ��
		if (!Find)		// Find == false
			continue;

		// --------- ���� 2�� �ٸ� �κ� : ���� üũ�ϴ� ���
		// 12���� ��� üũ�Ͽ� �ϼ��� ���� ���� ���� (��ȿ����)

		// �ݺ��� ������ ������ �� ���� �ֱ� ������, �ڵ尡 ���ư� ������ 0���� �ʱ�ȭ
		LineCount = 0;

		// *�� �ٲ� ���� �����ϱ� ���� ����
		int StarCount = 0, StarCount1 = 0;

		// ����, ���� üũ
		for (int i = 0; i < 5; ++i)
		{
			// *�� �ٲ� �� üũ�ϱ� ����, *�� ���� �����ϱ� ���� ������ 0���� �ʱ�ȭ
			StarCount = 0;
			StarCount1 = 0;

			// j for���� 5�� ���� ���� ���ڰ� �� ������ ����
			for (int j = 0; j < 5; ++j)
			{
				// ������ üũ
				if (Number[i * 5 + j] == -1)
					++StarCount;
				// ������ üũ
				if (Number[j * 5 + i] == -1)
					++StarCount1;
			}

			// �� ���� ��� *�� �ٲ���� ��� �� �� ����
			if (StarCount == 5)
				++LineCount;
			if (StarCount1 == 5)
				++LineCount;

		}

		// �밢�� üũ

		// ���� ��� -> ������ �ϴ� �밢�� üũ
		// ����, ���� üũ�� �� StarCount�� ���� ���� ���� ������ �ٽ� �ʱ�ȭ
		StarCount = 0;
		for (int i = 0; i <= 24; i += 6)
		{
			if (Number[i] == -1)
				++StarCount;
		}

		if (StarCount == 5)
			++LineCount;

		// ������ ��� -> ���� �ϴ� �밢�� üũ
		StarCount = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (Number[i] == -1)
				++StarCount;
		}

		if (StarCount == 5)
			++LineCount;

	}

}