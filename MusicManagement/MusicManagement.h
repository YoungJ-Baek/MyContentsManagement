#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QSignalMapper>
#include <QCheckBox>
#include <string>
#include <QAction>
#include <QMessageBox>
#include <QHBoxLayout>

#include "ui_MusicManagement.h"
#include "Register.h"
#include "LogIn.h"
#include "Info.h"
#include "AddSong.h"
#include "Modify.h"
#include "PlayListWidget.h"

#include "BinarySearchTree.h"
#include "CHeapBase.h"
#include "CMaxHeap.h"
#include "CircularQueue.h"
#include "CountType.h"
#include "DoublyIterator.h"
#include "DoublySortedLinkedList.h"
#include "GenreType.h"
#include "ItemType.h"
#include "PlayItem.h"
#include "SingerType.h"
#include "SongType.h"
#include "SortedList.h"
#include "TagType.h"

#define FILENAMESIZE 100

/**
*	main window class for music playlist(management).
*/
class MusicManagement : public QMainWindow
{
	Q_OBJECT

public:
	/**
	*	constructor.
	*/
	MusicManagement(int m_listSize, QWidget *parent = Q_NULLPTR);
	/**
	*	destructor.
	*/
	~MusicManagement();
	/**
	*	@brief	Display MasterList.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAll();
	/**
	*	Call data in list.
	*	@brief	call data in Playlist in index order.
	*	@pre	list should be initialized.
	*	@post	call PlayList data in index order.
	*	@param	index	insert order in list.
	*	@return return data.
	*/
	PlayItem& at(int index);
	/**
	*	@brif	find index in the list with target data USING BINARY SEARCH
	*	@pre	data's id is set by keyboard. optionally other values, too
	*	@post	if data is empty, data's record is set by record in index
	*	@param	data	item type for searching, must have music id
	*					optionally have other values if you choose replace function.
	*	@return	return index number if search successes, otherwise
	*			return -1 if search fails.
	*/
	int SimpleSearch(ItemType& temp);
	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@param	add	item type for addition, must have music id
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddMusic(ItemType add);
	/**
	*	@brief	Delete record into list.
	*	@pre	list should be initialized.
	*	@post	record is deleted from the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void DeleteMusic();
	/**
	*	@brief	Add new song into search list's song list.
	*	@pre	search lists should be initialized.
	*	@post	new song is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void Addsong(ItemType data);

	/**
	*	@brief	리스트가 비었는지 아닌지 검사한다.
	*	@pre	none.
	*	@post	비었는지 아닌지를 알려준다.
	*	@return	비어있으면 true, 아니면 false를 반환.
	*/
	bool CheckPlayList();
	/**
	*	@brief	반복 재생 여부를 확인한다.
	*	@pre	none.
	*	@post	none.
	*	@return	반복이면 true, 아니면 false를 반환.
	*/
	bool CheckRepeatability() { return r_PlayList; };
	/**
	*	@brief	플레이 리스트 처음으로 돌린다.
	*	@pre	없음.
	*	@post	none.
	*/
	void resetPlayList();
	/**
	*	@brief	재생된 플레이 리스트 곡 수 확인.
	*	@pre	없음.
	*	@post	none.
	*	@return	return play_count.
	*/
	int GetPlayCount() { return play_count; };
	/**
	*	@brief	재생된 플레이 리스트 곡 수 세팅.
	*	@pre	없음.
	*	@post	play_count set.
	*/
	void SetPlayCount(int data) { play_count = data; };
	/**
	*	@brief	플레이 리스트 곡 수 확인.
	*	@pre	없음.
	*	@post	none.
	*	@return	return count.
	*/
	int GetPlayListSize() { return count; };
	/**
	*	@brief	플레이 리스트 다음 곡 호출.
	*	@pre	없음.
	*	@post	index increase
	*	@param	temp	copy data.
	*	@return	return index if success.
				return -1 if end.
	*/
	int GetNextPlayItem(PlayItem& temp);
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
	int PLOpenOutFile(char* fileName);
	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data in play list.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int PLReadDataFromFile(char* fileName);
	/**
	*	@brief	Open a file as a write mode, and write all data into the file in play list.
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int PLWriteDataToFile(char* fileName);
	/**
	*	@brief	Add new song into play list.
	*	@pre	play list should be initialized.
	*	@post	new song is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddSongToPL(string& temp_id);
	/**
	*	@brief	Delete record in list.
	*	@pre	play list should be initialized.
	*	@post	record is deleted from the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteSongFrPL(string& temp_id);
	/**
	*	@brief	Turn on / off repeatability of play list.
	*	@pre	list should be initialized.
	*	@post	r_PlayList changes.
	*/
	bool ChangeRepeatability();
	/**
	*	@brief	Execute music file or url.
	*	@pre	music file type and name are set.
	*	@post	none.
	*	@param	temp_id		search id
	*			play_index	playlist order
	*			temp_db		data
	*/
	void Play(string temp_id, int play_index, ItemType& temp_db);

