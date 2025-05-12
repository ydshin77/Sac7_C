#pragma once

#include <assert.h>

template <typename T>
class CListNode
{
	// CLinkedList 클래스에서 CListNode 클래스의 private 멤버들에 접근이 가능함
	// template클래스이므로 아래와 같이 friend 처리를 함
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
	// Array가 더 빠름, 하지만 자리가 꽉 차서 재할당 할 때는 링크드가 더 빠름 (재할당하고 값을 복사해야 되기 때문)
	void push_back(const T& Data)
	{
		CListNode<T>* Node = new CListNode<T>;

		Node->mData = Data;

		// End노드와 End의 이전 노드 사이에 추가
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

		// Begin노드와 Begin의 다음노드 사이에 추가한다.
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

		// 지울 노드
		CListNode<T>* DeleteNode = mEnd->mPrev;

		// 지울 노드의 이전노드
		CListNode<T>* Prev = DeleteNode->mPrev;

		// 지울노드의 이전노드와 End노드를 연결한다.
		Prev->mNext = mEnd;
		mEnd->mPrev = Prev;

		// 지울노드의 메모리를 제거한다.
		delete	DeleteNode;

		--mSize;
	}

	void pop_front()
	{
		assert(mSize > 0);

		// 지울 노드
		CListNode<T>* DeleteNode = mBegin->mNext;

		// 지울 노드의 다음노드
		CListNode<T>* Next = DeleteNode->mNext;

		// 지울노드의 이전노드와 End노드를 연결한다.
		mBegin->mNext = Next;
		Next->mPrev = mBegin;

		// 지울노드의 메모리를 제거한다.
		delete	DeleteNode;

		--mSize;
	}

};

