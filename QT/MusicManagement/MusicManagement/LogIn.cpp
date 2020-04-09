#include "LogIn.h"

LogIn::LogIn(QWidget *parent)
	: QDialog(parent), ui(new Ui::LogIn)
{
	ui->setupUi(this);
}

LogIn::~LogIn()
{
	delete ui;
}

int LogIn::GetSize() { return size; }

void LogIn::on_push_exit_clicked()
{
	reject();
}

void LogIn::on_push_login_clicked()
{
	if (ID.empty() || PW.empty())
		return;
	ifstream user;
	user.open("user.txt");
	string user_ID;
	string user_PW;
	user >> user_ID;
	user >> user_PW;
	user.close();
	if (ID == user_ID && PW == user_PW)
		accept();
	else
		QMessageBox::information(this, "Error", "Wrong Information!");
}

void LogIn::on_ID_edit_textChanged(const QString &arg1)
{
	ID = arg1.toStdString();
}

void LogIn::on_PW_edit_textChanged(const QString &arg1)
{
	PW = arg1.toStdString();
}

void LogIn::on_Size_edit_textChanged(const QString &arg1)
{
	size = arg1.toInt();
}