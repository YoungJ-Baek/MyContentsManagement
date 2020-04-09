#pragma once
#include <string>
#include "SortedList.h"
#include "ItemType.h"
#include "SongType.h"

using namespace std;

/*
*	Genre Information class
*/
class GenreType
{
private:
	int genre_num;					//Genre number.
	SortedList<SongType>* SongList;	//Song List using SortedList of SongType.
public:
	//Constructor
	/**
	*	default constructor.
	*/
	GenreType();
	/**
	*	destructor.
	*/
	~GenreType();

	/**
	*	@brief	Initialize Song list iterator.
	*	@pre	Song list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	add a new song into song list.
	*	@pre	song list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new song information(ItemType).
	*	@return	return 1 if this function works well.
	*/
	int Add(ItemType data);

	/**
	*	@brief	Delete song in list.
	*	@pre	song list should be initialized.
	*	@post	delete record in the list.
	*	@param	data	deleted song information(ItemType).
	*	@return	return 1 if this function works well.
	*/
	int Delete(ItemType& data);

	/**
	*	@brief	Set genre number from keyboard.
	*	@pre	none.
	*	@post	genre number is set.
	*/
	void SetNumFromKB();

	/**
	*	@brief	Compare two genre types if left one is bigger.
	*	@pre	two genre types should be initialized.
	*	@post	show two genre types' relationship.
	*	@param	data	target genre for comparing.
	*	@return return true if left one has bigger number, otherwise, return false.
	*/
	bool operator>(GenreType &data);

	/**
	*	@brief	Compare two genre types if right one is bigger.
	*	@pre	two genre types should be initialized.
	*	@post	show two genre types' relationship.
	*	@param	data	target genre for comparing.
	*	@return return true if right one has bigger number, otherwise, return false.
	*/
	bool operator<(GenreType &data);

	/**
	*	Compare two genretype if they are same.
	*	@brief	Compare two genre types if thery are same by genre number.
	*	@pre	two genre types should be initialized.
	*	@post	show two gnere types' relationship.(equality)
	*	@param	data	target genre for comparing.
	*	@return return true if they have same genre, otherwise, return false.
	*	@comment	대소문자 관계없이 두 이름을 비교한다.
	*/
	bool operator==(GenreType &data);

	/**
	*	@brief	Substitute genre num using data's number.
	*	@pre	data should be initialized.
	*	@post	name is set by data's
	*	@return GenreType with name being filled.
	*/
	GenreType& operator=(const unsigned int &data);

	/**
	*	@brief	Substitute ID record to temp_ID.
	*	@pre	song id should be initialized ( ID doesn't start with '0' ).
	*	@post	temp_ID is set. iterator move forward.
	*/
	void operator>>(int& temp_ID);
};

