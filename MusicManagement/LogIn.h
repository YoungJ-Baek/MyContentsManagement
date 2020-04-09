#pragma once

#include <QDialog>
#include <QMessageBox>
#include <string>
#include <fstream>
#include <Windows.h>
#include "ui_LogIn.h"

using namespace std;
/**
*	LogIn class.
*/
class LogIn : public QDialog
{
	Q_OBJECT

public:
	/**
	*	constructor.
	*/
	LogIn(QWidget *parent = Q_NULLPTR);
	/**
	*	destructor.
	*/
	~LogIn();
	/**
	*	@brief	Get Size.
	*	@pre	none.
	*	@post	none.
	*	@return	int size.
	*/
	int GetSize();

private:
	Ui::LogIn *ui;
	string ID;		//ID
	string PW;		//Password
	int size;		//size

private slots:
	/**
	*	@brief	Exit button clicked event.
	*	@pre	Exit button clicked.
	*	@post	end program.
	*/
	void on_push_exit_clicked();
	/**
	*	@brief	LogIn button clicked event.
	*	@pre	LogIn button clicked.
	*	@post	log in, get to main window.
	*/
	void on_push_login_clicked();
	/**
	*	@brief	Store id for text changed.
	*	@pre	id text changed.
	*	@post	store id.
	*/
	void on_ID_edit_textChanged(const QString &arg1);
	/**
	*	@brief	Store password for text changed.
	*	@pre	password text changed.
	*	@post	store password.
	*/
	void on_PW_edit_textChanged(const QString &arg1);
	/**
	*	@brief	Store master list size for text changed.
	*	@pre	master list size text changed.
	*	@post	store master list size.
	*/
	void on_Size_edit_textChanged(const QString &arg1);
};
