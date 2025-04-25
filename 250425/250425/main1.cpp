
#include <iostream>
#include <time.h>

// ����, ����, ���� 1, 2, 3�� ���س��� > �������� �������� ���߿� ����� ���ɼ� ����
// => const int, ������ ���� ����Ͽ� ������ ���̱�

/*
������ : ����� �̸��� �ο����ִ� ���, �⺻������ 4����Ʈ(int��)
�������� ����� ���� ���� Ÿ�����ε� ��� ����
�������� �̸��� ����� ���� ���� Ÿ��, ������ ���� ����� ����� ��
������ ���� ����� �⺻���� 0���� 1�� ���ʷ� �����ϰ� ��
������ ���� ����� ���Ѵٸ� �⺻ ���� ������ ���� ����
main �Լ� �ȿ� �ۼ��� ����������, �ڵ� ����� ����� ����� ���ϱ� ������ ���� ���� ������ ���
������������ rock�� �ƴ϶� �����̸� ǥ���ϰ� ����.. �ٵ� �̸��� �ߺ��Ǽ� ����� ����
-> ���ӽ����̽��� ��� ������ ��� / enum class��� ���� ���
*/
enum ESRP : char {		// : char�� ���� 1����Ʈ�� ���� ���� (�⺻���� 4����Ʈ) -> �������� Ÿ�� ���� ����
	Scissor = 1, // Rock�� Paper�� 2, 3�� �� -> ������ ������ 1�� ����
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
		Scissor = 1, // ESPR3:Scissor�� �ϸ� �������� ��� ����
		Rock,
		Paper
	};
}

void main() {

	srand(time(0));
	rand();

	// �÷��̾��� ����, ����, �� ���� �����ϱ� ���� ������ ����
	// ���� : 1, ���� : 2, �� : 3
	int Player = 0;

	printf("1. ����\n2. ����\n3. ��\n");
	printf("���� : ");
	scanf_s("%d", &Player);

	// ������ ���� 1 ~ 3 ������ ���� �ƴ� ��� ������ ������
	// return�� �ҼӵǾ� �ִ� �Լ��� ���������� ���
	// main�� ���������� �Ǹ� ���α׷��� �����
	if (Player < 1 || Player > 3)
		return;

	// AI�� ����(1), ����(2), ��(3) �� �ϳ��� �����ϰ� ��
	int AI = rand() % 3 + 1;

	/*
	switch�� : �б� ó���� �� ���� -> � ������ ã�� �� ���� ������ �����Ǿ� ����, if���� �� �پ��ϰ� ���
	switch (��) {
		case ���:
			������ �ڵ�
			break;			// switch���� ���������� ����
		case ���:
			������ �ڵ�		// break�� ���ٸ� �ؿ� case���� ������
		case ���:
			������ �ڵ�
			break;
		default:			// if���� else�� ���� ����
			������ �ڵ�
			break;
	}
	*/

	if (AI == 1)
		printf("AI : ����\n");
	else if (AI == 2)
		printf("AI : ����\n");
	else
		printf("AI : ��\n");

	switch (AI)		// ���� �������� switch�� ���� ��, tab�� enter ������ �ڵ��ϼ�
					// namespace�� �ִ� �������� �ڵ��ϼ� �ȵ�
	{
	case Scissor:	// namespace�� �ִ� �ڵ��ϼ��� Ÿ���� int�� �ƴϱ� switch�� ���̳� case�� ����� ���� �� ����
					// ESRP2 Srp2 = ESRP2::Scissor2; �̷� ������ switch�� ���� �����س����� ��� ����
		// case �ȿ��� ���� ����� ���ÿ� �ʱ�ȭ�� �ϸ� ������ �߻���
		// -> int Number3 = 100;
		// ���� ���� �� �ʱ�ȭ�� �ϴ���, ���� ���� �κ��� �ڵ������ ���ų� �ؾ� ��
		//int Number3;
		//Number3 = 100;
		printf("AI : ����\n");
		break;
	case Rock:
	{
		/*int Number4 = 500;*/
		printf("AI : ����\n");
	}
		break;
	case Paper:
		//int Number3; // Number3�� switch���� �ڵ�� �ȿ��� ����Ǿ��� ������ ������ ���� �߻�
		//Number3 = 200;
		printf("AI : ��\n");
		break;
	}

	// �÷��̾�� AI�� ���� �̿��Ͽ� ��� ���

	// �÷��̾ �¸����� ���
	if (Player == ESRP3::Scissor && AI == 3 ||	// ���ӽ����̽� ESRP3�� ����Ͽ� �������� ���� �� ����
		Player == 2 && AI == 1 ||
		Player == 3 && AI == 2)
		printf("Player �¸�!\n");

	// �÷��̾ �¸����� ���
	else if (AI == 1 && Player == 3 ||
		AI == 2 && Player == 1 ||
		AI == 3 && Player == 2)
		printf("AI �¸�!\n");

	else
		printf("���\n");

	// ���� �ڵ� ����ȭ ��� : Player�� AI�� ���� �̿�
	int Result = Player - AI;

	if (Result == 1 || Result == -1)
		printf("Player �¸�\n");
	else if (Result == 0)
		printf("���\n");
	else
		printf("AI �¸�\n");

	printf("%d\n", ESRP2::Rock2);		// enum class�� ����ϸ� ESRP2::�� ����ؼ� ���� �ߺ��� ������ �� ����
	printf("%d\n", ESRP2::Scissor2);
	printf("%d\n", ESRP2::Paper2);

	int SRPNumber = Scissor;
	// RSPNumber = ERSP2::Scissor2;		-> ���� ���� ���(��, ����, ���� ��)�� �� �� ����� �� ���ٴ� �� ���ӽ����̽��� ����� �������� ����
	// RSPNumner = 2 - ERSP2::Scissor2;	-> ������ �� ������ ���ǿ� ���� ���, �������� ������ ���� ����

	

}