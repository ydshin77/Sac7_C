
#include <iostream>

int main()
{
	/*
	File Stream�� ���� FILE Ÿ���� ������ ������ �ְ� ���ش�.
	File Stream�� ������ ����ų� �о�� �� �ش� ���ϰ� ����� �����̴�.
	������ : ����̺���� ��ü ��θ� ǥ���ϴ� ����̴�.
	����� : ���� ������ �������� ������ ��α����� ������� ��θ� ǥ���ϴ�
	����̴�.
	*/
	FILE* FileStream = nullptr;

	// 1�������� FileStream�� ������ش�.
	// 2�����ڴ� ������ ��ΰ� ���µ� ������, ����� ���
	// �־ �������. ����θ� ����� ��� ���� ������Ʈ�� �ִ�
	// ��θ� �������� ����θ� �����Ѵ�. ����δ� ������Ʈ ������
	// �ִ� ��θ� �������� �����Ѵ�.
	// 3�������� Mode�� ������ ����ų� ���� �� � ������ ����ų� ������
	// �ɼ��� �����ϴ� ����̴�.
	// ù��° : r, w, a ���� �ϳ��� ����.
	// r : �б� w : ���� a : �߰�
	// �ι�° : t, b, +
	// t : �ؽ�Ʈ���� b : ���̳ʸ�����
	/*
	���	|	�ǹ�			|	����X	|	����O	|	�б�	|	����	|	�߰�
	r	|	�б�			|	�����߻�	|	���Ͽ���	|	O	|	X	|	X
	w	|	����			|	����		|	�����	|	X	|	O	|	X
	a	|	�߰�			|	����		|	�����߰�	|	X	|	O	|	O
	r+	|	�б�/����		|	�����߻�	|	���Ͽ���	|	O	|	O	|	X
	w+	|	�б�/����		|	���λ���	|	�����	|	O	|	O	|	X
	a+	|	�б�/�߰�		|	���λ���	|	����,�߰�	|	O	|	O	|	O
	rt	|	�ؽ�Ʈ�б�	|	�����߻�	|	���Ͽ���	|	O	|	X	|	X
	wt	|	�ؽ�Ʈ����

	*/
	fopen_s(&FileStream, "Test.txt", "wt");

	// ���� ��Ʈ���� ���� ��� ������ ���� �� �ִٴ� �ǹ��̴�.
	if (FileStream)
	{
		// ���Ͽ� �ؽ�Ʈ�� �������ִ� �Լ�.
		// fputc �� ���� �ϳ��� �����Ѵ�.
		fputc('A', FileStream);

		fputs("File Stream Test\n", FileStream);
		fputs("Stream Test", FileStream);


		//fputs("\xEF\xBB\xBF", FileStream);

		//// fputs�� ���ڿ��� �����Ѵ�.
		//fputs("���ڿ� �׽�Ʈ", FileStream);

		fclose(FileStream);
	}

	fopen_s(&FileStream, "Test.txt", "rt");

	if (FileStream)
	{
		// fgetc : ���� 1���� �о�´�.
		char FirstText = fgetc(FileStream);

		printf("%c", FirstText);
		
		char	Text[256] = {};

		// ���๮�ڰ� �ִ°����� �о�´�.
		// ���� ���๮�� ���� ������ ���� �����ߴٸ� �ű������
		// �о���� �ȴ�.
		fgets(Text, 256, FileStream);

		printf("%s", Text);

		fgets(Text, 256, FileStream);

		printf("%s", Text);

		fclose(FileStream);
	}

	return 0;
}