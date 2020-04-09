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
	NodeType<T>* m_pList;		// 리스트 포인터
	NodeType<T>* m_pCurPointer; // current pointer
	int m_nLength;				// 리스트에 저장된 레코드 수
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

// List를 비움
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

// 리스트가 보유하고 있는 item 개수 반환
template<typename T>
int SortedLinkedList<T>::GetLength() const { return m_nLength; }

// Add item into this list.
template <typename T>
int SortedLinkedList<T>::Add(T item)
{
	// 리스트 초기화
	ResetList();

	NodeType<T> *location = new NodeType<T>;//리스트에 추가할 item
	NodeType<T> *preLoc;					//이전 item을 가리킬 포인터
	T dummy;								//GetNextItem()위한 변수 선언
	bool bFound = false;					//추가할 자리 찾았는지 확인

	location->info = item;
	location->next = NULL;

	// list 에 item이 존재하지 않는 경우
	if (!m_nLength)
	{
		m_pList = location;
		m_nLength++;
		return 1;
	}

	// list 에 item이 하나 이상 존재하는 경우
	else
	{
		while (1)
		{
			// preLoc이 이전 item 가리킬 수 있도록 초기화.
			preLoc = m_pCurPointer;
			// m_pCurPointer 가 iterator로서 한칸 증가시킴.
			GetNextItem(dummy);

			// iterator의 값이 추가할 item보다 크면 preLoc 다음에 추가시킨다.
			if (m_pCurPointer->info > location->info)
			{
				//맨 앞자리에 들어갈 경우
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

			// 마지막에 도달할 경우
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

// 리스트에서 primary key를 기준으로 레코드를 삭제
template<typename T>
int SortedLinkedList<T>::Delete(T &item)
{
	m_pCurPointer = m_pList;
	bool moreToSearch = (m_pCurPointer != NULL);	//검색을 계속할지 결정하는 변수 선언.
	NodeType<T> *prePtr = NULL;						//이전 item 가리키는 포인터 변수 선언
	while (moreToSearch) {
		if (m_pCurPointer->info == item) {
			//지울 item이 맨 앞에 있을 경우
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

// Primary key를 기준으로 데이터를 검색하고 해당 데이터를 parameter 데이터로 교체
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

// Primary key를 기준으로 데이터를 검색하고 해당 데이터를 가져옴
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

// 레코드 포인터 초기화
template<typename T>
void SortedLinkedList<T>::ResetList() { m_pCurPointer = NULL; }

// Current Pointer 가 다음 location 를 가리키도록 이동 후 해당 레코드를 가져옴->
template<typename T>
void SortedLinkedList<T>::GetNextItem(T &item)
{
	if (m_pCurPointer == NULL)
		m_pCurPointer = m_pList;
	else
		m_pCurPointer = m_pCurPointer->next;
	item = m_pCurPointer->info;
}

//대입연산자 '=' 오버로딩.
template<typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(const SortedLinkedList<T> &data)
{
	m_nLength = data.m_nLength;
	m_pList = data.m_pList;
	m_pCurPointer = data.m_pCurPointer;
	return *this;
}
