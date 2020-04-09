#include "ItemType.h"
#include <ctime>
#include <Windows.h>
#include <mmsystem.h>
#include <direct.h>

#pragma comment(lib, "winmm.lib")
using namespace std;

//Constructor
ItemType::ItemType()
{
	m_tag = new SortedList<string>();
	m_Type = -1;
	m_Name = "";
	m_Writer = "";
	m_Player = "";
	m_Genre = -1;
	m_Id = to_string(time(NULL));//시간의 흐름에 따라 고유 번호 부여
	tag_count = 0;
	num_play = 0;
	f_Type = -1;
	f_Name = "";
}

//default destructor
ItemType::~ItemType() {}

//Get value
//Observer function
//Get music type.
int ItemType::GetType() { return m_Type; }
//Get music name.
string ItemType::GetName() const { return m_Name; }
//Get writer.
string ItemType::GetWriter() { return m_Writer; }
//Get player.
string ItemType::GetPlayer() { return m_Player; }
//Get music genre.
int ItemType::GetGenre() { return m_Genre; }
//Get music lyrics.
string ItemType::GetLyrics() { return m_Lyrics; }
//Get music id.
string ItemType::GetId() const { return m_Id; }
//Get music tag count.
int ItemType::GetTagCount() const { return tag_count; }
//Get music play count.
int ItemType::GetPlayCount() const { return num_play; }
//Get music file type.
int ItemType::GetFileType() { return f_Type; }
//Get music file name.
string ItemType::GetFileName() { return f_Name; }

//Set value
//Transformer function
//Set music type.
void ItemType::SetType(int inType) { m_Type = inType; }
//Set music name.
void ItemType::SetName(string inName) { m_Name = inName; }
//Set writer.
void ItemType::SetWriter(string inWriter) { m_Writer = inWriter; }
//Set player.
void ItemType::SetPlayer(string inInstructor) { m_Player = inInstructor; }
//Set music genre.
void ItemType::SetGenre(int inGenre) { m_Genre = inGenre; }
//Set music lyrics.
void ItemType::SetLyrics(string inLyrics) { m_Lyrics = inLyrics; }
//Set music tag.
void ItemType::SetTag(string inTag) { m_tag->Add(inTag); tag_count++; }
//Set music id.
//Music id should not be changed. Use carefully.
void ItemType::SetId(string inId) { m_Id = inId; }
//Set music file type.
void ItemType::SetFileType(int inFtype) { f_Type = inFtype; }
//Set music file name.
void ItemType::SetFileName(string inFname) { f_Name = inFname; }
//Set must have record.
//Music id is set when item type is initialized. No setting here.
void ItemType::SetRecord(int inType, string inName, string inWriter, string inPlayer, int inGenre, string inId)
{
	SetType(inType);
	SetName(inName);
	SetWriter(inWriter);
	SetPlayer(inPlayer);
	SetGenre(inGenre);
}

