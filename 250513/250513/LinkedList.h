#pragma once

#include <assert.h>

template <typename T>
class CListNode
{
	// CLinkedList Ŭ�������� CListNode Ŭ������
	// private ����鿡 ������ �����ϴ�.
	// template Ŭ�����̹Ƿ� �Ʒ��� ���� friend ó���� �Ѵ�.
	template <typename T>
	friend class CLinkedList;

	template <typename T>
	friend class CListIterator;

	template <typename T>
	friend class CListReverseIterator;

private:
	CListNode()
	{
	}

	~CListNode()
	{
	}

private:
	T	mData;
	CListNode<T>* mNext = nullptr;
	CListNode<T>* mPrev = nullptr;
};

template <typename T>
class CListIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListIterator()
	{
	}

	CListIterator(CListNode<T>* Node) :
		mNode(Node)
	{
	}

	~CListIterator()
	{
	}

private:
	CListNode<T>* mNode = nullptr;

public:
	bool operator == (const CListIterator<T>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListIterator<T>& iter)	const
	{
		return mNode != iter.mNode;
	}

	bool operator == (const CListReverseIterator<T>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListReverseIterator<T>& iter)	const
	{
		return mNode != iter.mNode;
	}

	const CListIterator<T>& operator ++ ()
	{
		mNode = mNode->mNext;

		return *this;
	}

	const CListIterator<T>& operator ++ (int)
	{
		mNode = mNode->mNext;

		return *this;
	}

	const CListIterator<T>& operator -- ()
	{
		mNode = mNode->mPrev;

		return *this;
	}

	const CListIterator<T>& operator -- (int)
	{
		mNode = mNode->mPrev;

		return *this;
	}

	T& operator * ()
	{
		return mNode->mData;
	}

	const T& operator * ()	const
	{
		return mNode->mData;
	}
};

template <typename T>
class CListReverseIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListReverseIterator()
	{
	}

	CListReverseIterator(CListNode<T>* Node) :
		mNode(Node)
	{
	}

	~CListReverseIterator()
	{
	}

private:
	CListNode<T>* mNode = nullptr;

public:
	bool operator == (const CListReverseIterator<T>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListReverseIterator<T>& iter)	const
	{
		return mNode != iter.mNode;
	}

	bool operator == (const CListIterator<T>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListIterator<T>& iter)	const
	{
		return mNode != iter.mNode;
	}

	const CListReverseIterator<T>& operator ++ ()
	{
		mNode = mNode->mPrev;

		return *this;
	}

	const CListReverseIterator<T>& operator ++ (int)
	{
		mNode = mNode->mPrev;

		return *this;
	}

	const CListReverseIterator<T>& operator -- ()
	{
		mNode = mNode->mNext;

		return *this;
	}

	const CListReverseIterator<T>& operator -- (int)
	{
		mNode = mNode->mNext;

		return *this;
	}

	T& operator * ()
	{
		return mNode->mData;
	}

	const T& operator * ()	const
	{
		return mNode->mData;
	}
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
		CListNode<T>* Node = mBegin;

		while (Node != nullptr)
		{
			CListNode<T>* Next = Node->mNext;

			delete Node;

			Node = Next;
		}
	}

public:
	typedef CListIterator<T>	iterator;
	typedef const CListIterator<T>	const_iterator;

	typedef CListReverseIterator<T>	reverse_iterator;
	typedef const CListReverseIterator<T>	const_reverse_iterator;

private:
	CListNode<T>* mBegin;
	CListNode<T>* mEnd;
	int			mSize = 0;

public:
	void push_back(const T& Data)
	{
		CListNode<T>* Node = new CListNode<T>;

		Node->mData = Data;

		// End���� End�� ������� ���̿� �߰��Ѵ�.
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

	// iter�� iter�� ���� ��� ���̿� ���ο� ��带 ����� �����͸� �����Ͽ�
	// �߰��Ѵ�.
	void insert(const_iterator& iter, const T& Data)
	{
		assert(iter != end());

		CListNode<T>* Next = iter.mNode->mNext;

		CListNode<T>* NewNode = new CListNode<T>;

		NewNode->mData = Data;

		iter.mNode->mNext = NewNode;
		NewNode->mPrev = iter.mNode;

		NewNode->mNext = Next;
		Next->mPrev = NewNode;

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

	int size()	const
	{
		return mSize;
	}

	bool empty()	const
	{
		return mSize == 0;
	}

	void clear()
	{
		// Begin�� ���������� End�� ���������� �����Ѵ�.
		CListNode<T>* Node = mBegin->mNext;

		while (Node != mEnd)
		{
			CListNode<T>* Next = Node->mNext;

			delete Node;

			Node = Next;
		}

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;

		mSize = 0;
	}

	iterator begin()	const
	{
		iterator	iter(mBegin->mNext);
		return iter;
	}

	const_iterator cbegin()	const
	{
		const_iterator	iter(mBegin->mNext);
		return iter;
	}

	reverse_iterator rbegin()	const
	{
		reverse_iterator	iter(mEnd->mPrev);
		return iter;
	}

	const_reverse_iterator crbegin()	const
	{
		const_reverse_iterator	iter(mEnd->mPrev);
		return iter;
	}

	iterator end()	const
	{
		iterator	iter(mEnd);
		return iter;
	}

	const_iterator cend()	const
	{
		const_iterator	iter(mEnd);
		return iter;
	}

	reverse_iterator rend()	const
	{
		reverse_iterator	iter(mBegin);
		return iter;
	}

	const_reverse_iterator crend()	const
	{
		const_reverse_iterator	iter(mBegin);
		return iter;
	}

	// ���ŵ� ����� ���� ��带 ������ �ִ� iterator�� ��ȯ�Ѵ�.
	iterator erase(const T& Data)
	{
		iterator	iter;
		iterator	iterEnd = end();

		for (iter = begin(); iter != iterEnd; ++iter)
		{
			if (*iter == Data)
			{
				return erase(iter);
			}
		}

		return end();
	}

	iterator erase(const iterator& iter)
	{
		assert(iter.mNode != nullptr && iter.mNode != mBegin && iter.mNode != mEnd);

		// ���� ����� �������� ������带 ���´�.
		CListNode<T>* Prev = iter.mNode->mPrev;
		CListNode<T>* Next = iter.mNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		// ��带 �����Ѵ�.
		delete iter.mNode;

		--mSize;

		return iterator(Next);
	}

	// Start�� End ������ ��带 �����Ѵ�.
	iterator erase(const_iterator& Start, const_iterator& End)
	{
		iterator _Start = Start;
		iterator _End = End;

		iterator	iter;
		iterator	iterEnd = end();

		bool	Find = false;

		for (iter.mNode = Start.mNode; iter != iterEnd; ++iter)
		{
			if (iter == End)
			{
				Find = true;
				break;
			}
		}

		if (!Find)
		{
			_Start = End;
			_End = Start;
		}

		// B 1 2 3 4 5 6 7 8 E
		CListNode<T>* Prev = _Start.mNode->mPrev;
		CListNode<T>* Next = _End.mNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		iterator	result(Next);

		while (_Start != _End)
		{
			Next = _Start.mNode->mNext;
			delete _Start.mNode;
			_Start.mNode = Next;
			--mSize;
		}

		// _End�� ������ �ʾұ� ������ ���⿡�� �����ش�.
		delete	_Start.mNode;
		--mSize;

		return result;
	}
};

