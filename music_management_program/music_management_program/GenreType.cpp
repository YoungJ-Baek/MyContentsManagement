#include "GenreType.h"



//Constructor.
GenreType::GenreType()
{
	genre_num = 100;
	SongList = new SortedList<SongType>();
}

//Destructor.
GenreType::~GenreType()
{
}

//Reset Song List.
void GenreType::ResetList() { SongList->ResetList(); }

//Add Song in SongList.
int GenreType::Add(ItemType data)
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
int GenreType::Delete(ItemType& data)
{
	SongType temp;
	int temp_ID;
	data >> temp_ID;
	temp.song_ID = to_string(temp_ID);
	data >> temp.song_Name;
	SongList->Delete(temp);
	return 1;
}

//Set genre number by keyboard.
void GenreType::SetNumFromKB()
{
	cout << "\n\tGenre : ";
	cin >> genre_num;
}

//Compare left genre has bigger number.
bool GenreType::operator>(GenreType &data)
{
	if (genre_num > data.genre_num)
		return true;
	else
		return false;
}

//Compare right genre has bigger number.
bool GenreType::operator<(GenreType &data)
{
	if (genre_num < data.genre_num)
		return true;
	else
		return false;
}

//Tell if genretypes have same number.
bool GenreType::operator==(GenreType &data)
{
	//대소문자 관계없이 이름 비교.
	if (genre_num==data.genre_num)
		return true;
	else
		return false;
}

//Substitute genre number by using data's number
GenreType& GenreType::operator=(const unsigned int& data)
{
	genre_num = data;
	return *this;
}

//Substitute temp_ID with songlist song's ID.
void GenreType::operator>>(int& temp_ID)
{
	SongType temp;
	//move iterator forward.
	if (SongList->GetNextItem(temp) != -1)
		temp_ID = atoi(temp.song_ID.c_str());
	else
		temp_ID = 0;
}