//Display value
//Display music type if it is pop music or instrumental music.
void ItemType::DisplayTypeOnScreen()
{
	if (m_Type == 1)
		cout << "\tType: " << "가요" << endl;
	if (m_Type == 2)
		cout << "\tType: " << "연주곡" << endl;
}
//Display music name.
void ItemType::DisplayNameOnScreen() { cout << "\tName: " << m_Name << endl; }
//Display writer.
void ItemType::DisplayWriterOnScreen() { cout << "\tWriter: " << m_Writer << endl; }
//Display player
void ItemType::DisplayPlayerOnScreen() { cout << "\tPlayer: " << m_Player << endl; }
//Display music genre.
void ItemType::DisplayGenreOnScreen()
{
	//pop music
	if (m_Type == 1)
		switch (m_Genre)
		{
		case POP:
			cout << "\tGenre: Dance / POP" << endl;
			break;
		case BALLAD:
			cout << "\tGenre: BALLAD" << endl;
			break;
		case ROCK:
			cout << "\tGenre: ROCK /  Metal" << endl;
			break;
		case HIPHOP:
			cout << "\tGenre: HIPHOP / Rap" << endl;
			break;
		case EDM:
			cout << "\tGenre: EDM" << endl;
			break;
		case JAZZ:
			cout << "\tGenre: JAZZ" << endl;
			break;
		case COUNTRY:
			cout << "\tGenre: COUNTRY" << endl;
			break;
		case FORK:
			cout << "\tGenre: Fork / Aquastic" << endl;
			break;
		case IDOL:
			cout << "\tGenre: Idol" << endl;
			break;
		case RnB:
			cout << "\tGenre: R&B / Soul" << endl;
			break;
		default:
			cout << "\tGenre: Unknown Genre" << endl;
			break;
		}

	enum Genre_INST { CLASSIC = 10, OST, NEWAGE, WORLD, TRADITIONAL, CCM };
	//instrumental music
	if (m_Type == 2)
		switch (m_Genre)
		{
		case CLASSIC:
			cout << "\tGenre: Classic" << endl;
			break;
		case OST:
			cout << "\tGenre: OST" << endl;
			break;
		case NEWAGE:
			cout << "\tGenre: New Age" << endl;
			break;
		case WORLD:
			cout << "\tGenre: World Music" << endl;
			break;
		case TRADITIONAL:
			cout << "\tGenre: Traditional Music" << endl;
			break;
		case CCM:
			cout << "\tGenre: CCM" << endl;
			break;
		default:
			cout << "\tGenre: Unknown Genre" << endl;
			break;
		}
}
//Display lyrics.
void ItemType::DisplayLyricsOnScreen()
{
	cout << "\tLyrics:\n";
	int index = m_Lyrics.find('\n', 0);
	cout << "\n\t\t" << m_Lyrics.substr(0, index + 1);
	while (1) {
		if (m_Lyrics.find('\n', index + 1) == string::npos) {
			cout << "\t\t" << m_Lyrics.substr(index + 1);
			break;
		}
		else {
			cout << "\t\t" << m_Lyrics.substr(index + 1, m_Lyrics.find('\n', index + 1) - index);
			index = m_Lyrics.find('\n', index + 1);
		}
	}
	cout << endl << endl;
}
//Display music tag.
void ItemType::DisplayTagOnScreen() 
{ 
	cout << "\tTag\n";
	string temp;
	m_tag->ResetList();
	if (m_tag->IsEmpty())
		cout << "\tNo Tag" << endl;
	else
		while (m_tag->GetNextItem(temp) != -1) { cout << "\t" << temp << endl; }
	cout << endl;
}
//Display music id.
void ItemType::DisplayIdOnScreen() { cout << "\tID: " << m_Id << endl; }
//Display music file Type.
void ItemType::DisplayFileTypeOnScreen() { cout << "\tFile Type: " << f_Type << endl; }
//Display music file name.
void ItemType::DisplayFileNameOnScreen() { cout << "\tFile Name: " << f_Name << endl; }
//Display record.
void ItemType::DisplayRecordOnScreen()
{
	string input;
	DisplayTypeOnScreen();
	DisplayNameOnScreen();
	DisplayWriterOnScreen();
	DisplayPlayerOnScreen();
	DisplayGenreOnScreen();
	//DisplayLyricsOnScreen();
	DisplayIdOnScreen();
	cout << endl;
	cout << "\tDo you want to see Lyrics? [y/n] : ";
	cin >> input;
	if (input == "y")
		DisplayLyricsOnScreen();
	else if (input == "n")
		return;
	else
		cout << "\n\tWrong input..." << endl;
	cout << "\tDo you want to see tag? [y/n] : ";
	cin >> input;
	if (input == "y")
		DisplayTagOnScreen();
	else if (input == "n")
		return;
	else
		cout << "\n\tWrong input..." << endl;
}

