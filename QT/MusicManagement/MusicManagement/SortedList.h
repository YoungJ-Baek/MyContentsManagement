#pragma once
#include <iostream>
#define DEFAULTMAXSIZE 10

using namespace std;

/**
*	array based simple unsorted list.
*/
template <typename T>
class SortedList
{
private:
	T* m_Array;	/// list array.
	int m_Length;				/// number of elements in list.
	int m_CurPointer;			/// iterator
	int m_MaxSize;				/// max size
public:
	/**
	*	default constructor.
	*/
	SortedList();

	/**
	*	constructor using user input ( maximum list size ).
	*/
	SortedList(int max);

	/**
	*	destructor.
	*/
	~SortedList();

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	Check capacity of list is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if length is 0, otherwise return false.
	*/
	bool IsEmpty();

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(T& data);

	/**
	*	@brief	add a new data into list.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Add(T data);

	/**
	*	@brief	Delete item type which have same id with data.
	*	@pre	data's id is set by keyboard.
	*	@post	Delete record which have same id with data's.
	*	@param	data	item type for searching, must have music id.
	*	@return	return 1 if deleting successes, otherwise,
				return 0 if deleting fails because there's no record with data's id.
	*/
	int Delete(T data);

	/**
	*	@brief	Replace item type which have same id with data's.
	*	@pre	data's record is set by keyboard including id.
	*	@post	Replace record which have same id with data's into data's record.
	*	@param	data	item type for searching and replacement, must have record
	*	@return	return 1 if replacing successes, otherwise,
	*			return 0 if replacing fails because there's no record with data's id.
	*/
	int Replace(T data);

	/**
	*	@brif	find index in the list with target data.
	*	@pre	data's id is set by keyboard. optionally other values, too
	*	@post	if data is empty, data's record is set by record in index
	*	@param	data	item type for searching, must have music id
	*					optionally have other values if you choose replace function.
	*	@return	return index number if search successes, otherwise
	*			return -1 if search fails.
	*/
	int Retrieve_SeqS(T& data);

	/**
	*	@brif	find index in the list with target data USING BINARY SEARCH
	*	@pre	data's id is set by keyboard. optionally other values, too
	*	@post	if data is empty, data's record is set by record in index
	*	@param	data	item type for searching, must have music id
	*					optionally have other values if you choose replace function.
	*	@return	return index number if search successes, otherwise
	*			return -1 if search fails.
	*/
	int Retrieve_Binary(T& data);

	/**
	*	@brif	simple check for data.
	*	@pre	data is set.
	*	@post	check if data is in list.
	*	@param	data	have key value
	*	@return	return index number if search successes, otherwise
	*			return -1 if search fails.
	*/
	int Retrieve_Simple(T& data);

	//얕은 복사를 막기 위해 대입연산자 '=' 오버로딩.
	/**
	*	@brief	Copy List.
	*	@pre	list should be initialized.
	*	@post	copy list.
	*	@return SortedList<T>	list same with data.
	*/
	SortedList<T>& operator=(const SortedList<T>& data);

	//index operator
	T SortedList<T>::at(int index);

};

//Constructor.
template <typename T>
SortedList<T>::SortedList()
{
	m_Length = 0;
	m_MaxSize = DEFAULTMAXSIZE;
	m_Array = new T[DEFAULTMAXSIZE];	//동적할당을 이용해 리스트 구성.
	m_CurPointer = -1;
}

//Constructor with max size input.
template <typename T>
SortedList<T>::SortedList(int max)
{
	m_Length = 0;
	m_MaxSize = max;
	m_Array = new T[max];	//동적할당을 이용해 사용자가 원하는 사이즈의 리스트 구성
	m_CurPointer = -1;
}

//Destructor.
template <typename T>
SortedList<T>::~SortedList() { delete[] m_Array; }

//Make list empty.
template <typename T>
void SortedList<T>::MakeEmpty()
{
	m_Length = 0;
	m_CurPointer = -1;
}

//Get a number of records in current list.
template <typename T>
int SortedList<T>::GetLength()
{
	return m_Length;
}

// Check capacity of list is full.
template <typename T>
bool SortedList<T>::IsFull()
{
	if (m_Length == m_MaxSize)
		return true;
	else
		return false;
}

// Check list is empty.
template <typename T>
bool SortedList<T>::IsEmpty()
{
	if (!m_Length)
		return true;//if it is empty, return true
	else
		return false;
}

// Initialize list iterator.
template <typename T>
void SortedList<T>::ResetList()
{
	m_CurPointer = -1;
}

