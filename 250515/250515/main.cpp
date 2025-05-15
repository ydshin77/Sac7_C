
#include <iostream>
// RTTI�� �̿��� Ÿ���� ������ �� �� �ְ� �ϴ� ���
#include <typeinfo>

/*
- ���
Ŭ������ �θ�� �ڽ��� ���踦 ������ �� ����
�ڽ� Ŭ������ �θ� Ŭ������ ����� �����Ͽ� �����ϰ� ��

���� ��� ���� (���� ���� Ŭ����)
�θ� Ŭ������ �ڽ� Ŭ������ ��ӹ��� �� ����

- ��� �������� �����ڿ� �Ҹ����� ȣ�� ���� (�� �ϱ�!!)
������ : �θ� -> �ڽ�
�Ҹ��� : �ڽ� -> �θ�

: �ڿ� ���������� ��� ���� (public, private, protected)
private ����� �ް� �Ǹ� Ŭ���� �ܺο����� �θ��� ����� ���� �Ұ���, ���ο����� ���� ����

- private
: Ŭ���� �ܺο��� ���� �Ұ���, Ŭ���� ���ο����� ���� ����
: �ڽ� Ŭ������ ���ο����� ������ �Ұ���

- protected
: Ŭ���� �ܺο��� ���� �Ұ���, Ŭ���� ���ο����� ���� ����
: �ڽ�Ŭ������ ���ο����� ���� ���� (private���� ������)

- RTTI(Run Time Type Information)
: �ǽð����� Ÿ�� ������ ���� �� �ְ� ���ִ� ���

- ������
: ��� ���迡 �ִ� Ŭ���� ���̿� ���� ����ȯ�� ������ ������ ����

- ��ĳ����
: �ڽ� -> �θ� ����ȯ

- �ٿ�ĳ����
: �θ� -> �ڽ� ����ȯ
: �޸� �뷮 �������� �ٿ�ĳ���� ���� �����ؾ���

- ����� ����
: Ŭ������ ���뼺�� ������
	> �������� ����� �θ� �ΰ�, �� �ڽ��� Ư¡�� �ڽ� Ŭ������ ����� ���� ���
: �������� �̿��Ͽ� �θ� Ÿ�������� ����ȯ�� �����ϱ� ������,
  �θ� Ÿ���� �����ϴ� �ϳ��� ������� ���� �ڽ� Ŭ������ ��ü���� ������ �� ����
	 
*/

class CParent
{
public:
	CParent()
	{
		printf("CParent ������\n");
	}

	/*
	- �����Լ� (� ������ �����ϴ��� �� �˱�!!)
	�Ҹ��ڳ� �Ϲ� Ŭ���� ����Լ� �տ� virtual Ű���带 �ٿ��ָ� �ش� �Լ��� �����Լ��� ��
	�����Լ��� ������ �ִ� Ŭ������ �����Լ����̺��� ������ ��
	�θ� �����Լ��� �ִ� �ڽ�Ŭ������ �����Լ����̺��� ������ ��
	Ŭ������ �����Լ����̺��� ������
	�����Լ��� ������ �ִ� Ŭ������ �̿��ؼ� ��ü�� �����ϸ�
	__vfptr �̶�� ������ ������ �ڵ����� ������ ��
	�� ������ ������ �ش� Ŭ������ �����Լ����̺��� �޸� �ּҸ� ������ ��
	
	�����Լ� ���̺��� �����Լ��� �ּҸ� ��� ����
	�����Լ��� ȣ���ϰ� �Ǹ� ���� �ش� �Լ��� �ּҸ� �����Լ����̺��� �����Ͽ� ������,
	�� �ּҸ� �̿��Ͽ� �Լ��� ȣ�����ִ� �����
	
	������, �����Լ�, ���̳���ĳ��Ʈ > ����/���������ʼ�!!
	��ȣ��Ǵ���, vfptr�� ���ִ���

	�� Ŭ���� 1����Ʈ , �����Լ��� �ִ� Ŭ���� 8����Ʈ > �̰ŵ� �ʼ�!!
	*/
	~CParent()
	{
		printf("CParent �Ҹ���\n");
	}

public:
	int mA = 10;
	
private:
	int mB = 20;
	
protected:
	int mZ = 30;

public:
	virtual void Output()
	{
		mZ = 1123;
		printf("CParent Output Function\n");
	}

