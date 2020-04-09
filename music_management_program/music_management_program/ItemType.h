#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "PlayItem.h"
#include "SortedList.h"
using namespace std;


/*
*	use this for printing music genre when it is pop music.
*/
enum Genre_POP { POP, BALLAD, ROCK, HIPHOP, EDM, JAZZ, COUNTRY, FORK, IDOL, RnB };

/*
*	use this for printing music genre when it is instrumental music.
*/
enum Genre_INST { CLASSIC = 10, OST, NEWAGE, WORLD, TRADITIONAL, CCM };

/*
*	Item Information class
*/
class ItemType
{
private:
	int m_Type;					//곡 타입 (int): 1: 가요, 2: 연주곡
	string m_Name;				//곡명
	string m_Writer;			//작곡가
	string m_Player;			//가수 또는 연주자
	int m_Genre;				//장르
	string m_Lyrics;			//가사
	SortedList<string>* m_tag;	//태그 목록
	int tag_count;				//태크 카운트
	int num_play;				//재생 횟수
	string m_Id;				//고유 번호 ( 0으로 시작하면 오류 발생 )
	int f_Type;					//파일 종류.
	string f_Name;				//파일 이름 or 주소
public:

	//Constructor
	/**
	*	default constructor.
	*/
	ItemType();

	/**
	*	destructor.
	*/
	~ItemType();

	//Observer
	/**
	*	@brief	Get music type.
	*	@pre	music type is set
	*	@post	none.
	*	@return	music type(int),(1:팝, 2:연주곡)
	*/
	int GetType();

	/**
	*	@brief	Get music name.
	*	@pre	music name is set.
	*	@post	none.
	*	@return	music name.
	*/
	string GetName() const;

	/**
	*	@brief	Get writer.
	*	@pre	writer is set.
	*	@post	none.
	*	@return	writer.
	*/
	string GetWriter();

	/**
	*	@brief	Get player.
	*	@pre	player is set.
	*	@post	none.
	*	@return	player.
	*/
	string GetPlayer();

	/**
	*	@brief	Get genre.
	*	@pre	genre is set.
	*	@post	none.
	*	@return	genre.
	*/
	int GetGenre();

	/**
	*	@brief	Get lyrics.
	*	@pre	lyrics is set.
	*	@post	none.
	*	@return	lyrics.
	*/
	string GetLyrics();
	
	/**
	*	@brief	Get music id.
	*	@pre	music id is set.
	*	@post	none.
	*	@return	music id.
	*/
	string GetId() const;

	/**
	*	@brief	Get music tag count.
	*	@pre	music tag is set.
	*	@post	none.
	*	@return	music tag count.
	*/
	int GetTagCount() const;

	/**
	*	@brief	Get music play count.
	*	@pre	music play count is set.
	*	@post	none.
	*	@return	music play count.
	*/
	int GetPlayCount() const;

	/**
	*	@brief	Get music file type.
	*	@pre	music file type is set.
	*	@post	none.
	*	@return	music file type.
	*/
	int GetFileType();

	/**
	*	@brief	Get music play count.
	*	@pre	music play count is set.
	*	@post	none.
	*	@return	music play count.
	*/
	string GetFileName();

	//Transformer
	/**
	*	@brief	Set music type.
	*	@pre	none.
	*	@post	music type is set.
	*	@param	inType		music type.
	*/
	void SetType(int inType);

	/**
	*	@brief	Set music name.
	*	@pre	none.
	*	@post	music name is set.
	*	@param	inName		music name.
	*/
	void SetName(string inName);

	/**
	*	@brief	Set music writer.
	*	@pre	none.
	*	@post	music writer is set.
	*	@param	inWriter	music writer.
	*/
	void SetWriter(string inWriter);

	/**
	*	@brief	Set music player.
	*	@pre	none.
	*	@post	music player is set.
	*	@param	inPlayer	music player.
	*/
	void SetPlayer(string inPlayer);

	/**
	*	@brief	Set music genre.
	*	@pre	none.
	*	@post	music genre is set.
	*	@param	inGenre		music genre.
	*/
	void SetGenre(int inGenre);

	/**
	*	@brief	Set music lyrics.
	*	@pre	none.
	*	@post	music lyrics is set.
	*	@param	inLyrics	music lyrics.
	*/
	void SetLyrics(string inLyrics);

