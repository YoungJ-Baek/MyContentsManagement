#include "Info.h"
#include "ui_Info.h"

Info::Info(ItemType item, QWidget *parent)
	: QDialog(parent), ui(new Ui::Info)
{
	ui->setupUi(this);
	ui->label_name->setText(QString::fromStdString(item.GetName()));
	ui->label_singer->setText(QString::fromStdString(item.GetPlayer()));
	ui->label_genre->setText(QString::fromStdString(to_string(item.GetGenre())));
	layout = new QVBoxLayout(ui->area_lyrics);
	if (item.GetLyrics().empty())
		layout->addWidget(new QLabel("No Lyrics"));
	else
		layout->addWidget(new QLabel(QString::fromStdString(item.GetLyrics())));
	layout = new QVBoxLayout(ui->area_tag);
	string temp_tag;
	string tag_list = "";;
	item.ResetTagList();
	while (item.GetNextTag(temp_tag) != -1)
	{
		tag_list = tag_list + "\n" + temp_tag;
	}
	if(tag_list=="")
		layout->addWidget(new QLabel("No Tag"));
	else
		layout->addWidget(new QLabel(QString::fromStdString(tag_list)));
}

Info::~Info()
{
	delete ui;
}


void Info::on_push_close_clicked()
{
	close();
}