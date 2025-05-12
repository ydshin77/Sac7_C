#pragma once

#include <assert.h>

template <typename T>
class CListNode
{
	// CLinkedList Ŭ�������� CListNode Ŭ������ private ����鿡 ������ ������
	// templateŬ�����̹Ƿ� �Ʒ��� ���� friend ó���� ��
	template <typename T>
	friend class CLinkedList;

private:
	CListNode()
	{

	}
	~CListNode()
	{

	}

private:
	T mData;
	CListNode<T>* mNext = nullptr;
	CListNode<T>* mPrev = nullptr;
};

template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		mBegin = new CListNode<T>;
		mEnd = new CListNode<T>;

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}
	
	~CLinkedList()
	{

	}

private:
	CListNode<T>* mBegin;
	CListNode<T>* mEnd;
	int mSize = 0;

public:
	// Array�� �� ����, ������ �ڸ��� �� ���� ���Ҵ� �� ���� ��ũ�尡 �� ���� (���Ҵ��ϰ� ���� �����ؾ� �Ǳ� ����)
	void push_back(const T& Data)
	{
		CListNode<T>* Node = new CListNode<T>;

		Node->mData = Data;

		// End���� End�� ���� ��� ���̿� �߰�
		CListNode<T>* Prev = mEnd->mPrev;

		Prev->mNext = Node;
		Node->mPrev = Prev;

		Node->mNext = mEnd;
		mEnd->mPrev = Node;

		++mSize;
	}

	void push_front(const T& Data)
	{
		CListNode<T>* Node = new CListNode<T>;

		Node->mData = Data;

		// Begin���� Begin�� ������� ���̿� �߰��Ѵ�.
		CListNode<T>* Next = mBegin->mNext;

		mBegin->mNext = Node;
		Node->mPrev = mBegin;

		Node->mNext = Next;
		Next->mPrev = Node;

		++mSize;
	}
	
	void pop_back()
	{
		assert(mSize > 0);

		// ���� ���
		CListNode<T>* DeleteNode = mEnd->mPrev;

		// ���� ����� �������
		CListNode<T>* Prev = DeleteNode->mPrev;

		// �������� �������� End��带 �����Ѵ�.
		Prev->mNext = mEnd;
		mEnd->mPrev = Prev;

		// �������� �޸𸮸� �����Ѵ�.
		delete	DeleteNode;

		--mSize;
	}

	void pop_front()
	{
		assert(mSize > 0);

		// ���� ���
		CListNode<T>* DeleteNode = mBegin->mNext;

		// ���� ����� �������
		CListNode<T>* Next = DeleteNode->mNext;

		// �������� �������� End��带 �����Ѵ�.
		mBegin->mNext = Next;
		Next->mPrev = mBegin;

		// �������� �޸𸮸� �����Ѵ�.
		delete	DeleteNode;

		--mSize;
	}

};

