
#include <iostream>
#include <list>
#include "LinkedList.h"

// �̳�Ŭ���� : Ŭ���� �ȿ� ��������ִ� Ŭ������ �ǹ��Ѵ�.
class COutClass
{
public:
	class CInClass
	{
	public:
		int		mNum = 10;
	};
};

// typedef �� ���� Ÿ���� �̸��� �ٸ� �̸����� ����� �� �ְ� ���ִ� ����̴�.
typedef int	MyInt;

int main()
{
	COutClass::CInClass	InClass;

	COutClass	OutClass;

	InClass.mNum = 100;

	int	Number = 100;
	MyInt	Number1 = 200;

	Number1 = ++Number;

	CLinkedList<int>	IntList;

	for (int i = 0; i < 10; ++i)
	{
		IntList.push_back(i + 1);
	}

	CLinkedList<int>::iterator	iter;
	CLinkedList<int>::iterator	iterEnd = IntList.end();

	CLinkedList<int>::iterator	StartIter = IntList.begin();
	++StartIter;
	++StartIter;

	CLinkedList<int>::iterator	EndIter = StartIter;
	++EndIter;
	++EndIter;
	++EndIter;

	IntList.insert(StartIter, 100);
	//iter = IntList.erase(EndIter, StartIter);

	//printf("Erase Next : %d\n", *iter);

	for (iter = IntList.begin(); iter != iterEnd; ++iter)
	{
		if (*iter == 5)
		{
			iter = IntList.erase(iter);
			--iter;
			continue;
		}

		printf("%d\n", *iter);
	}

	CLinkedList<int>::reverse_iterator	riter;
	CLinkedList<int>::reverse_iterator	riterEnd = IntList.rend();

	for (riter = IntList.rbegin(); riter != riterEnd; ++riter)
	{
		printf("%d\n", *riter);
	}

	/*CLinkedList<int>::iterator	iter;
	CLinkedList<int>::const_iterator	citer;

	IntList.cbegin();*/


	/*std::list<int>	IntList1;
	std::list<int>::iterator	iter;*/

	return 0;
}