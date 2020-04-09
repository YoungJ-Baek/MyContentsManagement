#pragma once

#include <QDialog>
#include "ui_AddSong.h"
#include "MusicManagement.h"

#include <ctime>

namespace Ui {
	class AddSong;
}
/**
*	AddSong class.
*/
class AddSong : public QDialog
{
	Q_OBJECT

public:
	/**
	*	constructor.
	*/
	AddSong(QWidget *parent = Q_NULLPTR);
	/**
	*	destructor.
	*/
	~AddSong();

private slots:
	/**
	*	@brief	Store id for text changed.
	*	@pre	edit id changed.
	*	@post	store edit id.
	*/
	void on_edit_id_textChanged(const QString &arg1);
	/**
	*	@brief	Store name for text changed.
	*	@pre	edit name changed.
	*	@post	store edit name.
	*/
	void on_edit_name_textChanged(const QString &arg1);
	/**
	*	@brief	Store singer for text changed.
	*	@pre	edit singer changed.
	*	@post	store edit singer.
	*/
	void on_edit_singer_textChanged(const QString &arg1);
	/**
	*	@brief	Store genre for combobox activated.
	*	@pre	combobox activated.
	*	@post	store edit genre.
	*/
	void on_edit_genre_activated(const QString &arg1);
	/**
	*	@brief	Store tag for text changed.
	*	@pre	edit tag changed.
	*	@post	store edit tag.
	*/
	void on_edit_tag_textChanged(const QString &arg1);
	/**
	*	@brief	Store type for combobox activated.
	*	@pre	combobox activated.
	*	@post	store edit type.
	*/
	void on_edit_type_activated(const QString &arg1);
	/**
	*	@brief	Store writer for text changed.
	*	@pre	edit writer changed.
	*	@post	store edit writer.
	*/
	void on_edit_writer_textChanged(const QString &arg1);
	/**
	*	@brief	Store filetype for combobox activated.
	*	@pre	combobox activated.
	*	@post	store edit filetype.
	*/
	void on_edit_ftype_activated(const QString &arg1);
	/**
	*	@brief	Store filename for text changed.
	*	@pre	edit filename changed.
	*	@post	store edit filename.
	*/
	void on_edit_fname_textChanged(const QString &arg1);
	/**
	*	@brief	Tag button clicked event.
	*	@pre	Tag button clicked and keyword set.
	*	@post	Add tag.
	*/
	void on_push_tag_clicked();
	/**
	*	@brief	Close button clicked event.
	*	@pre	Close button clicked and keyword set.
	*	@post	close widget.
	*/
	void on_push_close_clicked();
	/**
	*	@brief	Add button clicked event.
	*	@pre	Add button clicked and keyword set.
	*	@post	Add content to master list.
	*/
	void on_push_add_clicked();

private:
	string ID;			//ID
	string tag;			//Tag
	Ui::AddSong *ui;
	ItemType addition;	//ItemType for addition
};

