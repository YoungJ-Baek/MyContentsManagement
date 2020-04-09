#pragma once
#include <iostream>
using namespace std;

// Tree�� �����ϴ� Node (node data, left ������, right ������)
template<typename T>
struct Node
{
	T data;
	Node* left;
	Node* right;
};

// Binary Search Tree 
template<typename T>
class BinarySearchTree
{
public:
	// ������
	BinarySearchTree();
	// �Ҹ���
	~BinarySearchTree();

	/**
	*	@brief	Tree�� Empty���� Ȯ��
	*	@pre	none
	*	@post	none
	*	@return	Tree�� ��������� true����, �ƴϸ� false ����
	*/
	bool IsEmpty()const;

	/**
	*	@brief	Tree�� ����
	*	@pre	none
	*	@post	none
	*/
	void MakeEmpty();

	/**
	*	@brief	Tree�� node�� �� ������ Ȯ����
	*	@pre	none
	*	@post	none
	*	@return	Tree�� node ������ ����
	*/
	int GetLength() const;

	/**
	*	@brief	Tree�� �� node�� �߰��Ѵ�
	*	@pre	T�� ��ü�� ����
	*	@post	Tree�� �� node�� �߰���
	*/
	void Add(T item);

	/**
	*	@brief	Tree���� ������� �ϴ� node�� ã�� ����
	*	@pre	T�� ��ü�� ����
	*	@post	Tree���� �Է��� node�� ������
	*/
	void DeleteItem(T item);

	/**
	*	@brief	�Է��� ���� node�� Tree���� �˻���
	*	@pre	ã���� �ϴ� item�� �˻������ ���� found ����
	*	@post	node�� Tree�� �ִ��� �˻������ �˷���
	*/
	void RetrieveItem(T& item, bool &found)const;

	/**
	*	@brief	Tree�� node�� ��ũ���� ����Ѵ�.
	*	@pre	none
	*	@post	��ũ���� Tree�� InOrder, PreOrder, PostOrder ������� ���� ��µ�.
	*/
	void PrintTree(ostream &out)const;

private:
	Node<T>* root;		// Node Ÿ���� root
};

// ������
template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = NULL;
}

//�Ҹ���
template<typename T>
BinarySearchTree<T>::~BinarySearchTree() { MakeEmpty(); }

// Tree�� ����ִ��� Ȯ��
template<typename T>
bool BinarySearchTree<T>::IsEmpty()const
{
	if (root == NULL)			// root ��尡 NULL�� ��� true ����
		return true;
	else
		return false;			// root ��尡 NULL�� �ƴ� ��� false ����
}

// Tree�� ���
template<typename T>
void BinarySearchTree<T>::MakeEmpty()
{
	MakeEmptyTree(root);				// Tree �ʱ�ȭ �Լ� ȣ��
}

// Tree�� node������ �˷���
template<typename T>
int BinarySearchTree<T>::GetLength()const
{
	return CountNodes(root);			// node ������ ���� �Լ� ȣ��
}

// Tree�� ���ο� node �߰�
template<typename T>
void BinarySearchTree<T>::Add(T item)
{
	Insert(root, item);					// �� node �߰��ϴ� �Լ� ȣ��
}

// Tree�� node�� ����
template<typename T>
void BinarySearchTree<T>::DeleteItem(T item)
{
	Delete(root, item);					// �����ϴ� node �����ϴ� �Լ��� ȣ��
}

// Tree���� ã���� �ϴ� ���� node�� �˻�
template<typename T>
void BinarySearchTree<T>::RetrieveItem(T& item, bool &found)const
{
	Retrieve(root, item, found);		// Tree �˻� �Լ� ȣ��
}

// Tree�� node�� ������ ������ �����
template<typename T>
void BinarySearchTree<T>::PrintTree(ostream &out)const
{
	cout << "[InOrder]" << endl;
	PrintInOrderTraversal(root, out);			// InOrder ������� ���
	cout << endl << "[PreOrder]" << endl;
	PrintPreOrderTraversal(root, out);			// PreOrder ������� ���
	cout << endl << "[PostOrder]" << endl;
	PrintPostOrderTraversal(root, out);			// PostOrder ������� ���
}

/////////////////////////////Global functions//////////////////////////
// Tree�� �ʱ�ȭ�ϴ� �Լ�
////////modify
template<typename T>
void MakeEmptyTree(Node<T>*& root)
{
	if (root == NULL)
		return;
	else
	{
		MakeEmptyTree(root->left);
		MakeEmptyTree(root->right);
		delete root;
	}
}

// Tree�� node ������ ���� �Լ�
template<typename T>
int CountNodes(Node<T>* root)
{
	if (root == NULL)		// root ��尡 null�ϰ�� 0�� ����
		return 0;
	else
		return CountNodes(root->left) + CountNodes(root->right) + 1;		// ����� ����, �����ʿ� ���� ����� ȣ��� root�� �ش��ϴ� 1�� ���ؼ� ���� ����
}

