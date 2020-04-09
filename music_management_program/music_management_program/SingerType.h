#pragma once
#include <string>
#include "SortedList.h"
#include "ItemType.h"
#include "SongType.h"

using namespace std;


/*
*	Singer Information class
*/
class SingerType
{
private:
	string singer_Name;				//Singer name.
	int singer_Age;					//Singer Age ( 0:group )
	int singer_Sex;					//Singer Sex ( 0:male	1:female	2:group )
	SortedList<SongType>* SongList;	//Song List using SortedList of SongType.
public:

	//Constructor
	/**
	*	default constructor.
	*/
	SingerType();

	/**
	*	destructor.
	*/
	~SingerType();

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
	*	@brief	delete a song from song list.
	*	@pre	song list should be initialized.
	*	@post	delete the record from the list.
	*	@param	data	delete song information(ItemType).
	*	@return	return 1 if this function works well.
	*/
	int Delete(ItemType data);

	//Transformer
	/**
	*	@brief	Set singer name from keyboard.
	*	@pre	none.
	*	@post	singer name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set singer age from keyboard.
	*	@pre	none.
	*	@post	singer age is set.
	*/
	void SetAgeFromKB();

	/**
	*	@brief	Set singer sex from keyboard.
	*	@pre	none.
	*	@post	singer sex is set.
	*/
	void SetSexFromKB();

	/**
	*	@brief	Set record from keyboard.
	*	@pre	none.
	*	@post	record is set.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	Display record on screen.
	*	@pre	every values are set.
	*	@post	record is on screen.
	*/
	void DisplayRecord();

	/**
	*	@brief	Tell if singer type is empty.
	*	@pre	none.
	*	@post	know singer type's emptiness.
	*	@return	return true if it is empty, otherwise, return false.
	*/
	bool operator!();

	/**
	*	Compare two itemtypes if they are same.
	*	@brief	Compare two singer types if thery are same by singer name.
	*	@pre	two singer types should be initialized.
	*	@post	show two singer types' relationship.(equality)
	*	@param	data	target singer for comparing.
	*	@return return true if they have same name, otherwise, return false.
	*	@comment	대소문자 관계없이 두 이름을 비교한다.
	*/
	bool operator==(SingerType &data);

	/**
	*	@brief	Compare two singer types if left one is bigger.
	*	@pre	two singer types should be initialized.
	*	@post	show two singer types' relationship.
	*	@param	data	target singer for comparing.
	*	@return return true if left one has bigger name, otherwise, return false.
	*/
	bool operator>(SingerType &data);

	/**
	*	@brief	Compare two singer types if right one is bigger.
	*	@pre	two singer types should be initialized.
	*	@post	show two singer types' relationship.
	*	@param	data	target singer for comparing.
	*	@return return true if right one has bigger name, otherwise, return false.
	*/
	bool operator<(SingerType &data);

	/**
	*	@brief	Assign data's record to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by data's
	*	@return singertype with record being filled.
	*/
	SingerType& operator=(const SingerType& data);

	/**
	*	@brief	Substitute data's name to self's name.
	*	@pre	data should be initialized.
	*	@post	name is set by data's
	*	@return itemtype with name being filled.
	*/
	SingerType& operator=(const string& data);

	/**
	*	@brief	Substitute ID record to temp_ID.
	*	@pre	song id should be initialized ( ID doesn't start with '0' ).
	*	@post	temp_ID is set. iterator move forward.
	*/
	void operator>>(int& temp_ID);

	/**
	*	@brief	Substitute Player record to temp_Player.
	*	@pre	object should be initialized.
	*	@post	temp_Name is set. Move iterator forward.
	*/
	void operator>>(string& temp_Name);

	/**
	*	@brief	Display singer type on screen.
	*	@pre	brief records are set.
	*	@post	record is on screen.
	*/
	friend ostream& operator<<(ostream& os, const SingerType& data);
};

