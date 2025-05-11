#include <iostream>
#include <fstream>

int main()
{
	// 파일 스트림 생성 (파일 쓰기)
	std::ofstream WriteFile("Test2.txt");

	// 파일을 만들 수 있는 상태인지 체크 -> 파일 스트림이 안열려있으면 종료
	if (!WriteFile.is_open())
		return 0;

	// 텍스트 쓰기
	WriteFile << "텍스트추가\n";
	WriteFile << "2번째 줄 텍스트추가";

	// 파일 스트림 닫기
	WriteFile.close();

	// ===============================
	
	// 파일 스트림 생성(파일 읽기)
	std::ifstream ReadFile("Test2.txt");

	// 파일 스트림이 안열려있으면 종료
	if (!ReadFile.is_open())
		return 0;

	// 텍스트 읽어오기
	char Text[256] = {};
	
	// 개행 문자 전까지 한 줄 읽기 (개행문자는 미포함)
	ReadFile.getline(Text, 256);
	// 출력 : 텍스트추가
	printf("%s\n", Text);

	ReadFile.getline(Text, 256);
	// 출력 : 2번째 줄 텍스트추가
	printf("%s\n", Text);

	// 파일 스트림 닫기
	ReadFile.close();

	return 0;
}