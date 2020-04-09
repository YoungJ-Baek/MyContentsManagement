#pragma once
#ifndef _DOUBLYITERATOR_H
#define _DOUBLYITERATOR_H

#include "DoublySortedLinkedList.h"

template<typename T>
struct DoublyNodeType;
template<typename T>
class DoublySortedLinkedList;

/**
*	연결리스트에서 쓰이는 Iterator의 클래스.
*/
template <typename T>
class DoublyIterator
{
	friend class DoublySortedLinkedList<T>;
public:
	/**
	*	디폴트 생성자.
	*/
	DoublyIterator(const DoublySortedLinkedList<T> &list) : m_List(list), m_pCurPointer(list.m_pFirst)
	{}; ///< DoublySortedLinkedList와 친구 클래스.

	/**
	*	@brief	Check if node is not empty.
	*	@pre	Iterator should be initialized.
	*	@post	none.
	*	@return	return true if current pointer is not empty, otherwise false.
	*/
	bool NotNull();

	/**
	*	@brief	Check if next node is not empty.
	*	@pre	Iterator should be initialized.
	*	@post	none.
	*	@return	return true if next node is not empty, otherwise 0.
	*/
	bool NextNotNull();

	/**
	*	@brief	Return first node of list.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return list's first node.
	*/
	T First();

	/**
	*	@brief	Return next node.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return next node of current pointer.
	*/
	T Next();

	/**
	*	@brief	Return current node of list.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return list's current node.
	*/
	DoublyNodeType<T> GetCurrentNode();
private:
	const DoublySortedLinkedList<T> &m_List;//List that iterator points.
	DoublyNodeType<T>* m_pCurPointer;//current node that iterator points.
};

//Check if node is not empty.
template <typename T>
bool DoublyIterator<T> :: NotNull()
{
	if(m_pCurPointer == NULL)
		return false;
	else
		return true;
}

//Check if next node is not empty.
template <typename T>
bool DoublyIterator<T> :: NextNotNull()
{
	if(m_pCurPointer->next == NULL)
		return false;
	else
		return true;
}

//Return first node of list.
template <typename T>
T DoublyIterator<T> :: First()
{
	return m_List.m_pFirst->data;
}

//Return next node.
template <typename T>
T DoublyIterator<T> :: Next()
{
	m_pCurPointer = m_pCurPointer->next;
	return m_pCurPointer->data;
}

//Return current node.
template <typename T>
DoublyNodeType<T> DoublyIterator<T> :: GetCurrentNode()
{
	return *m_pCurPointer;
}

#endif _DOUBLYITERATOR_H