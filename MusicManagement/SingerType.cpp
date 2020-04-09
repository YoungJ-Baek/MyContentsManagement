#include "SingerType.h"
#include <string.h>
#include <string>

using namespace std;


//Constructor.
SingerType::SingerType()
{
	singer_Name = "";
	singer_Age = 0;
	singer_Sex = 0;
	SongList = new SortedList<SongType>();
}

//Destructor.
SingerType::~SingerType()
{
}

//Reset Song List.
void SingerType::ResetList() { SongList->ResetList(); }

//Add Song in SongList.
int SingerType::Add(ItemType data)
{
	SongType temp;
	int temp_ID;
	data >> temp_ID;
	temp.song_ID = to_string(temp_ID);
	data >> temp.song_Name;
	SongList->Add(temp);
	return 1;
}

//Delete song in SongList.
int SingerType::Delete(ItemType data)
{
	SongType temp;
	int temp_ID;
	data >> temp_ID;
	temp.song_ID = to_string(temp_ID);
	data >> temp.song_Name;
	SongList->Delete(temp);
	return 1;
}

//Set Singer Name from keyboard.
void SingerType::SetNameFromKB()
{
	cout << "\n\tName : ";
	cin.ignore(256, '\n');//delete buffer
	getline(cin, singer_Name);
}

//Set Singer Age from keyboard.
void SingerType::SetAgeFromKB()
{
	cout << "\n\tAge ( 0 : group ) : ";
	cin >> singer_Age;
}

//Set Singer Sex from keyboard.
void SingerType::SetSexFromKB()
{
	cout << "\n\tSex ( 0 : Male\t1 : Female\t2 : Group ) : ";
	cin >> singer_Sex;
}

//Set Singer Record from keyboard.
void SingerType::SetRecordFromKB()
{
	cout << "\n\tPlease enter " << singer_Name << "'s information.\n\n";
	SetAgeFromKB();
	SetSexFromKB();
}

//Display Singer Record on screen.
void SingerType::DisplayRecord()
{
	cout << "\n\t-----Singer Information-----\n\n";
	cout << "\tName: " << singer_Name << endl;
	if (singer_Age == 0)
		cout << "\tAge: Group\n";
	else
		cout << "\tAge: " << singer_Age << endl;
	cout << "\tSex: ";
	switch (singer_Sex) {
	case 0:
		cout << "Male\n";
		break;
	case 1:
		cout << "Female\n";
		break;
	case 2:
		cout << "Group\n";
		break;
	default:
		cout << "No information..." << endl;
		break;
	}
	cout << "\t--------------------------\n\n";
}

//Tell if singertype is empty.
bool SingerType::operator!()
{
	if (singer_Name == "")
		return true;
	else
		return false;
}

//Tell if singertypes have same name.
bool SingerType::operator==(SingerType &data)
{
	//대소문자 관계없이 이름 비교.
	if (_strcmpi(singer_Name.c_str(), data.singer_Name.c_str()) == 0)
		return true;
	else
		return false;
}

//Tell if left singer have bigger name.
bool SingerType::operator>(SingerType &data)
{
	//대소문자 관계없이 비교.
	if (_strcmpi(singer_Name.c_str(), data.singer_Name.c_str()) > 0)
		return true;
	else
		return false;
}

//Tell if right singer have bigger name.
bool SingerType::operator<(SingerType &data)
{
	//대소문자 관계없이 비교.
	if (_strcmpi(singer_Name.c_str(), data.singer_Name.c_str()) < 0)
		return true;
	else
		return false;
}

//Copy target data's record.
SingerType& SingerType::operator=(const SingerType& data)
{
	singer_Name = data.singer_Name;
	singer_Age = data.singer_Age;
	singer_Sex = data.singer_Sex;
	SongList = data.SongList;
	return *this;
}

//Initialize singer_Name with data.
SingerType& SingerType::operator=(const string& data)
{
	singer_Name = data;
	return *this;
}

//Substitute temp_ID with songlist song's ID.
void SingerType::operator>>(int& temp_ID)
{
	SongType temp;
	//move iterator forward.
	if (SongList->GetNextItem(temp) != -1)
		temp_ID = atoi(temp.song_ID.c_str());
	else
		temp_ID = 0;
}

//Substitute temp_Name with songlist song's name.
void SingerType::operator>>(string& temp_Name)
{
	SongType temp;
	if (SongList->GetNextItem(temp) != -1)
		temp_Name = temp.song_Name;
	else
		return;
}

//Display singertype's records on screen.
ostream& operator<<(ostream& os, const SingerType& data)
{
	SortedList<SongType>* tempList;
	tempList = new SortedList<SongType>();
	SongType temp;
	tempList = data.SongList;
	tempList->ResetList();
	while (tempList->GetNextItem(temp)!=-1)
	{
		temp.DisplaySongID();
		temp.DisplaySongName();
	}
	return os;
}