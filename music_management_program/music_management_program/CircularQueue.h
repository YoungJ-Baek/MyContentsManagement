#pragma once
#include <iostream>

using namespace std;

//Default list Maxsize
#define DEFAULTMAXSIZE 10

/**
*	pointer based ring type queue ( dynamic allocation ).
*/
template <typename T>
class CircularQueueType
{
public:
	/**
	*	Default constructor.
	*	Create circular queue(default size) using dynamic allocation
	*/
	CircularQueueType();

	/**
	*	Constructor using user input ( maximum list size ).
	*	Create circular queue(max size) using dynamic allocation
	*/
	CircularQueueType(int max);

	/**
	*	default destructor, release circular queue
	*/
	~CircularQueueType();

	/**
	*	@brief	Check capacity of queue is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	Check capacity of queue is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if front==rear, otherwise return false.
	*/
	bool IsEmpty();

	/**
	*	@brief	Make queue empty.
	*	@pre	none.
	*	@post	clear queue.
	*/
	void MakeEmpty();

	/**
	*	@brief	add a new data into queue ( add item to top ).
	*	@pre	queue should be initialized.
	*	@post	added the new record into the queue.
	*	@param	item	new item.
	*/
	void EnQueue(T item);

	/**
	*	@brief	If queue is not empty, return item and delete item.
	*	@pre	queue is not empty.
	*	@post	Delete record by insert order and return deleted item.
	*	@param	data	parameter to save deleted item.
	*/
	void DeQueue(T &item);

	/**
	*	@brief	Print all item on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void Print();

	/**
	*	@brief	Initialize queue iterator.
	*	@pre	queue should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	move queue iterator to the next item in list and get that item ( insert order ).
	*	@pre	queue and queue iterator should be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	return true if queue is not empty. otherwise
	*			return false if queue is empty.
	*/
	bool GetNextItem(T &item);

	/**
	*	@brif	find item in the queue with target data.
	*	@pre	data's id is set.
	*	@post	find queue item by parameter's ID.
	*	@param	item	parameter for searching, must have music id
	*	@return	return item which have same ID with parameter, otherwise.
	*			return parameter if search fails.
	*/
	T Search(T item);

	/**
	*	@brif	find index in the queue with target data.
	*	@pre	data's id is set
	*	@post	none.
	*	@param	item	parameter for searching, must have music id.
	*	@return	return index number if search successes, otherwise
	*			return -1 if search fails.
	*/
	int SearchIndex(T item);

	/**
	*	@brief	Delete item type which have same id with data.
	*	@pre	data's id is set by keyboard.
	*	@post	Delete record which have same id with data's.
	*	@param	item	parameter for searching, must have music id.
	*	@return	return 1 if deleting successes, otherwise,
				return 0 if deleting fails because there's no record with data's id.
	*/
	int Delete(T item);

	/**
	*	@brief	Replace item type which have same id with data's.
	*	@pre	data's record is set by keyboard including id.
	*	@post	Replace record which have same id with data's into data's record.
	*	@param	item	parameter for searching and replacement, must have record
	*	@return	return 1 if replacing successes, otherwise,
	*			return 0 if replacing fails because there's no record with data's id.
	*/
	int Replace(T item);
	
private:
	int m_iFront;		// front index of the circular queue
	int m_iRear;		// rear index of the circular queue
	int m_nMaxQueue;	// maximum size of the circular queue
	T *m_pItems;		// item pointer
	int m_CurPointer;	// current pointer ( iterator )
};

//Default constructor.
template <typename T>
CircularQueueType<T>::CircularQueueType()
{
	m_nMaxQueue = DEFAULTMAXSIZE + 1;
	m_pItems = new T[m_nMaxQueue];
	m_iFront = m_nMaxQueue - 1;
	m_iRear = m_nMaxQueue - 1;
	m_CurPointer = m_iFront;
}

//Constructor with maximum size by user.
template <typename T>
CircularQueueType<T>::CircularQueueType(int max)
{
	m_nMaxQueue = max + 1;
	m_pItems = new T[m_nMaxQueue];
	m_iFront = m_nMaxQueue - 1;
	m_iRear = m_nMaxQueue - 1;
	m_CurPointer = m_iFront;
}

