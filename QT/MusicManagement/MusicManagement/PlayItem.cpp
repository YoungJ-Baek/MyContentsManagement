#include "PlayItem.h"


//Constructor.
PlayItem::PlayItem()
{
	p_ID = "";
	p_numPlay = 0;
	p_inTime = -1;
	play = false;
}

//Default destructor.
PlayItem::~PlayItem()
{
}

//Set ID from keyboard.
void PlayItem::SetIdFromKB()
{
	cout << "\tEnter the ID: ";
	cin >> p_ID;
}

//Set Record from keyboard.
void PlayItem::SetRecordFromKB()
{
	cout << "\tEnter the number the song has been played: ";
	cin >> p_numPlay;
	cout << "\tEnter the insert order: ";
	cin >> p_inTime;
}

//Read & Write File
//Read a record from file.
int PlayItem::ReadDataFromFile(ifstream& fin)
{
	//skip blank which are made to distinguish item types.
	string temp;
	getline(fin, temp);
	if (temp == "")
		getline(fin, p_ID);
	if (fin.eof())
		return 0;
	getline(fin, temp);
	p_numPlay = atoi(temp.c_str());
	getline(fin, temp);
	p_inTime = atoi(temp.c_str());
	getline(fin, temp);
	if (temp == "1")
		play = true;
	else
		play = false;
	cout << endl;
	return 1;
}

//Write a record into file.
//Use \n instead of ' ', because of considering blank between words.
int PlayItem::WriteDataToFile(ofstream& fout)
{
	//enter blank to distinguish each item types.
	fout << endl;
	fout << p_ID << endl;
	fout << p_numPlay << endl;
	fout << p_inTime << endl;
	if (play == true)
		fout << '1' << endl;
	else
		fout << '0' << endl;

	return 1;
}

//Logical operator overloading.
//Substitute insert order.
void PlayItem::operator=(const int& temp_Count)
{
	p_inTime = temp_Count;
}

//Substitute ID.
void PlayItem::operator=(const string& temp_id)
{
	p_ID = temp_id;
}

//외부에 primary key 를 전달.
void PlayItem::operator>>(string& temp_ID)
{
	temp_ID = p_ID;
}

//외부에 재생횟수 전달.
void PlayItem::operator>>(int& temp_freq)
{
	temp_freq = p_numPlay;
}

//ID 비교를 통해 두개의 오브젝트가 같은지 확인.
bool PlayItem::operator==(PlayItem &data)
{
	if (p_ID == data.p_ID)
		return true;
	else
		return false;
}

//Check if song is already played.
bool PlayItem::operator==(bool check)
{
	if (play == check)
		return true;
	else
		return false;
}

//Check insert order.
bool PlayItem::operator==(int order)
{
	if (p_inTime == order)
		return true;
	else
		return false;
}

//재생 횟수 증가.
PlayItem& PlayItem::operator++()
{
	p_numPlay++;
	return *this;
}

//Compare if left one is late.
bool PlayItem::operator>(PlayItem &data)
{
	if (this->p_inTime == -1) {
		if (this->p_ID > data.p_ID)
			return true;
		else
			return false;
	}
	else {
		if (this->p_inTime > data.p_inTime)
			return true;
		else
			return false;
	}
}

//Compare if left one is late.
bool PlayItem::operator<(PlayItem &data)
{
	if (this->p_inTime == -1) {
		if (this->p_ID < data.p_ID)
			return true;
		else
			return false;
	}
	else {
		if (this->p_inTime < data.p_inTime)
			return true;
		else
			return false;
	}
}

//Change play state.
void PlayItem::operator!()
{
	if (play)
		play = false;
	else
		play = true;
}

//간단한 정보들 출력.
ostream& operator<<(ostream& os, const PlayItem& data)
{
	os << "\n\tID :\t" << data.p_ID << endl;
	os << "\tPlay :\t" << data.p_numPlay << endl;
	os << "\tOrder :\t" << data.p_inTime << endl;
	return os;
}