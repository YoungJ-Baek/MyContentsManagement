#include "Register.h"

Register::Register(QWidget *parent)
	: QDialog(parent), ui(new Ui::Register)
{
	ui->setupUi(this);
}

Register::~Register()
{
	delete ui;
}

void Register::on_push_exit_clicked()
{
	reject();
}

void Register::on_push_register_clicked()
{
	if (ID.empty() || PW.empty())
		return;
	ofstream user;
	user.open("user.txt");
	user << ID << endl;
	user << PW << endl;
	DWORD attributes = GetFileAttributes(L"user.txt");
	SetFileAttributes(L"user.txt", attributes + FILE_ATTRIBUTE_HIDDEN);
	user.close();
	accept();
}

void Register::on_ID_edit_textChanged(const QString &arg1)
{
	ID = arg1.toStdString();
}

void Register::on_PW_edit_textChanged(const QString &arg1)
{
	PW = arg1.toStdString();
}