// BinarySearchTree�� ���ο� ��� �߰�
template<typename T>
void Insert(Node<T>*& root, T item)
{
	if (root == NULL)				// root�� null�� ��� 
	{
		root = new Node<T>;	// root ��� ����
		root->left = NULL;			// root ����̹Ƿ� left�� right�� NULL�� ����
		root->right = NULL;
		root->data = item;			// root ����� ��
	}
	else if (root->data > item)		// root�� �����ϰ�, �� ���� ���ο� item ������ Ŭ ��
		Insert(root->left, item);	// root�� �������� Insert �Լ� �ٽ� ȣ��
	else if (root->data < item)		// root�� �����ϰ�, �� ���� ���ο� item ������ ���� ��
		Insert(root->right, item);	// root�� ���������� Insert �Լ� �ٽ� ȣ��
}

// ���� ū ���� ã�� �Լ� 
template<typename T>
void GetPredecessor(Node<T> *root, T& item)
{
	while (root->right != NULL)			// root�� �������� ������ ���
		root = root->right;				// root�� ������ ��尪�� root�� ������ �Ѵ�
	item = root->data;					// root ����� ���� item�� �����Ѵ�.
}

// ������� ��带 ã���� ������ Ʈ������ �� ��带 ����� �Լ�
template<typename T>
void DeleteNode(Node<T> *&root)
{
	T item;
	Node<T>* tempPtr;			// �ӽ� ��带 �����ϰ� root ��带 �ӽ� ��忡 ����
	tempPtr = root;

	if (root->left == NULL)				// ���ʳ�尡 ���� ��
	{
		root = root->right;				// ������ ��尡 root�� �ǵ��� �����ϰ� �ӽó�带 ����
		delete tempPtr;
	}
	else if (root->right == NULL)		// �����ʳ�尡 ���� ��
	{
		root = root->left;				// ���� ��尡 root�� �ǵ��� �����ϰ� �ӽó�带 ����
		delete tempPtr;
	}
	else
	{
		GetPredecessor(root->left, item);	// �߰��� �ִ� ��带 ����� ���� �� (left, right, child ��� ���� ���)
		root->data = item;					// ������� ��庸�� ���� ���� �߿� ���� ū ��带 ã��
		Delete(root->left, item);			// �� ���� ���� ��忡 ���縦 �ؼ� ���� ��ó�� ������
	}
}

// ���� ������� �ϴ� ��带 ã�� recursive �Լ�
template<typename T>
void Delete(Node<T> *&root, T item)
{
	if (item < root->data)				// root��尪���� item��尡 ���� ��
		Delete(root->left, item);		// ���ʳ��� ���� delete�Լ� ȣ��
	else if (item > root->data)			// root��尪���� item��尡 Ŭ ��
		Delete(root->right, item);		// �����ʳ��� ���� delete�Լ� ȣ��
	else
		DeleteNode(root);				// ã���� �ϴ� ���� ��ġ�ϴ� ��� deletenode �Լ� ȣ��
}

// Tree���� node�� �˻��ϴ� �Լ�
template<typename T>
void Retrieve(Node<T> *root, T& item, bool &found)
{
	if (root == NULL)						// root�� NULL�� ��� found�� false 
		found = false;
	else if (item < root->data)				// ã���� �ϴ� �����۰��� root������ ���� �� 
		Retrieve(root->left, item, found);	// ���� ���� ���� retrieve �Լ� ȣ��
	else if (item > root->data)				// ã���� �ϴ� �����۰��� root������ Ŭ ��
		Retrieve(root->right, item, found);	// ������ ���� ���� retrieve �Լ� ȣ��
	else
	{										// ã���� �ϴ� ���� ��ġ�� ��
		item = root->data;					// item�� ��� ������ ����
		found = true;						// found���� true�� �ؼ� ã�� ������ ����
	}
}

// InOrder ������� ����ϴ� �Լ� 
template<typename T>
void PrintInOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		PrintInOrderTraversal(root->left, out);		// root�� �������� ���� �ٽ� InOrder �Լ� ȣ��
		out << root->data;							// root ���
		PrintInOrderTraversal(root->right, out);	// root�� ���������� ���� �ٽ� InOrder �Լ� ȣ��
	}
}

// PreOrder ������� ����ϴ� �Լ�
template<typename T>
void PrintPreOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		out << root->data;							// root�� ���� ���
		PrintPreOrderTraversal(root->left, out);	// root�� �������� ���� PreOrder �Լ� �ٽ� ȣ��
		PrintPreOrderTraversal(root->right, out);	// root�� ���������� ���� PreOrder �Լ� �ٽ� ȣ��
	}
}

// PostOrder ������� ����ϴ� �Լ�
template<typename T>
void PrintPostOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		PrintPostOrderTraversal(root->left, out);	// root�� �������� ���� �ٽ� PostOrder �Լ� ȣ��
		PrintPostOrderTraversal(root->right, out);	// root�� ���������� ���� �ٽ� PostOrder �Լ� ȣ��
		out << root->data;							// root�� �� ���
	}
}