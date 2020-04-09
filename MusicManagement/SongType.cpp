#include "SongType.h"



//Tell if songtype is empty.
bool SongType::operator!()
{
	if (song_ID == "")
		return true;
	else
		return false;
}

//Compare two songtypes by id.
bool SongType::operator==(SongType &data)
{
	if (song_ID == data.song_ID)
		return true;
	else
		return false;
}

//Compare if song(self) has bigger id than target song.
bool SongType::operator>(SongType &data)
{
	if (atoi(song_ID.c_str()) > atoi(data.song_ID.c_str()))
		return true;
	else
		return false;
}

//Compare if song(self) has smaller id than target song.
bool SongType::operator<(SongType &data)
{
	if (atoi(song_ID.c_str()) < atoi(data.song_ID.c_str()))
		return true;
	else
		return false;
}

//Copy records of data's.
SongType& SongType::operator=(const SongType& data)
{
	song_ID = data.song_ID;
	song_Name = data.song_Name;
	return *this;
}

//Copy records of data's.
SongType& SongType::operator=(const ItemType& data)
{
	song_ID = data.GetId();
	song_Name = data.GetName();
	return *this;
}