	virtual void OutputOverride()
	{
	}

	// �߻�Ŭ���� : ���������Լ��� ������ �ִ� Ŭ������ �߻�Ŭ���� ��� �Ѵ�.
	// �߻�Ŭ������ ��ü ������ �Ұ����ϴ�.
	// ���� ���������Լ��� ������ �ִ� Ŭ������ ��ӹ޴� �ڽ�Ŭ�������� ���������Լ���
	// �����ǰ� ���ٸ� �ڽ�Ŭ������ �߻�Ŭ������ �ȴ�.
	// ���������Լ��� �ڽ�Ŭ�������� ������ ������ �ؾ� �Ѵ�.
	virtual void OutputPure() = 0;
	// �Լ� �ڿ� abstract�� �ٿ��� ���������Լ��� ���� �� �ִ�.
	virtual void OutputPure1()	abstract
	{
	}

	void Output1()
	{
		printf("CParent Output1 Function\n");
	}
};

class CChild :
	public CParent
{
public:
	CChild()
	{
		mA = 500;
		//mB = 400;
		mZ = 600;
		printf("CChild ������\n");
	}

	~CChild()
	{
		printf("CChild �Ҹ���\n");
	}

public:
	int	mC = 30;

public:
	// �Լ� ������(�Լ� �������̵�). �θ�Ŭ������ �Լ��� ������ ������ ���·�
	// �ڽ�Ŭ������ ������ �ϴ°��� ���Ѵ�.
	// final Ű����� �� Ŭ������ �ڽ�Ŭ�������� ���̻� �� �Լ��� ������ �� ��
	// ���ٴ� �ǹ��̴�.
	void Output()	final
	{
		printf("CChild Output Function\n");
	}

	virtual void OutputPure()
	{
	}

	virtual void OutputPure1()
	{
	}

	// override�� ��������� �� �Լ��� �θ��� �Լ��� ������ �� �Լ��� �νĽ��Ѽ�
	// �θ� ���� �Լ��� ����� �Ǹ� ������ �߻��Ѵ�.
	/*void OutputOverride()	override
	{
	}

	void Output3()	override
	{
	}*/

};

class CChild1 :
	public CParent
{
public:
	CChild1()
	{
		printf("CChild1 ������\n");
	}

	~CChild1()
	{
		printf("CChild1 �Ҹ���\n");
	}

public:
	int mD = 30;
	int mE = 40;

public:
	// �Լ� ������(�Լ� �������̵�). �θ�Ŭ������ �Լ��� ������ ������ ���·�
	// �ڽ�Ŭ������ ������ �ϴ°��� ���Ѵ�.
	/*void Output()
	{
		printf("CChild1 Output Function\n");
	}*/

	virtual void OutputPure()
	{
	}

	virtual void OutputPure1()
	{
	}

};

class CChildChild :
	public CChild
{
public:
	CChildChild()
	{
		printf("CChildChild ������\n");
	}

	~CChildChild()
	{
		printf("CChildChild �Ҹ���\n");
	}

public:
	int mD = 40;

public:
	// �Լ� ������(�Լ� �������̵�). �θ�Ŭ������ �Լ��� ������ ������ ���·�
	// �ڽ�Ŭ������ ������ �ϴ°��� ���Ѵ�.
	/*void Output()
	{
		printf("CChildChild Output Function\n");
	}*/

};