//Set value by user
//Transformer function
//Set music type from keyboard.
//Use getline instead of >>, because of considering blank between words.
void ItemType::SetTypeFromKB()
{
	//two types: 1.Pop Music	2.Instrumental Music
	cout << "\tEnter the Type(1: Pop Music, 2: Instrumental Music): ";
	cin >> m_Type;
	if (m_Type != 1 && m_Type != 2) {
		cout << "\n\tWrong Input!\n" << endl;
		SetTypeFromKB();
		//If user enter integer out of range(1,2), retry entering type.
	}
}
//Set music name from keyboard.
void ItemType::SetNameFromKB()
{
	cout << "\tEnter the Name: ";
	cin.ignore(256, '\n');	//delete buffer from 'cin>>m_Type' line num.152.
	getline(cin, m_Name);
}
//Set writer from keyboard.
void ItemType::SetWriterFromKB()
{
	cout << "\tEnter the Writer: ";
	getline(cin, m_Writer);
}
//Set music player from keyboard.
void ItemType::SetPlayerFromKB()
{
	cout << "\tEnter the Player: ";
	getline(cin, m_Player);
}
//Set music genre from keyboard.
void ItemType::SetGenreFromKB()
{
	cout << "\tEnter the Genre: ";
	cin >> m_Genre;
}
//Set music lyrics from keyboard.
void ItemType::SetLyricsFromKB()
{
	cout << "\tEnter the Lyrics ( you should enter '^' end of your lyrics input. )\n";
	cin.ignore(256, '\n');	//delete buffer from 'cin>>m_Genre' line num.188.
	getline(cin, m_Lyrics, '^');	//get lyrics until user enter ^.
	cin.ignore(256, '\n');	//delete buffer from line num.195.
}
//Set music tag from keyboard.
void ItemType::SetTagFromKB()
{
	string temp="";
	cout << "\tAdd tag ( Enter 'end' to finish Addition )\n";
	cout << "\tEnter the Tag: ";
	cin >> temp;
	while (temp != "end")
	{
		m_tag->Add(temp);
		tag_count++;
		cout << "\tEnter the Tag: ";
		cin >> temp;
	}
}
//Set music id from keyboard.
//Music id is initialized when constructor work. Use this function carefully.
void ItemType::SetIdFromKB()
{
	cout << "\tEnter the ID: ";
	cin >> m_Id;
}
//Set music file type from keyboard.
void ItemType::SetFileTypeFromKB()
{
	//two types: 1.music file	2. URL
	cout << "\tEnter the Type(1: Music File, 2: URL): ";
	cin >> f_Type;
	if (f_Type != 1 && f_Type != 2) {
		cout << "\n\tWrong Input!\n" << endl;
		SetFileTypeFromKB();
		//If user enter integer out of range(1,2), retry entering type.
	}
}
//Set music file name from keyboard.
void ItemType::SetFileNameFromKB()
{
	cout << "\tEnter the File name or URL: ";
	cin >> f_Name;
}
//Set record from keyboard.
//Music id is initialized when constructor work. No SetIdFromKB() function here.
void ItemType::SetRecordFromKB()
{
	SetTypeFromKB();
	SetNameFromKB();
	SetWriterFromKB();
	SetPlayerFromKB();
	SetGenreFromKB();
	SetLyricsFromKB();
	SetTagFromKB();
}

//Read & Write File
//Read a record from file.
int ItemType::ReadDataFromFile(ifstream& fin)
{
	//skip blank which are made to distinguish item types.
	string temp;
	getline(fin, temp);
	if (temp == "")
		getline(fin, temp);
	if (fin.eof())
		return 0;
	m_Type = atoi(temp.c_str());
	getline(fin, m_Name);
	getline(fin, m_Writer);
	getline(fin, m_Player);
	getline(fin, temp);
	m_Genre = atoi(temp.c_str());
	getline(fin, m_Lyrics, '^');
	getline(fin, temp);
	getline(fin, temp);
	while (temp != "end")
	{
		m_tag->Add(temp);
		getline(fin, temp);
		tag_count++;
	}
	getline(fin, m_Id);
	getline(fin, temp);
	num_play = atoi(temp.c_str());
	getline(fin, temp);
	f_Type = atoi(temp.c_str());
	getline(fin, f_Name);
	cout << endl;
	//if you read lines of data more than one line, use getline(fin, string, string differenciation data)
	//여러 줄의 데이터를 받아오고 싶을 경우 getline 의 다른 용법인 구분자가 포함된 경우를 사용한다.
	//if you use this function, you should use 	'cin.ignore(256, '\n');' every line.
	return 1;
}
//Write a record into file.
//Use \n instead of ' ', because of considering blank between words.
int ItemType::WriteDataToFile(ofstream& fout)
{
	string temp;
	//enter blank to distinguish each item types.
	fout << endl;
	fout << m_Type << endl;
	fout << m_Name << endl;
	fout << m_Writer << endl;
	fout << m_Player << endl;
	fout << m_Genre << endl;
	fout << m_Lyrics << '^' << endl;
	m_tag->ResetList();
	while (m_tag->GetNextItem(temp) != -1)
		fout << temp << endl;
	fout << "end" << endl;
	fout << m_Id << endl;
	fout << num_play << endl;
	fout << f_Type << endl;
	fout << f_Name << endl;

	return 1;
}
//Play Music.
void ItemType::Play()
{
	if (f_Type == 1)
	{
		char dir[55] = "./DB/";
		strcat_s(dir, f_Name.c_str());
		wchar_t buffer[55];
		mbstowcs(buffer, dir, strlen(dir) + 1);
		LPCWSTR test = buffer;
		if (ShellExecute(NULL, NULL, TEXT("C://Program Files (x86)/Google/Chrome/Application/chrome.exe"), test, NULL, SW_HIDE) < HINSTANCE(32))
			PlaySound((LPCWSTR)dir, NULL, SND_FILENAME);
	}
	else if (f_Type == 2)
	{
		char address[300] = "explorer ";
		strcat_s(address, f_Name.c_str());
		wchar_t buffer[300];
		mbstowcs(buffer, f_Name.c_str(), strlen(f_Name.c_str()) + 1);
		LPCWSTR test = buffer;
		if (ShellExecute(NULL, NULL, TEXT("C://Program Files (x86)/Google/Chrome/Application/chrome.exe"), test, NULL, SW_HIDE) < HINSTANCE(32))
			system(address);
	}
	else
		return;
}