	/**
	*	@brief	Add music tag.
	*	@pre	none.
	*	@post	music tag is set.
	*	@param	inTag	music tag.
	*/
	void SetTag(string inTag);

	/**
	*	@brief	Set music id.
	*	@pre	none.
	*	@post	music id is set. ( ID doesn't start with '0' )
	*	@param	inId	music id.
	*/
	void SetId(string inId);

	/**
	*	@brief	Set music file type.
	*	@pre	none.
	*	@post	music file type is set.
	*	@param	inFtype	music file type.
	*/
	void SetFileType(int inFtype);

	/**
	*	@brief	Set music file name or address.
	*	@pre	none.
	*	@post	music file name is set.
	*	@param	inFtype	music file name.
	*/
	void SetFileName(string inFname);

	/**
	*	@brief	Set record.
	*	@pre	none.
	*	@post	every values are set.
	*	@param	inType	music type, inName	music name, inWriter	writer, inPlayer	music player, inGenre	music genre, inId	music id.)
	*/
	void SetRecord(int inType, string inName, string inWriter, string inPlayer, int inGenre, string inId);

	//Display
	/**
	*	@brief	Display music type on screen.
	*	@pre	music type is set.
	*	@post	music type is on screen.
	*/
	void DisplayTypeOnScreen();

	/**
	*	@brief	Display music name on screen.
	*	@pre	music name is set.
	*	@post	music name is on screen.
	*/
	void DisplayNameOnScreen();

	/**
	*	@brief	Display writer on screen.
	*	@pre	writer is set.
	*	@post	writer is on screen.
	*/
	void DisplayWriterOnScreen();

	/**
	*	@brief	Display player on screen.
	*	@pre	player is set.
	*	@post	player is on screen.
	*/
	void DisplayPlayerOnScreen();

	/**
	*	@brief	Display music genre on screen.
	*	@pre	music genre is set.
	*	@post	music genre is on screen.
	*/
	void DisplayGenreOnScreen();

	/**
	*	@brief	Display music lyrics on screen.
	*	@pre	music lyrics is set.
	*	@post	music lyrics is on screen.
	*/
	void DisplayLyricsOnScreen();

	/**
	*	@brief	Display music tag on screen.
	*	@pre	music taag is set.
	*	@post	music tag is on screen.
	*/
	void DisplayTagOnScreen();

	/**
	*	@brief	Display music id on screen.
	*	@pre	music id is set.
	*	@post	music id is on screen.
	*/
	void DisplayIdOnScreen();

	/**
	*	@brief	Display music file type on screen.
	*	@pre	music file type is set.
	*	@post	music file type is on screen.
	*/
	void DisplayFileTypeOnScreen();

	/**
	*	@brief	Display music file name or address on screen.
	*	@pre	music file name is set.
	*	@post	music file name is on screen.
	*/
	void DisplayFileNameOnScreen();

	/**
	*	@brief	Display record on screen.
	*	@pre	every values are set.
	*	@post	record is on screen.
	*/
	void DisplayRecordOnScreen();

	//Transformer
	/**
	*	@brief	Set music type from keyboard.
	*	@pre	none.
	*	@post	music type is set.
	*/
	void SetTypeFromKB();

	/**
	*	@brief	Set music name from keyboard.
	*	@pre	none.
	*	@post	music name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set writer from keyboard.
	*	@pre	none.
	*	@post	writer is set.
	*/
	void SetWriterFromKB();

	/**
	*	@brief	Set player from keyboard.
	*	@pre	none.
	*	@post	player is set.
	*/
	void SetPlayerFromKB();

	/**
	*	@brief	Set music genre from keyboard.
	*	@pre	none.
	*	@post	music genre is set.
	*/
	void SetGenreFromKB();

	/**
	*	@brief	Set music lyrics from keyboard.
	*	@pre	none.
	*	@post	music lyrics is set.
	*/
	void SetLyricsFromKB();

	/**
	*	@brief	Set music tags from keyboard.
	*	@pre	none.
	*	@post	music tags is set.
	*/
	void SetTagFromKB();

	/**
	*	@brief	Set music id from keyboard.
	*	@pre	none.
	*	@post	music id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Set music file type from keyboard.
	*	@pre	none.
	*	@post	music file type is set.
	*/
	void SetFileTypeFromKB();

	/**
	*	@brief	Set music file name from keyboard.
	*	@pre	none.
	*	@post	music file name is set.
	*/
	void SetFileNameFromKB();

