#include "TagType.h"


//Constructor.
TagType::TagType()
{
	tag = "";
	SongList = new SortedList<SongType>();
}

//Destructor.
TagType::~TagType()
{
}

//Iterator.
void TagType::ResetList() { SongList->ResetList(); }

//Add Song in SongList.
int TagType::Add(ItemType data)
{
	SongType temp;
	int temp_ID;
	data >> temp_ID;
	temp.song_ID = to_string(temp_ID);
	data >> temp.song_Name;
	SongList->Add(temp);
	return 1;
}

//Delete Song in SongList.
int TagType::Delete(ItemType& data)
{
	SongType temp;
	int temp_ID;
	data >> temp_ID;
	temp.song_ID = to_string(temp_ID);
	data >> temp.song_Name;
	SongList->Delete(temp);
	return 1;
}

//Set tag by keyboard.
void TagType::SetTagFromKB()
{
	cout << "\n\tTag : ";
	cin >> tag;
}

//Substitute tag.
TagType& TagType::operator=(const string& data)
{
	tag = data;
	return *this;
}

//Substitute TagType.
TagType& TagType::operator=(const TagType& data)
{
	tag = data.tag;
	SongList = data.SongList;
	return *this;
}

//Tell if TagTypes have same name.
bool TagType::operator==(TagType &data)
{
	//대소문자 관계없이 이름 비교.
	if (_strcmpi(tag.c_str(), data.tag.c_str()) == 0)
		return true;
	else
		return false;
}

//Tell if left singer have bigger name.
bool TagType::operator>(TagType &data)
{
	//대소문자 관계없이 비교.
	if (_strcmpi(tag.c_str(), data.tag.c_str()) > 0)
		return true;
	else
		return false;
}

//Tell if right singer have bigger name.
bool TagType::operator<(TagType &data)
{
	//대소문자 관계없이 비교.
	if (_strcmpi(tag.c_str(), data.tag.c_str()) < 0)
		return true;
	else
		return false;
}

void TagType::operator>>(int& temp_ID)
{
	SongType temp;
	if (SongList->GetNextItem(temp) != -1)
		temp_ID = atoi(temp.song_ID.c_str());
	else
		temp_ID = 0;
}