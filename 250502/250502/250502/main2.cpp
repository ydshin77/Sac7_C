
#include <iostream>
#include <fstream>

int main()
{
	// 2번 인자에 std::ios::binary 을 넣어주면 바이너리 파일이 된다.
	std::ofstream	WriteFile("Test2.txt");

	// 파일을 만들 수 있는 상태인지 체크한다.
	if (!WriteFile.is_open())
		return 0;

	WriteFile << "텍스트추가\n";
	WriteFile << "2번째 줄 텍스트추가";


	WriteFile.close();

	std::ifstream	ReadFile("Test2.txt");

	if (!ReadFile.is_open())
		return 0;

	char	Text[256] = {};

	// 개행문자 전까지 한줄을 읽어오고 개행문자는 미포함.
	ReadFile.getline(Text, 256);

	printf("%s\n", Text);

	ReadFile.getline(Text, 256);

	printf("%s\n", Text);

	// 문자만 읽어오고, 스페이스바, 개행 등의 전까지만 읽어온다.
	/*ReadFile >> Text;

	printf("%s", Text);

	ReadFile >> Text;

	printf("%s", Text);*/

	ReadFile.close();

	return 0;
}