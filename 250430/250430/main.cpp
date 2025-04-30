// �Լ��� ����Ͽ� �ۼ��� ���� ����

#include <iostream>
#include <time.h>

// ��ó���� -> ������ ���� ����
// define : �ڿ� �� �ڵ带 �������ִ� ��, �� �� ������
// ���� : ������ ����, �� �ٲ� �� ���� -> ȿ���� / ���� : ������� ��ٷο�
// const int�� �����ص� ���� ���� ����
#define LINECOUNT	5
#define ARRAYCOUNT	(LINECOUNT * LINECOUNT)

// �Լ��� ����� ����� ���� main�� �ʿ��� �� ����ͼ� ����ϱ⿡ �ͼ������� ��

// �Լ��� ����� ���� ���ÿ� �ص� ������, ������ �Լ�, �ؿ��� ����. �̷��� ���� �ص� ��
// ���� �Լ� ���� -> ��򰡿� ���� �κ��� ���� ���̴� / main �Լ� �ؿ� ���� ����
// �Լ� �̸� Ŭ�� �� F12 ������ �Լ� ���� �κ����� �̵� -> �ٽ� ������ ���� �κ�����
// �Լ� ����κ� ��� ��� ��Ʈ��+. > c ������ ���� �κ� �ڵ� ������
// �ܾ� ���� : ����Ŭ��, ��Ʈ��Ŭ��
void SetNumber(int Number[ARRAYCOUNT]);
void Shuffle(int Number[ARRAYCOUNT]);
void OutputInfo(int Number[ARRAYCOUNT], int LineCount);
int ChangeNumber(int Number[ARRAYCOUNT], int Input);
int ComputeLineCount(int Number[ARRAYCOUNT], int Index);
int SelectAI(int Number[ARRAYCOUNT]);

void main()
{
	srand(time(0));
	rand();
	
	// �迭[] �ȿ��� ����� ���� �� -> const ��� ����
	// const int Count = 25;

	// ���� �迭 ����
	int Number[ARRAYCOUNT] = {};
	int AINumber[ARRAYCOUNT] = {};

	// ���ڿ� �� �ֱ�
	SetNumber(Number);
	SetNumber(AINumber);

	// ���� ����
	Shuffle(Number);
	Shuffle(AINumber);

	int Input = 0;
	int LineCount = 0, AILineCount = 0;

	while (true)
	{
		system("cls");

		// �÷��̾� ���� ���
		printf("======== Player ========\n");
		OutputInfo(Number, LineCount);

		// AI ���� ���
		printf("======== AI ========\n");
		OutputInfo(AINumber, AILineCount);

		// 5�� �̻� �ϼ��ߴٸ� ���� ����
		if (LineCount >= LINECOUNT)
		{
			printf("�÷��̾� �¸�\n");
			break;
		}
		else if (AILineCount >= LINECOUNT)
		{
			printf("AI �¸�\n");
			break;
		}

		// ���ڸ� �Է� ����
		printf("0 ~ 25 ������ ���ڸ� �Է��ϼ��� (0: ����) : ");
		scanf_s("%d", &Input);

		if (Input == 0)
			break;
		else if (Input < 0 || Input > ARRAYCOUNT)
		{
			printf("�߸��� ���ڸ� �Է��Ͽ����ϴ�\n");
			system("pause");
			continue;
		}

		// �Է��� ���ڸ� *�� �ٲ���
		int FindIndex = ChangeNumber(Number, Input);
		
		// *�� �ٲ� �ε����� -1�̶�� �̹� *�� �ٲ� ���ڸ� �Է��� ���̹Ƿ� �ٽ� �Է¹ް� ��
		if (FindIndex == -1)
			continue;

		int AIFindIndex = ChangeNumber(AINumber, Input);

		// �� �� üũ
		// ComputeLineCount �Լ����� �Ѱ��� �ε����� *�� �ٲپ��� ���
		// �� ���� �߰��Ǿ�� �ϴ����� ��ȯ
		LineCount += ComputeLineCount(Number, FindIndex);
		AILineCount += ComputeLineCount(AINumber, AIFindIndex);

		// AI�� �Է�
		Input = SelectAI(AINumber);

		// AI�� ã���� ���ڸ� *�� �ٲ���
		FindIndex = ChangeNumber(Number, Input);
		AIFindIndex = ChangeNumber(AINumber, Input);

		LineCount += ComputeLineCount(Number, FindIndex);
		AILineCount += ComputeLineCount(AINumber, AIFindIndex);

	}

}

void SetNumber(int Number[ARRAYCOUNT])
{
	for (int i = 0; i < ARRAYCOUNT; ++i)
	{
		Number[i] = i + 1;
	}
}

void Shuffle(int Number[ARRAYCOUNT])
{
	for (int i = 0; i < 100; ++i)
	{
		// 0 ~ 24 ������ ������ �� ����
		int Index1 = rand() % ARRAYCOUNT;
		int Index2 = rand() % ARRAYCOUNT;

		int Temp = Number[Index1];
		Number[Index1] = Number[Index2];
		Number[Index2] = Temp;
	}
}

void OutputInfo(int Number[ARRAYCOUNT], int LineCount)
{
	for (int i = 0; i < LINECOUNT; ++i)
	{
		for (int j = 0; j < LINECOUNT; ++j)
		{
			if (Number[i * LINECOUNT + j] == -1)
				printf("*\t");
			else
				printf("%d\t", Number[i * LINECOUNT + j]);
		}
		printf("\n");
	}

	printf("�ϼ��� �� : %d\n", LineCount);
}