//Destroctor delete dunamic allocation.
template <typename T>
CircularQueueType<T>::~CircularQueueType() { delete[] m_pItems; }

//Check if queue is full.
template <typename T>
bool CircularQueueType<T>::IsFull()
{
	if ((m_iRear + 1) % m_nMaxQueue == m_iFront)
		return true;
	else
		return false;
}

//Check if queue is empty.
template <typename T>
bool CircularQueueType<T>::IsEmpty()
{
	if (m_iFront == m_iRear)
		return true;
	else
		return false;
}

//Make queue empty ( Front = Rear ).
template <typename T>
void CircularQueueType<T>::MakeEmpty()
{
	m_iFront = m_iRear;
}

//Add new item to queue by insert order.
template <typename T>
void CircularQueueType<T>::EnQueue(T item)
{
	if (IsFull()) {
		return;
	}
	else {
		if (IsEmpty()) {
			m_iRear = (m_iRear + 1) % m_nMaxQueue;
			m_pItems[m_iRear] = item;
		}
		else if (SearchIndex(item) != -1) {
			return;
		}
		else {
			m_iRear = (m_iRear + 1) % m_nMaxQueue;
			m_pItems[m_iRear] = item;
		}
	}
}

//Delete and return item by insert order.
template <typename T>
void CircularQueueType<T>::DeQueue(T &item)
{
	if (IsEmpty()) {
		return;
	}
	else {
		m_iFront = (m_iFront + 1) % m_nMaxQueue;
		item = m_pItems[m_iFront];
	}
}

//Print all items in queue.
template <typename T>
void CircularQueueType<T>::Print()
{
	cout << endl << "\tPlay List" << endl;
	for (int i = (m_iFront + 1) % m_nMaxQueue; i <= m_iRear; (++i) % m_nMaxQueue)
		cout << m_pItems[i] << endl;
}

//Reset iterator.
template <typename T>
void CircularQueueType<T>::ResetList()
{
	m_CurPointer = m_iFront;
}


//Increase iterator and return item.
template <typename T>
bool CircularQueueType<T>::GetNextItem(T &item)
{
	if (!IsEmpty()) {
		if (m_CurPointer == m_iRear)
			m_CurPointer = (m_iFront + 1) % m_nMaxQueue;
		else
			m_CurPointer = (m_CurPointer + 1) % m_nMaxQueue;
		item = m_pItems[m_CurPointer];
		++m_pItems[m_CurPointer];
		return true;
	}
	else {
		cout << "\tYour List is empty\n";
		return false;
	}
}

//return item which have same ID with your input.
template <typename T>
T CircularQueueType<T>::Search(T item)
{
	for (int i = (m_iFront + 1) % m_nMaxQueue; i != (m_iRear + 1) % m_nMaxQueue; (++i) % m_nMaxQueue)
		if (m_pItems[i] == item)
			return m_pItems[i];
	cout << "\n\tThere's no item with your ID.\n";
	return item;
}

//return item index which have same ID with your input.	fail : return -1.
template <typename T>
int CircularQueueType<T>::SearchIndex(T item)
{
	for (int i = (m_iFront + 1) % m_nMaxQueue; i != (m_iRear + 1) % m_nMaxQueue; (++i) % m_nMaxQueue)
		if (m_pItems[i] == item)
			return i;
	return -1;
}

//Delete item in queue by ID.
template <typename T>
int CircularQueueType<T>::Delete(T item)
{
	for (int i = (m_iFront + 1) % m_nMaxQueue; i != (m_iRear + 1) % m_nMaxQueue; (++i) % m_nMaxQueue)
		if (m_pItems[i] == item) {
			for (int j = i; j != m_iRear; (++j) % m_nMaxQueue)
				m_pItems[j] = m_pItems[j + 1];
			if (m_iRear == 0) {
				m_iRear = m_nMaxQueue - 1;
				return 1;
			}
			else
				m_iRear--;
			return 1;
		}
	return 0;
}

//Replace item in queue by ID.
template <typename T>
int CircularQueueType<T>::Replace(T item)
{
	for (int i = (m_iFront + 1) % m_nMaxQueue; i != (m_iRear + 1) % m_nMaxQueue; (++i) % m_nMaxQueue)
		if (m_pItems[i] == item) {
			m_pItems[i] = item;
			return 1;
		}
	return 0;
}