	/**
	*	@brief	Search record and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void SearchByID();
	/**
	*	@brief	Search record by name and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void SearchByName();
	/**
	*	@brief	Search record by singer and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void SearchBySinger();
	/**
	*	@brief	Search record by gnere and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void SearchByGenre();
	/**
	*	@brief	Search record by tag and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void SearchByTag();
	/**
	*	@brief	Search record by lyrics and display it.
	*	@pre	list should be initialized.
	*	@post	none.
	*/
	void SearchByLyrics();

private slots:
	/**
	*	@brief	Info button clicked event.
	*	@pre	Info button clicked.
	*	@post	Info widget open.
	*/
	void onClicked_Info();
	/**
	*	@brief	Add button clicked event.
	*	@pre	Add button clicked.
	*	@post	Add contents to playlist.
	*/
	void onClicked_AddToPlaylist();

	/**
	*	@brief	Exit button clicked event.
	*	@pre	Exit button clicked.
	*	@post	end program.
	*/
	void on_push_exit_clicked();

	/**
	*	@brief	Store fstream keyword for text changed.
	*	@pre	fstream keyword text changed.
	*	@post	store fstream keyword.
	*/
	void on_edit_fstream_textChanged(const QString &arg1);
	/**
	*	@brief	Open button clicked event.
	*	@pre	Open button clicked and keyword set.
	*	@post	open data base file.
	*/
	int on_push_open_clicked();
	/**
	*	@brief	Save button clicked event.
	*	@pre	Save button clicked and keyword set.
	*	@post	save data base file.
	*/
	int on_push_save_clicked();

	/**
	*	@brief	AddSong button clicked event.
	*	@pre	AddSong button clicked.
	*	@post	AddSong widget open.
	*/
	void on_push_add_clicked();

	/**
	*	@brief	Delete text changed event.
	*	@pre	Delete text changed.
	*	@post	delete conotents from master list.
	*/
	void on_edit_delete_textChanged(const QString &arg1);
	/**
	*	@brief	Delete button clicked event.
	*	@pre	Delete button clicked.
	*	@post	delete contents from master list.
	*/
	void on_push_delete_clicked();

	/**
	*	@brief	Modify button clicked event.
	*	@pre	Modify button clicked.
	*	@post	Modify widget open.
	*/
	void on_push_modify_clicked();

	/**
	*	@brief	MakeEmpty button clicked event.
	*	@pre	MakeEmpty button clicked.
	*	@post	make master list empty.
	*/
	void on_push_make_empty_clicked();

	/**
	*	@brief	PlayList button clicked event.
	*	@pre	PlayList button clicked.
	*	@post	PlayListWidget open.
	*/
	void on_push_playlist_clicked();

	/**
	*	@brief	Recent button clicked event.
	*	@pre	Recent button clicked.
	*	@post	Recent list shows on result list.
	*/
	void on_push_recent_clicked();
	/**
	*	@brief	Priority button clicked event.
	*	@pre	Priority button clicked.
	*	@post	Priority list shows on result list.
	*/
	void on_push_priority_clicked();
	/**
	*	@brief	Recommend button clicked event.
	*	@pre	Recommend button clicked.
	*	@post	Recommend list shows on result list.
	*/
	void on_push_recommend_clicked();

	void on_search_type_activated(const QString &arg1);

	void on_push_search_clicked();

	void on_edit_search_textChanged(const QString &arg1);

private:
	Ui::MusicManagementClass *ui;

	QSignalMapper* checkboxMapper;
	QWidget* pWidget_Info;
	QPushButton* btn_Info;
	QWidget* pWidget_add;
	QPushButton* btn_add;

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

	int count;									//play list 에 있는 노래 수.
	int play_count;								//현재 재생 목록 중 재생한 수.
	bool r_PlayList;							//Play List 반복 재생 여부 
	int index;									//현재 가리키는 플레이 리스트


	string fstream_keyword;						//파일 열기위한 검색어
	string delete_ID;							//삭제, 수정 위한 검색어
	string search_type;							//콤보박스 통해 고르는 검색 종류
	string search_keyword;						//검색 위한 검색어
	enum Column
	{
		ID, TITLE, ARTIST, GENRE, ADD, INFO
	};
};