int ChangeNumber(int Number[ARRAYCOUNT], int Input)
{
	for (int i = 0; i < ARRAYCOUNT; ++i)
	{
		// �Է��� ���ڰ� ���� �迭�� ���� ���
		if (Number[i] == Input)
		{
			// ���� -1�� ��� *�� ���
			Number[i] = -1;
			// ã���� ���� �迭 �ε��� ��ȯ
			return i;
		}
	}
	// ���� for������ �� ã�� ��� ����� �ͼ� -1 ��ȯ
	// �� ��� �� ã�� �� -> �̹� *�� �ٲ� ���ڸ� �Է��� ���
	return -1;
}

int ComputeLineCount(int Number[ARRAYCOUNT], int Index)
{
	// �Լ��� LineCount ���ڸ� ���� ���� ����
	// �� ���� �߰��Ǵ����� ���� return ����

	// ����, ���� üũ
	int LineCount = 0;

	int IndexX = Index % LINECOUNT;
	int IndexY = Index / LINECOUNT;

	int StarCount = 0, StarCount1 = 0;

	// �� ���� ����ŭ �ݺ�
	for (int i = 0; i < LINECOUNT; ++i)
	{
		// ������ üũ
		if (Number[IndexY * LINECOUNT + i] == -1)
			++StarCount;

		// ������ üũ
		if (Number[i * LINECOUNT + IndexX] == -1)
			++StarCount1;
	}

	if (StarCount == LINECOUNT)
		++LineCount;

	if (StarCount1 == LINECOUNT)
		++LineCount;

	// �밢�� �ε��� : 0, 6, 12, 18, 24
	if (Index % (LINECOUNT + 1) == 0)
	{
		StarCount = 0;
		for (int i = 0; i < ARRAYCOUNT; i += (LINECOUNT + 1))
		{
			if (Number[i] == -1)
				++StarCount;
		}
		if (StarCount == LINECOUNT)
			++LineCount;
	}

	// �밢�� �ε��� : 4, 8, 12, 16, 20
	if (Index % (LINECOUNT - 1) == 0 && Index != 0 && Index != (ARRAYCOUNT - 1))
	{
		StarCount = 0;
		for (int i = LINECOUNT - 1; i <= (LINECOUNT * (LINECOUNT - 1)); i += (LINECOUNT - 1))
		{
			if (Number[i] == -1)
				++StarCount;
		}
		if (StarCount == LINECOUNT)
			++LineCount;
	}

	return LineCount;
}

int SelectAI(int Number[ARRAYCOUNT])
{
	// �ϼ��� ���� ���� ���� �ε����� ���� ���� ���� �ε����� ������ ���� 2�� ����.
	int AICheckIndex = -1, AICheckStarIndex = -1;
	int AIPrevStarCount = -1;
	int StarCount = 0, StarCount1 = 0;

	// ���� ������ ���� �� ���� ���� ���� �ϼ��� �� �ִ� ���ڸ� �����ϴ� ���
	// �ƹ� �ٵ� �ϼ��� �� ���ٸ� �ٿ� ���� ���� ���� �� ����
	for (int i = 0; i < ARRAYCOUNT; ++i)
	{
		// ���� �ƴ� ��쿡�� üũ
		if (Number[i] != -1)
		{
			int IndexX = i % LINECOUNT;
			int IndexY = i / LINECOUNT;

			StarCount = 0, StarCount1 = 0;

			for (int j = 0; j < LINECOUNT; ++j)
			{
				// AI�� ������ üũ
				if (Number[IndexY * LINECOUNT + j] == -1)
					++StarCount;

				// AI�� ������ üũ
				if (Number[j * LINECOUNT + IndexX] == -1)
					++StarCount1;
			}

			// ������ ���� �ε����� �ش��ϴ� ����, �����ٿ� ����
			// *�� �� ������ ������ �ص� ����
			// ������ �����ص� *�� ������ ���� ������ *�� ������ ���Ͽ�
			// *�� �� ���� ���� ������
			if (AIPrevStarCount < StarCount)
			{
				AICheckStarIndex = i;
				AIPrevStarCount = StarCount;
			}
			else if (AIPrevStarCount < StarCount1)
			{
				AICheckStarIndex = i;
				AIPrevStarCount = StarCount1;
			}

			// �밢�� 2�ٿ� ���ؼ� üũ�Ѵ�.
			if (i % (LINECOUNT + 1) == 0)
			{
				StarCount = 0;

				for (int i = 0; i < ARRAYCOUNT; i += (LINECOUNT + 1))
				{
					if (Number[i] == -1)
						++StarCount;
				}

				if (AIPrevStarCount < StarCount)
				{
					AICheckStarIndex = i;
					AIPrevStarCount = StarCount;
				}
			}

			if (i % (LINECOUNT - 1) == 0 && i != 0 && i != (ARRAYCOUNT - 1))
			{
				StarCount = 0;

				for (int i = LINECOUNT - 1; i <= (LINECOUNT * (LINECOUNT - 1)); 
					i += (LINECOUNT - 1))
				{
					if (Number[i] == -1)
						++StarCount;
				}

				if (AIPrevStarCount < StarCount)
				{
					AICheckStarIndex = i;
					AIPrevStarCount = StarCount;
				}
			}
		}
	}

	return Number[AICheckStarIndex];
}
