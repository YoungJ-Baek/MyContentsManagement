#pragma once
#include <iostream>
using namespace std;

/**
*	Structure for NodeType to use in Linked structure.
*/
template<typename T>
struct NodeType
{
	T info;
	NodeType *next;
};

/**
*	Simple unsorted list class for managing items.
*/
template<typename T>
class SortedLinkedList
{
public:
	/**
	*	default constructor.
	*/
	SortedLinkedList();

	/**
	*	destructor.
	*/
	~SortedLinkedList();

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;

	/**
	*	@brief	Add item into appropriate spot of this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);

	/**
	*	@brief	Delete item from this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item is deleted from this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Delete(T &item);

	/**
	*	@brief	Change value of item which is in this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item's value is changed.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Replace(T item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T &item);

	/**
	*	@brief	Display All Item on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllItem() const;

	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetList();

	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*/
	void GetNextItem(T &item);

	// Logic operator overloading.
	/**
	*	@brief	Initialize self by data's record.
	*	@pre	data should be initialized.
	*	@post	data's elements are copied to self's elements.
	*	@param	data for copy.
	*	@return	return this pointer which is copied with parameter data.
	*/
	SortedLinkedList<T>& operator=(const SortedLinkedList<T> &data);

private:
	NodeType<T>* m_pList;		// ����Ʈ ������
	NodeType<T>* m_pCurPointer; // current pointer
	int m_nLength;				// ����Ʈ�� ����� ���ڵ� ��
};

// Class constructor
template<typename T>
SortedLinkedList<T>::SortedLinkedList()
{
	m_nLength = 0;
	m_pList = NULL;
	m_pCurPointer = NULL;
}

// Class destructor
template<typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
	MakeEmpty();
}

// List�� ���
template<typename T>
void SortedLinkedList<T>::MakeEmpty()
{
	NodeType<T> *tempPointer;
	while (m_pList != NULL) {
		tempPointer = m_pList;
		m_pList = m_pList->next;
		//deallocate all items.
		delete tempPointer;
	}
}

// ����Ʈ�� �����ϰ� �ִ� item ���� ��ȯ
template<typename T>
int SortedLinkedList<T>::GetLength() const { return m_nLength; }

// Add item into this list.
template <typename T>
int SortedLinkedList<T>::Add(T item)
{
	// ����Ʈ �ʱ�ȭ
	ResetList();

	NodeType<T> *location = new NodeType<T>;//����Ʈ�� �߰��� item
	NodeType<T> *preLoc;					//���� item�� ����ų ������
	T dummy;								//GetNextItem()���� ���� ����
	bool bFound = false;					//�߰��� �ڸ� ã�Ҵ��� Ȯ��

	location->info = item;
	location->next = NULL;

	// list �� item�� �������� �ʴ� ���
	if (!m_nLength)
	{
		m_pList = location;
		m_nLength++;
		return 1;
	}

	// list �� item�� �ϳ� �̻� �����ϴ� ���
	else
	{
		while (1)
		{
			// preLoc�� ���� item ����ų �� �ֵ��� �ʱ�ȭ.
			preLoc = m_pCurPointer;
			// m_pCurPointer �� iterator�μ� ��ĭ ������Ŵ.
			GetNextItem(dummy);

			// iterator�� ���� �߰��� item���� ũ�� preLoc ������ �߰���Ų��.
			if (m_pCurPointer->info > location->info)
			{
				//�� ���ڸ��� �� ���
				if (preLoc == NULL)
				{
					location->next = m_pCurPointer;
					m_pList = location;
					break;
				}
				location->next = m_pCurPointer;
				preLoc->next = location;
				break;
			}

			// �������� ������ ���
			if (m_pCurPointer->next == NULL)
			{
				m_pCurPointer->next = location;
				break;
			}
		}
	}

	m_nLength++;

	return 1;
}

// ����Ʈ���� primary key�� �������� ���ڵ带 ����
template<typename T>
int SortedLinkedList<T>::Delete(T &item)
{
	m_pCurPointer = m_pList;
	bool moreToSearch = (m_pCurPointer != NULL);	//�˻��� ������� �����ϴ� ���� ����.
	NodeType<T> *prePtr = NULL;						//���� item ����Ű�� ������ ���� ����
	while (moreToSearch) {
		if (m_pCurPointer->info == item) {
			//���� item�� �� �տ� ���� ���
			if (prePtr == NULL)
				m_pList->next = m_pCurPointer->next;
			else
				prePtr->next = m_pCurPointer->next;
			delete m_pCurPointer;
			m_nLength--;
			return 1;
		}
		prePtr = m_pCurPointer;
		m_pCurPointer = m_pCurPointer->next;
		moreToSearch = (m_pCurPointer != NULL);
	}
	cout << "\n\tThere's no record with your input...\n";
	return 0;
}

// Primary key�� �������� �����͸� �˻��ϰ� �ش� �����͸� parameter �����ͷ� ��ü
template<typename T>
int SortedLinkedList<T>::Replace(T item)
{
	m_pCurPointer = m_pList;
	bool moreToSearch = (m_pCurPointer != NULL);
	while (moreToSearch) {
		if (m_pCurPointer->info == item) {
			m_pCurPointer->info = item;
			return 1;
		}
		m_pCurPointer = m_pCurPointer->next;
		moreToSearch = (m_pCurPointer != NULL);
	}
	cout << "\n\tThere's no record with your input...\n";
	return 0;
}

// Primary key�� �������� �����͸� �˻��ϰ� �ش� �����͸� ������
template<typename T>
int SortedLinkedList<T>::Get(T &item)
{
	m_pCurPointer = m_pList;
	bool moreToSearch = (m_pCurPointer != NULL);
	while (moreToSearch) {
		if (m_pCurPointer->info == item) {
			item = m_pCurPointer->info;
			return 1;
		}
		m_pCurPointer = m_pCurPointer->next;
		moreToSearch = (m_pCurPointer != NULL);
	}
	cout << "\n\tThere's no data with your input...\n";
	return 0;
}

//Display All Record in List
template<typename T>
void SortedLinkedList<T>::DisplayAllItem() const
{
	NodeType<T>* temp;
	temp = m_pList;
	bool moreToSearch = (temp != NULL);
	while (moreToSearch) {
		cout << temp->info << endl;
		temp = temp->next;
		moreToSearch = (temp != NULL);
	}
}

// ���ڵ� ������ �ʱ�ȭ
template<typename T>
void SortedLinkedList<T>::ResetList() { m_pCurPointer = NULL; }

// Current Pointer �� ���� location �� ����Ű���� �̵� �� �ش� ���ڵ带 ������->
template<typename T>
void SortedLinkedList<T>::GetNextItem(T &item)
{
	if (m_pCurPointer == NULL)
		m_pCurPointer = m_pList;
	else
		m_pCurPointer = m_pCurPointer->next;
	item = m_pCurPointer->info;
}

//���Կ����� '=' �����ε�.
template<typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(const SortedLinkedList<T> &data)
{
	m_nLength = data.m_nLength;
	m_pList = data.m_pList;
	m_pCurPointer = data.m_pCurPointer;
	return *this;
}
