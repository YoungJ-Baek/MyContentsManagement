#pragma once

#include <QDialog>
#include <QMessageBox>
#include <string>
#include <fstream>
#include <Windows.h>
#include "ui_Register.h"

using namespace std;
/**
*	Register class.
*/
class Register : public QDialog
{
	Q_OBJECT

public:
	/**
	*	constructor.
	*/
	Register(QWidget *parent = Q_NULLPTR);
	/**
	*	destructor.
	*/
	~Register();

private:
	Ui::Register *ui;
	string ID;			//ID
	string PW;			//PassWord

private slots:
	/**
	*	@brief	Exit button clicked event.
	*	@pre	Exit button clicked.
	*	@post	end program.
	*/
	void on_push_exit_clicked();
	/**
	*	@brief	Register button clicked event.
	*	@pre	Register button clicked.
	*	@post	Register user data.
	*/
	void on_push_register_clicked();
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

};