//Logical Operators
//Compare two itemtypes if they are same by item id.
bool ItemType::operator==(ItemType &data)
{
	if (data.m_Id == this->m_Id)
		return true;
	else
		return false;
}
//Compare two itemtypes if they are same by player name.
bool ItemType::operator==(string inPlayer)
{
	if (inPlayer == m_Player)
		return true;
	else if (m_Lyrics.find(inPlayer) != string::npos)
		return true;
	else
		return false;
}
//Compare two itemtypes if they are same by item genre.
bool ItemType::operator==(int inGenre)
{
	if (inGenre == m_Genre)
		return true;
	else
		return false;
}
//Compare two itemtypes if this has bigger ID.
bool ItemType::operator>(ItemType &data)
{
	if (atoi(data.m_Id.c_str()) < atoi(this->m_Id.c_str()))
		return true;
	else
		return false;
}
//Compare two itemtypes if this has smaller ID.
bool ItemType::operator<(ItemType &data)
{
	if (atoi(data.m_Id.c_str()) > atoi(this->m_Id.c_str()))
		return true;
	else
		return false;
}
//Tell if item type is empty.
bool ItemType::operator!()
{
	if (GetName() == "")
		return true;
	else
		return false;
}
//Assign data's record to self's record.
ItemType& ItemType::operator=(const ItemType& data)
{
	this->m_Type = data.m_Type;
	this->m_Name = data.m_Name;
	this->m_Writer = data.m_Writer;
	this->m_Player = data.m_Player;
	this->m_Genre = data.m_Genre;
	this->m_Lyrics = data.m_Lyrics;
	this->m_tag = data.m_tag;
	this->m_Id = data.m_Id;
	this->num_play = data.num_play;
	this->f_Type = data.f_Type;
	this->f_Name = data.f_Name;
	return *this;
}
//Assign data's ID with playitem data's.
ItemType& ItemType::operator=(const string& data)
{
	m_Id = data;
	return *this;
}
//Check if there's keyword in item's name.
bool ItemType::operator!=(string keyword)
{
	if (m_Name.find(keyword) != string::npos)
		return true;
	else
		return false;
}
//Substitute ID to external parameter.
void ItemType::operator>>(int& temp_ID)
{
	temp_ID = atoi(m_Id.c_str());
}
//Substitute Genre to external parameter.
void ItemType::operator>>(unsigned int& temp_Genre)
{
	temp_Genre = m_Genre;
}
//Substitute play count to external parameter.
void ItemType::operator>>(float& temp_numPlay) { temp_numPlay = num_play; }

//Substitute name to external parameter.
void ItemType::operator>>(string& temp_Player)
{
	temp_Player = m_Player;
}

int ItemType::GetIndexTag(int index, string& temp_tag)
{
	if (m_tag->IsEmpty())
		return 0;
	if (index >= tag_count)
		return 0;
	m_tag->ResetList();
	for (int i = 0; i <= index; i++)
		m_tag->GetNextItem(temp_tag);
	return 1;
}

int ItemType::GetNextTag(string& temp_tag)
{
	if (m_tag->IsEmpty())
		return -1;
	if (m_tag->GetNextItem(temp_tag) != -1)
		return 1;
	else
		return -1;
}

void ItemType::ResetTagList() { m_tag->ResetList(); }

//Increase play count.
ItemType& ItemType::operator++()
{
	num_play++;
	return *this;
}