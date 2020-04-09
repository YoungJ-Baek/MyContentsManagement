#pragma once

#include <QDialog>
#include "ui_PlayListWidget.h"
#include "MusicManagement.h"
#include "CHeapBase.h"
#include "CMaxHeap.h"
#include "CountType.h"

namespace Ui {
	class PlayListWidget;
}
/**
*	play list widget class
*/
class PlayListWidget : public QDialog
{
	friend class MusicManagement;
	Q_OBJECT

public:
	/**
	*	constructor.
	*/
	PlayListWidget(QWidget *parent = Q_NULLPTR);
	/**
	*	destructor.
	*/
	~PlayListWidget();
	/**
	*	@brief	Display PlayList.
	*	@pre	none.
	*	@post	none.
	*/
	void displayall();
	/**
	*	@brief	Info button clicked event.
	*	@pre	Info button clicked.
	*	@post	Info widget open.
	*/
	void onClicked_Info();
	/**
	*	@brief	NowInfo button clicked event.
	*	@pre	NowInfo button clicked.
	*	@post	Info widget open.
	*/
	void onClicked_nowInfo();
	/**
	*	@brief	Next button clicked event in insert play order.
	*	@pre	Next button clicked.
	*	@post	Play next song.
	*/
	void onClicked_insert();
	/**
	*	@brief	Next button clicked event in frequency play order.
	*	@pre	Next button clicked.
	*	@post	Play next song.
	*/
	void onClicked_frequency();
	/**
	*	@brief	Next button clicked event in random play order.
	*	@pre	Next button clicked.
	*	@post	Play next song.
	*/
	void onClicked_random();

private slots:
	/**
	*	@brief	AddSong button clicked event.
	*	@pre	AddSong button clicked.
	*	@post	AddSong widget open.
	*/
	void on_push_add_clicked();
	/**
	*	@brief	Refresh button clicked event.
	*	@pre	Refresh button clicked.
	*	@post	display play list.
	*/
	void on_push_refresh_clicked();
	/**
	*	@brief	Store fstream keyword for text changed.
	*	@pre	fstream keyword text changed.
	*	@post	store fstream keyword.
	*/
	void on_edit_fstream_textChanged(const QString &arg1);
	/**
	*	@brief	Save button clicked event.
	*	@pre	Save button clicked and keyword set.
	*	@post	save data base file.
	*/
	void on_push_save_clicked();
	/**
	*	@brief	Open button clicked event.
	*	@pre	Open button clicked and keyword set.
	*	@post	open data base file.
	*/
	void on_push_open_clicked();
	/**
	*	@brief	Close button clicked event.
	*	@pre	Close button clicked.
	*	@post	close widget.
	*/
	void on_push_close_clicked();
	/**
	*	@brief	add text changed event.
	*	@pre	add text changed.
	*	@post	none.
	*/
	void on_edit_add_textChanged(const QString &arg1);
	/**
	*	@brief	Delete button clicked event.
	*	@pre	Delete button clicked.
	*	@post	delete contents from master list.
	*/
	void on_push_delete_clicked();
	/**
	*	@brief	Pinsert button clicked event.
	*	@pre	Pinsert button clicked.
	*	@post	play insert order.
	*/
	void on_push_pinsert_clicked();
	/**
	*	@brief	Pfrequency button clicked event.
	*	@pre	Pfrequency button clicked.
	*	@post	play frequency order.
	*/
	void on_push_pfrequency_clicked();
	/**
	*	@brief	random button clicked event.
	*	@pre	random button clicked.
	*	@post	play random order.
	*/
	void on_push_random_clicked();
	/**
	*	@brief	Repeat button clicked event.
	*	@pre	Repeat button clicked.
	*	@post	change repeatability.
	*/
	void on_push_repeat_clicked();

private:
	CHeapBase<CountType>* PriorityList;			//재생횟수 순 리스트.
	string filename;							//filename keyword
	string add_id;								//id for addition
	Ui::PlayListWidget *ui;
	QWidget* pWidget_Info;
	QPushButton* btn_Info;
	int pre_index;								//pre_index to avoid repeat
	int play_index;								//now play index
	int order;									//front order, back order

	int now_play;


	enum Column
	{
		ID, TITLE, ARTIST, GENRE, INFO, NEXT
	};
};