// move list iterator to the next item in list and get that item.
template <typename T>
int SortedList<T>::GetNextItem(T& data) 
{
	m_CurPointer++;//increase list pointer.
	if (m_CurPointer == m_Length)//if it approaches end of list, return -1.
		return -1;
	else
	{
		data = m_Array[m_CurPointer];//copy curpointer's record to data's
		return m_CurPointer;
	}


}

// add a new data into list.
template <typename T>
int SortedList<T>::Add(T data)
{
	if (!IsFull()) {
		//if list is empty, add data front of the list.
		if (IsEmpty()) {
			m_Array[m_Length] = data;
			m_Length++;
			return 1;
		}

		//avoiding addition of record with same id.
		if (Retrieve_Simple(data) == -1)
		{
			//if data is bigger than last item in list, put data after last item.
			if (data > m_Array[m_Length - 1]) {
				m_Array[m_Length++] = data;
				return 1;
			}
			//otherwise, data의 id보다 큰 id의 item이 나오면 뒤의 item들은 다 한칸씩 밀고 그 자리에 들어간다.
			for (int iPos = 0; iPos < GetLength(); iPos++) {
				if (data < m_Array[iPos]) {
					for (int j = GetLength(); j > iPos; j--)
						m_Array[j] = m_Array[j - 1];
					m_Array[iPos] = data;
					m_Length++;
					return 1;
				}
			}
		}
		else
		{
			//cout << "\n\tYour ID already exists." << endl;
			return 0;
		}
	}
	else
		return 0;
}

//Delete record which has same id with data's
template <typename T>
int SortedList<T>::Delete(T data)
{
	if (Retrieve_Simple(data) == -1)//search fail
	{
		cout << "\n\tThere's no data with your ID" << endl << endl;
		return 0;
	}
	for (int i = Retrieve_Simple(data); i < m_Length - 1; i++)
		m_Array[i] = m_Array[i + 1];//빈 공간 채우기 위해 한칸씩 앞으로 이동.
	m_Length--;
	cout << endl << "\tDelete Complete" << endl << endl;
	return 1;
}

//Replace record which has same id with data's
template <typename T>
int SortedList<T>::Replace(T data)
{
	if (Retrieve_Binary(data) == -1)//search fail
	{
		cout << "\n\tThere's no data with your ID" << endl << endl;
		return 0;
	}
	m_Array[Retrieve_Binary(data)] = data;//replacement
	cout << "\n\tReplacement Complete" << endl << endl;
	return 1;
}

//Search list with data's id and return index.
template <typename T>
int SortedList<T>::Retrieve_SeqS(T& data)
{
	for (int i = 0; i < m_Length; i++)
		if (m_Array[i] == data)
		{
			if (!data)//check data is empty to avoid copying when you use replace function
				data = m_Array[i];
			return i;//return index
		}
	return -1;//search fail
}

//Search list with data's id by using binary search and return index.
template <typename T>
int SortedList<T>::Retrieve_Binary(T& data)
{
	int start = 0;				//retrieving start here.
	int end = GetLength() - 1;	//retrieving end here.
	int mid;					//check mid item.
	while (end >= start) {
		mid = (start + end) / 2;
		if (m_Array[mid] == data) {
			if (!data)//check data is empty to avoid copying when you use replace function
				data = m_Array[mid];
			return mid;
		}
		else if (data > m_Array[mid])
			start = mid + 1;	//if item < data, reset start.
		else
			end = mid - 1;		//if item > data, reset end.
	}

	return -1;
}

//Simple check for data.
template <typename T>
int SortedList<T>::Retrieve_Simple(T& data)
{
	int start = 0;				//retrieving start here.
	int end = GetLength() - 1;	//retrieving end here.
	int mid;					//check mid item.
	while (end >= start) {
		mid = (start + end) / 2;
		if (m_Array[mid] == data)
			return mid;
		else if (data > m_Array[mid])
			start = mid + 1;	//if item < data, reset start.
		else
			end = mid - 1;		//if item > data, reset end.
	}

	return -1;
}

//Copy list. 얕은 복사 막기 위해 오버로딩.
template<typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList<T>& data)
{
	m_Length = data.m_Length;
	m_CurPointer = data.m_CurPointer;
	m_MaxSize = data.m_MaxSize;
	for (int i = 0; i < m_Length; i++)
		m_Array[i] = data.m_Array[i];
	return *this;
}

template <typename T>
T SortedList<T>::at(int index)
{
	return m_Array[index];
}
