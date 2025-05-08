
#include <iostream>

int main()
{
	/*
	File Stream을 만들어서 FILE 타입의 변수에 가지게 있게 해준다.
	File Stream은 파일을 만들거나 읽어올 때 해당 파일과 연결된 변수이다.
	절대경로 : 드라이브부터 전체 경로를 표현하는 방식이다.
	상대경로 : 현재 폴더를 기준으로 목적지 경로까지의 상대적인 경로를 표현하는
	방식이다.
	*/
	FILE* FileStream = nullptr;

	// 1번인자의 FileStream을 만들어준다.
	// 2번인자는 파일의 경로가 들어가는데 절대경로, 상대경로 어떤걸
	// 넣어도 상관없다. 상대경로를 사용할 경우 현재 프로젝트가 있는
	// 경로를 기준으로 상대경로를 지정한다. 상대경로는 프로젝트 파일이
	// 있는 경로를 기준으로 지정한다.
	// 3번인자의 Mode는 파일을 만들거나 읽을 때 어떤 파일을 만들거나 읽을지
	// 옵션을 지정하는 기능이다.
	// 첫번째 : r, w, a 셋중 하나를 쓴다.
	// r : 읽기 w : 쓰기 a : 추가
	// 두번째 : t, b, +
	// t : 텍스트파일 b : 바이너리파일
	/*
	모드	|	의미			|	파일X	|	파일O	|	읽기	|	쓰기	|	추가
	r	|	읽기			|	오류발생	|	파일열기	|	O	|	X	|	X
	w	|	쓰기			|	생성		|	덮어쓰기	|	X	|	O	|	X
	a	|	추가			|	생성		|	내용추가	|	X	|	O	|	O
	r+	|	읽기/쓰기		|	오류발생	|	파일열기	|	O	|	O	|	X
	w+	|	읽기/쓰기		|	새로생성	|	덮어쓰기	|	O	|	O	|	X
	a+	|	읽기/추가		|	새로생성	|	열기,추가	|	O	|	O	|	O
	rt	|	텍스트읽기	|	오류발생	|	파일열기	|	O	|	X	|	X
	wt	|	텍스트쓰기

	*/
	fopen_s(&FileStream, "Test.txt", "wt");

	// 파일 스트림이 있을 경우 파일을 만들 수 있다는 의미이다.
	if (FileStream)
	{
		// 파일에 텍스트를 저장해주는 함수.
		// fputc 는 문자 하나를 저장한다.
		fputc('A', FileStream);

		fputs("File Stream Test\n", FileStream);
		fputs("Stream Test", FileStream);


		//fputs("\xEF\xBB\xBF", FileStream);

		//// fputs는 문자열을 저장한다.
		//fputs("문자열 테스트", FileStream);

		fclose(FileStream);
	}

	fopen_s(&FileStream, "Test.txt", "rt");

	if (FileStream)
	{
		// fgetc : 문자 1개를 읽어온다.
		char FirstText = fgetc(FileStream);

		printf("%c", FirstText);
		
		char	Text[256] = {};

		// 개행문자가 있는곳까지 읽어온다.
		// 만약 개행문자 없이 파일의 끝에 도달했다면 거기까지만
		// 읽어오게 된다.
		fgets(Text, 256, FileStream);

		printf("%s", Text);

		fgets(Text, 256, FileStream);

		printf("%s", Text);

		fclose(FileStream);
	}

	return 0;
}