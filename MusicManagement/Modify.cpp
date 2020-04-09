#include "Modify.h"
#include "ui_Modify.h"
extern MusicManagement *Main;

Modify::Modify(string ID, QWidget *parent)
	: QDialog(parent), ui(new Ui::Modify)
{
	QIntValidator *intValidator = new QIntValidator(0, 9999999999);
	addition.SetId(ID);
	ui->setupUi(this);
	ui->edit_genre->setValidator(intValidator);
	ui->edit_type->setValidator(intValidator);
	ui->edit_ftype->setValidator(intValidator);
}

Modify::~Modify()
{
	delete ui;
}

void Modify::on_edit_name_textChanged(const QString &arg1)
{
	addition.SetName(arg1.toStdString());
}

void Modify::on_edit_singer_textChanged(const QString &arg1)
{
	addition.SetPlayer(arg1.toStdString());
}

void Modify::on_edit_genre_activated(const QString &arg1)
{
	if (arg1.toStdString() == "Genre")
		addition.SetGenre(0);
	if (arg1.toStdString() == "Pop")
		addition.SetGenre(1);
	if (arg1.toStdString() == "Ballad")
		addition.SetGenre(2);
	if (arg1.toStdString() == "Rock")
		addition.SetGenre(3);
	if (arg1.toStdString() == "HipHop")
		addition.SetGenre(4);
	if (arg1.toStdString() == "EDM")
		addition.SetGenre(5);
	if (arg1.toStdString() == "Jazz")
		addition.SetGenre(7);
	if (arg1.toStdString() == "Classic")
		addition.SetGenre(10);
	if (arg1.toStdString() == "NewAge")
		addition.SetGenre(12);
}

void Modify::on_edit_tag_textChanged(const QString &arg1)
{
	tag = arg1.toStdString();
}

void Modify::on_edit_type_activated(const QString &arg1)
{
	if (arg1.toStdString() == "Type")
		addition.SetType(0);
	if (arg1.toStdString() == "Pop")
		addition.SetType(1);
	if (arg1.toStdString() == "Instrumental")
		addition.SetType(2);
}

void Modify::on_edit_writer_textChanged(const QString &arg1)
{
	addition.SetWriter(arg1.toStdString());
}

void Modify::on_edit_ftype_activated(const QString &arg1)
{
	if (arg1.toStdString() == "File Type")
		addition.SetFileType(0);
	if (arg1.toStdString() == "File")
		addition.SetFileType(1);
	if (arg1.toStdString() == "URL")
		addition.SetFileType(2);
}

void Modify::on_edit_fname_textChanged(const QString &arg1)
{
	addition.SetFileName(arg1.toStdString());
}

void Modify::on_push_tag_clicked()
{
	addition.SetTag(tag);
}

void Modify::on_push_close_clicked()
{
	QMessageBox MsgBox;
	MsgBox.setWindowTitle("Stop Modify");
	MsgBox.setText("Stop Modifying?");
	MsgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	MsgBox.setDefaultButton(QMessageBox::Ok);
	if (MsgBox.exec() == QMessageBox::Ok)
		this->close();
}

void Modify::on_push_add_clicked()
{
	QString str = ui->edit_lyrics->toPlainText();
	addition.SetLyrics(str.toStdString());
	if (addition.GetName().empty() || addition.GetPlayer().empty() || addition.GetWriter().empty() || addition.GetGenre() == 0 || addition.GetType() == 0 || addition.GetFileType() == 0 || addition.GetFileName().empty())
		return;
	else
	{
		Main->AddMusic(addition);
		this->close();
	}
}