	/**
	*	@brief	Set record from keyboard.
	*	@pre	none.
	*	@post	record is set.
	*/
	void SetRecordFromKB();

	//Read & Write File
	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	music record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new music record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well
	*/
	int WriteDataToFile(ofstream& fout);

	/**
	*	@brief	Execute music file or url.
	*	@pre	none.
	*	@post	music file type and name are set.
	*/
	void Play();

	/**
	*	Compare two itemtypes if they are same.
	*	@brief	Compare two item types if thery are same by item id.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.(equality)
	*	@param	data	target item for comparing.
	*	@return return true if they have same id, otherwise, return false.
	*/
	bool operator==(ItemType &data);

	/**
	*	Compare two itemtypes if they are same, OVERRIDING for comparing player.
	*	@brief	Compare two item types if thery are same by player name.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.(equality)
	*	@param	data	target item for comparing.
	*	@return return true if they have same player, otherwise, return false.
	*/
	bool operator==(string inPlayer);

	/**
	*	Compare two itemtypes if they are same, OVERRIDING for comparing genre.
	*	@brief	Compare two item types if thery are same by genre.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.(equality)
	*	@param	data	target item for comparing.
	*	@return return true if they have same genre, otherwise, return false.
	*/
	bool operator==(int inGenre);

	/**
	*	@brief	Compare two item types if left one is bigger.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.
	*	@param	data	target item for comparing.
	*	@return return true if left one has bigger ID, otherwise, return false.
	*/
	bool operator>(ItemType &data);

	/**
	*	@brief	Compare two item types if right one is bigger.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.
	*	@param	data	target item for comparing.
	*	@return return true if right one has bigger ID, otherwise, return false.
	*/
	bool operator<(ItemType &data);

	/**
	*	@brief	Tell if item type is empty.
	*	@pre	none.
	*	@post	know item type's emptiness.
	*	@return	return true if it is empty, otherwise, return false.
	*/
	bool operator!();

	/**
	*	@brief	Assign data's record to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by data's
	*	@return itemtype with record being filled.
	*/
	ItemType& operator=(const ItemType& data);

	/**
	*	@brief	Substitute data's ID to self's ID.
	*	@pre	data should be initialized.
	*	@post	ID is set by data's
	*	@return itemtype with ID being filled.
	*/
	ItemType& operator=(const string& data);

	/**
	*	@brief	Check if m_Name include keyword.
	*	@pre	self is initialized, and keyword is initialized.
	*	@post	check weather keyword is included in self item.
	*	@param	keyword	entered by user, keyword for searching. Search every item include keyword in name.
	*	@return	return true if there's keyword in name, otherwise,
				return false if there's no keyword in name.
	*/
	bool operator!=(string keyword);

	/**
	*	@brief	Substitute ID record to temp_ID.
	*	@pre	object should be initialized.
	*	@post	prarameter ID is set by record.
	*/
	void operator>>(int& temp_ID);

	/**
	*	@brief	Substitute genre record to temp_genre.
	*	@pre	object should be initialized.
	*	@post	prarameter genre is set by record.
	*/
	void operator>>(unsigned int& temp_Genre);

	/**
	*	@brief	Substitute Player record to temp_Player.
	*	@pre	object should be initialized.
	*	@post	prarameter player is set by record.
	*/
	void operator>>(string& temp_Player);

	/**
	*	@brief	Substitute play count to temp_numPlay.
	*	@pre	object should be initialized.
	*	@post	prarameter play count is set by record.
	*/
	void operator>>(float& temp_numPlay);

	/**
	*	@brief	Call data in class working as index operator.
	*	@pre	list should be initialized.
	*	@post	call data in index order.
	*	@param	index	insert order in list.
	*	@return return tag record in index string in m_tag.
	*/
	int GetIndexTag(int index, string& temp_tag);

	/**
	*	@brief	Call data in class working as index operator.
	*	@pre	list should be initialized.
	*	@post	call data in index order.
	*	@param	index	insert order in list.
	*	@return return tag record in index string in m_tag.
	*/
	int GetNextTag(string& temp_tag);

	void ResetTagList();

	/**
	*	@brief	Increase play count.
	*	@pre	none.
	*	@post	increase play count.
	*	@return	return *this with increased play count.
	*/
	ItemType& operator++();
};