// Ŭ������ ������ �� Ŭ���� �̸� �ڿ� abstract �� �ٿ��ָ� �ش� Ŭ������
// �߻�Ŭ������ �ȴ�.
class CEmpty	abstract
{
public:
	CEmpty()
	{
	}

	~CEmpty()
	{
	}

public:
	int	mA;
};

// Ŭ���� �ڿ� final Ű���带 �ٿ��ָ� ���̻� ����� �� ���� Ŭ������ �ȴ�.
class CEmpty1 final
{
public:
	CEmpty1()
	{
	}

	virtual ~CEmpty1()
	{
	}

public:
	int	mA;
};

//class CEmpty2 : public CEmpty1
//{
//};


int main()
{
	// CChild Ÿ���� ��ü�� �����ϰ� �� �ּҸ� CParent ������ Ÿ���� ������
	// ��Ƶд�.
	CParent* Parent11[2];

	Parent11[0] = new CChild;
	Parent11[1] = new CChild1;

	CChild1* Child11 = dynamic_cast<CChild1*>(Parent11[0]);

	Parent11[0]->Output();
	Parent11[1]->Output();

	// CParent ������ Ÿ�Կ� �ִ� �ּҸ� �����Ѵ�.
	delete Parent11[0];
	delete Parent11[1];

	system("cls");

	printf("Empty Size : %d\n", sizeof(CEmpty));
	printf("Empty1 Size : %d\n", sizeof(CEmpty1));
	//CParent	parent, parent1;
	//CChild	child, child1;
	/*CChild	child;

	child.Output();
	child.Output1();*/

	return 0;

	//CParent	Parent;
	//CChild		Child;
	//CChildChild		ChildChild;

	//Child.Output();
	//Child.mA = 120;
	//Child.mB = 130;
	//Child.mZ = 1111;
	// typeid(���� Ȥ�� Ÿ��) �� �־��ָ� type_info Ÿ���� ��ü�� ���´�. -> RTTI �̿�
	//type_info
	//typeid(Child).;
	// ��� : class CChild
	//printf("TypeName : %s\n", typeid(Child).name());

	CChild Child;

	CChild	Child;
	// Child��ü�� CParent ������Ÿ������ ��ĳ���� �Ͽ���.
	CParent* Parent = &Child;

	// Child1 ������ Ÿ������ �ٿ�ĳ���� �Ͽ���.
	CChild1* Child1 = (CChild1*)Parent;

	// reinterpret�� ����
	int	Addr = (int)Child1;

	printf("�޸� : %p\n", &Child);
	printf("�޸� : %p\n", Parent);
	printf("�޸� : %p\n", Child1);


	/*
	C++�� ����ȯ (����������)
	static_cast : �Ϲ����� Ÿ�� ����ȯ. ��κ��� ����ȯ�� ����
	const_cast : const �Ӽ��� ������ �� ���
	dynamic_cast : ��Ÿ�ӿ� Ÿ���� �˻��Ͽ� ����ȯ�� ������ (RTTI ����� Ȱ���� ��)
	: Ÿ���� �������̶�� ����ȯ, �ƴ϶�� nullptr�� ��ȯ
	reinterpret_cast : ��Ʈ ������ ���� ����ȯ (C��Ÿ��������ȯ)
	*/

	//Addr = static_cast<int>(Child1);
	Addr = static_cast<int>(3.14f);

	const int cNumber = 500;

	//int* Addr2 = &cNumber;
	int* Addr1 = const_cast<int*>(&cNumber);

	CParent* Parent1 = dynamic_cast<CParent*>(&Child);

	printf("dynamic cast Parent1 = %p\n", Parent1);

	// ���� �߻� : ���� Ŭ���� �����̾�� �� -> ���� �Լ� �� ����
	/*CChild1* dnChild1 = dynamic_cast<CChild1*>(Parent1);

	printf("dynamic cast Parent1 = %p\n", dnChild1);*/



	return 0;
}