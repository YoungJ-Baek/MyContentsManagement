#pragma once
#include <string>
#include <iostream>
#include "ItemType.h"

using namespace std;
/**
*	class for SongList in SingerType&GenreType by SortedList.
*/
class SongType
{
private:
	friend class GenreType;
	friend class SingerType;
	friend class TagType;
	string song_ID;
	string song_Name;
public:
	SongType()
	{
		song_ID = "";
		song_Name = "";
	};

	~SongType() {};

	void DisplaySongID() { cout << "\tID: " << song_ID << endl; };
	void DisplaySongName() { cout << "\tName: " << song_Name << endl; };

	/**
	*	@brief	Tell if song type is empty.
	*	@pre	none.
	*	@post	know item type's emptiness.
	*	@return	return true if it is empty, otherwise, return false.
	*/
	bool operator!();

	/**
	*	Compare two songtypes if they are same.
	*	@brief	Compare two song types if thery are same by item id.
	*	@pre	two song types should be initialized.
	*	@post	show two song types' relationship.(equality)
	*	@param	data	target songtype for comparing.
	*	@return return true if they have same id, otherwise, return false.
	*/
	bool operator==(SongType &data);

	/**
	*	@brief	Compare two song types if left one is bigger.
	*	@pre	two song types should be initialized.
	*	@post	show two song types' relationship.
	*	@param	data	target song for comparing.
	*	@return return true if left one has bigger ID, otherwise, return false.
	*/
	bool operator>(SongType &data);

	/**
	*	@brief	Compare two song types if right one is bigger.
	*	@pre	two song types should be initialized.
	*	@post	show two song types' relationship.
	*	@param	data	target song for comparing.
	*	@return return true if right one has bigger ID, otherwise, return false.
	*/
	bool operator<(SongType &data);

	/**
	*	@brief	Assign data's record to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by data's
	*	@return itemtype with record being filled.
	*/
	SongType& operator=(const SongType& data);

	/**
	*	@brief	Assign data's record to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by data's
	*	@return itemtype with record being filled.
	*/
	SongType& operator=(const ItemType& data);

	/**
	*	@brief	Print Song information.
	*	@pre	none.
	*	@post	none.
	*/
	friend ostream& operator << (ostream& out, SongType& item)
	{
		item.DisplaySongID();
		item.DisplaySongName();
		return out;
	}
};

