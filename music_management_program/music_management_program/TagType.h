#pragma once
#include "SortedList.h"
#include "SongType.h"
#include "ItemType.h"
#include <string>

using namespace std;

/*
*	Tag Information class
*/
class TagType
{
private:
	string tag;									//Tag.
	SortedList<SongType>* SongList;				//Song List using SortedList of SongType.
public:
	//Constructor
	/**
	*	default constructor.
	*/
	TagType();
	/**
	*	destructor.
	*/
	~TagType();
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
	*	@brief	Set tag number from keyboard.
	*	@pre	none.
	*	@post	genre number is set.
	*/
	void SetTagFromKB();

	/**
	*	@brief	Substitute tag.
	*	@pre	data should be initialized.
	*	@post	tag is set by data's
	*	@return TagType with tag being filled.
	*/
	TagType& operator=(const string &data);

	/**
	*	@brief	Substitute TagType.
	*	@pre	data should be initialized.
	*	@post	tagtype is set by data's
	*	@return TagType with tag being filled.
	*/
	TagType& operator=(const TagType &data);

	/**
	*	Compare two tag type if they are same.
	*	@brief	Compare two tag types if thery are same by tag name.
	*	@pre	two tag types should be initialized.
	*	@post	show two tag types' relationship.(equality)
	*	@param	data	target tag for comparing.
	*	@return return true if they have same name, otherwise, return false.
	*	@comment	대소문자 관계없이 두 이름을 비교한다.
	*/
	bool operator==(TagType &data);

	/**
	*	@brief	Compare two tag types if left one is bigger.
	*	@pre	two tag types should be initialized.
	*	@post	show two tag types' relationship.
	*	@param	data	target tag for comparing.
	*	@return return true if left one has bigger name, otherwise, return false.
	*/
	bool operator>(TagType &data);

	/**
	*	@brief	Compare two tag types if right one is bigger.
	*	@pre	two tag types should be initialized.
	*	@post	show two tag types' relationship.
	*	@param	data	target tag for comparing.
	*	@return return true if right one has bigger name, otherwise, return false.
	*/
	bool operator<(TagType &data);

	/**
	*	@brief	Substitute ID record to temp_ID.
	*	@pre	song id should be initialized ( ID doesn't start with '0' ).
	*	@post	temp_ID is set. iterator move forward.
	*/
	void operator>>(int& temp_ID);

};

