#pragma once
#include "SortedList.h"
#include "CircularQueue.h"
#include "PlayItem.h"
#include "ItemType.h"
#include "SortedLinkedList.h"
#include "SingerType.h"
#include "DoublySortedLinkedList.h"
#include "GenreType.h"
#include "TagType.h"
#include "BinarySearchTree.h"
#include "CountType.h"
#include "CircularQueue.h"
#include "CHeapBase.h"
#include "CMaxHeap.h"

#define FILENAMESIZE 100

/**
*	application class for music playlist(management).
*/
class Application
{
public:

	/**
	*	default constructor.
	*/
	Application();

	/**
	*	destructor.
	*/
	~Application();

	/**
	*	@brief	Register user.
	*	@pre	program is started.
	*	@post	user data set.
	*/
	void MakeUserData();

	/**
	*	@brief	Log In.
	*	@pre	register complete.
	*	@post	run program driver.
	*/
	void LogIn(ifstream& user);

	/**
	*	@brief	Program driver.
	*	@pre	log in complete.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Master List driver.
	*	@pre	input 1 in Run() function.
	*	@post	open Master List Menu.
	*/
	void Run_MasterList();

	/**
	*	@brief	Play List driver.
	*	@pre	input 2 in Run() function.
	*	@post	open Play List Menu.
	*/
	void Run_PlayList();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommand();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	Master List open.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommandMasterList();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	Play List open.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommandPlayList();

	/**
	*	@brief	Dynamic Allocate Master List by default state or user input.
	*	@pre	none.
	*	@post	master list initialized.
	*/
	void AllocateMasterList();



	//Master List Command.

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddMusic();

	/**
	*	@brief	Delete record into list.
	*	@pre	list should be initialized.
	*	@post	record is deleted from the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteMusic();

	/**
	*	@brief	Replace record.
	*	@pre	list should be initialized.
	*	@post	new record is replaced into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReplaceMusic();

	/**
	*	@brief	Open Display tool.
	*	@pre	none.
	*	@post	none.
	*/
	void Display();

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllMusic();

	/**
	*	@brief	Display recent played musics in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayRecentMusic();

	/**
	*	@brief	Display played musics in the list of priority on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayPriorityMusic();

	/**
	*	@brief	Make list Empty.
	*	@pre	none.
	*	@post	make list empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Recommend songs by priority.
	*	@pre	none.
	*	@post	display recommend list.
	*/
	void RecommendSong();

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName	a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(char *fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(char *fileName);

	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile();

	/**
	*	@brief	Open a file as a write mode, and write all data into the file,
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile();

	/**
	*	@brif	open searching tool by id or name.
	*	@pre	none.
	*	@post	open searchbyid or searchbyname by user's input.
	*/
	void Search();

	/**
	*	@brief	Search record and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int SearchById_SequenS();

	/**
	*	@brief	Search record by name and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int SearchByName();

	/**
	*	@brief	Search record by lyrics and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int SearchByLyrics();

	/**
	*	@brief	Search record by singer and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int SearchBySinger();

	/**
	*	@brief	Search record by gnere and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int SearchByGenre();

	/**
	*	@brief	Search record by tag and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int SearchByTag();


	//Search List Operation.

	/**
	*	@brief	Add new genre into genre list.
	*	@pre	genre list should be initialized.
	*	@post	new genre is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void AddGenre(GenreType data);

	/**
	*	@brief	Add new singer into singer list.
	*	@pre	singer list should be initialized.
	*	@post	new singer is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void AddSinger(SingerType data);

	/**
	*	@brief	Add new tag into tag list.
	*	@pre	tag list should be initialized.
	*	@post	new tag is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void AddTag(TagType data);

	/**
	*	@brief	Add new song into search list's song list.
	*	@pre	search lists should be initialized.
	*	@post	new song is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddSong(ItemType data);




	//Play List Operation.

	/**
	*	@brief	Add new song into play list.
	*	@pre	play list should be initialized.
	*	@post	new song is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddSongToPL();

	/**
	*	@brief	Delete record in list.
	*	@pre	play list should be initialized.
	*	@post	record is deleted from the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteSongFrPL();

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayPlayList();

	/**
	*	@brif	open play tool.
	*	@pre	none.
	*	@post	open play functions by user's input.
	*/
	void Play();

	/**
	*	@brief	Play songs in insert time order.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void PlayIOAddTime();

	/**
	*	@brief	Play songs in frequency order.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void PlayIOFreq();

	/**
	*	@brief	Play songs in random order.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void PlayIORandom();

	/**
	*	@brief	Turn on / off repeatability of play list.
	*	@pre	list should be initialized.
	*	@post	r_PlayList changes.
	*/
	void ChangeRepeatability();


	/**
	*	@brief	Open a file by file descriptor as an input file in play list.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName	a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int PLOpenInFile(char *fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file in play list.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int PLOpenOutFile(char *fileName);

	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data in play list.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int PLReadDataFromFile();

	/**
	*	@brief	Open a file as a write mode, and write all data into the file in play list.
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int PLWriteDataToFile();



private:
	ifstream m_InFile;							//input file descriptor. master list
	ofstream m_OutFile;							//output file descriptor. master list
	ifstream p_InFile;							//input file descriptor. play list
	ofstream p_OutFile;							//output file descriptor. play list
	SortedList<ItemType> *m_List;				//item list.
	BinarySearchTree<SingerType> SList;			//singer list.
	DoublySortedLinkedList<PlayItem> PlayList;	//play list.
	DoublySortedLinkedList<GenreType> GList;	//genre list.
	DoublySortedLinkedList<TagType> TList;		//tag list.
	SortedList<CountType> *CountList;			//Play Count List.
	CircularQueueType<SongType> *RecentList;	//Recent Play List.
	CHeapBase<CountType>* PriorityList;			//재생횟수 순 리스트.
	int m_Command;								//current command number.
	int count;									//play list 에 있는 노래 수.
	int play_count;								//현재 재생 목록 중 재생한 수.
	bool checkMasterList;						//마스터 리스트 생성 여부
	bool r_PlayList;							//Play List 반복 재생 여부 
};
