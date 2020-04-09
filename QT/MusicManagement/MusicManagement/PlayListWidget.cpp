#include "PlayListWidget.h"
#include "ui_PlayListWidget.h"
extern MusicManagement *Main;

PlayListWidget::PlayListWidget(QWidget *parent)
	: QDialog(parent), ui(new Ui::PlayListWidget)
{
	PriorityList = new CMaxHeap<CountType>(Main->GetPlayListSize());
	ui->setupUi(this);
	ui->PlayList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->PlayList->setRowCount(0);
	ui->PlayList->setColumnWidth(ID, 50);
	ui->PlayList->setColumnWidth(TITLE, 100);
	ui->PlayList->setColumnWidth(ARTIST, 100);
	ui->PlayList->setColumnWidth(GENRE, 70);
	ui->PlayList->setColumnWidth(INFO, 90);
	pre_index = -1;
	play_index = 1;
	now_play = 0;
	order = 1;

	displayall();
}

PlayListWidget::~PlayListWidget()
{
	delete ui;
}

void PlayListWidget::displayall()
{
	ui->PlayList->setRowCount(0);

	if (Main->CheckPlayList() == true)
	{
		ui->PlayList->setRowCount(1);
		ui->PlayList->setItem(0, 0, new QTableWidgetItem("Empty"));
	}
	else
	{
		Main->resetPlayList();
		PlayItem temp;
		while (Main->GetNextPlayItem(temp) != -1)
		{
			ui->PlayList->insertRow(ui->PlayList->rowCount());
			int index = ui->PlayList->rowCount() - 1;

			pWidget_Info = new QWidget();
			btn_Info = new QPushButton();
			btn_Info->setText("More");
			connect(btn_Info, &QPushButton::clicked, this, &PlayListWidget::onClicked_Info);
			QHBoxLayout* pLayout = new QHBoxLayout(pWidget_Info);
			pLayout->addWidget(btn_Info);
			pLayout->setAlignment(Qt::AlignCenter);
			pLayout->setContentsMargins(0, 0, 0, 0);
			pWidget_Info->setLayout(pLayout);

			ItemType db;
			string genre;
			db.SetId(temp.GetId());
			Main->SimpleSearch(db);
			QTableWidgetItem* id = new QTableWidgetItem(QString::fromStdString(db.GetId()));
			QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(db.GetName()));
			QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(db.GetPlayer()));
			if (db.GetGenre() == 0)
				genre = "Unknown";
			if (db.GetGenre() == 1)
				genre = "Pop";
			if (db.GetGenre() == 2)
				genre = "Ballad";
			if (db.GetGenre() == 3)
				genre = "Rock";
			if (db.GetGenre() == 4)
				genre = "HipHop";
			if (db.GetGenre() == 5)
				genre = "EDM";
			if (db.GetGenre() == 7)
				genre = "Jazz";
			if (db.GetGenre() == 10)
				genre = "Classic";
			if (db.GetGenre() == 12)
				genre = "NewAge";
			QTableWidgetItem* pgenre = new QTableWidgetItem(QString::fromStdString(genre));
			id->setTextAlignment(Qt::AlignCenter);
			name->setTextAlignment(Qt::AlignCenter);
			player->setTextAlignment(Qt::AlignCenter);
			pgenre->setTextAlignment(Qt::AlignCenter);
			ui->PlayList->setItem(index, ID, id);
			ui->PlayList->setItem(index, TITLE, name);
			ui->PlayList->setItem(index, ARTIST, player);
			
			
			ui->PlayList->setItem(index, GENRE, pgenre);

			ui->PlayList->setCellWidget(index, INFO, pWidget_Info);
		}
	}
}

void PlayListWidget::onClicked_Info()
{
	QWidget *w = qobject_cast<QWidget *>(sender()->parent());

	int row = ui->PlayList->indexAt(w->pos()).row();
	ItemType temp;
	temp.SetId(Main->at(row).GetId());
	Main->SimpleSearch(temp);

	Info infowidget(temp);
	infowidget.exec();
}

void PlayListWidget::on_edit_add_textChanged(const QString &arg1)
{
	add_id = arg1.toStdString();
}

void PlayListWidget::on_push_add_clicked()
{
	int det = Main->AddSongToPL(add_id);
	if(det==1)
		QMessageBox::information(this, "Success!", "Addition Complete");
	displayall();
}


void PlayListWidget::on_push_refresh_clicked()
{
	displayall();
}

void PlayListWidget::on_edit_fstream_textChanged(const QString &arg1)
{
	filename = arg1.toStdString();
}

void PlayListWidget::on_push_save_clicked()
{
	char *fileName = new char[filename.size() + 1];
	copy(filename.begin(), filename.end(), fileName);
	fileName[filename.size()] = '\0';
	Main->PLWriteDataToFile(fileName);
}

void PlayListWidget::on_push_open_clicked()
{
	char *fileName = new char[filename.size() + 1];
	copy(filename.begin(), filename.end(), fileName);
	fileName[filename.size()] = '\0';
	Main->PLReadDataFromFile(fileName);
	displayall();
}

void PlayListWidget::on_push_close_clicked()
{
	this->close();
}

void PlayListWidget::on_push_delete_clicked()
{
	int det = Main->DeleteSongFrPL(add_id);
	if(det==1)
		QMessageBox::information(this, "Success!", "Delete Complete");
	displayall();
}

void PlayListWidget::on_push_pinsert_clicked()
{
	ui->now_info->disconnect();
	ui->now_next->disconnect();
	PlayItem temp_play;
	string temp_id;
	
	ItemType temp_db;
	for (int i = 0; i < Main->GetPlayListSize(); i++)
		if (Main->at(i) == play_index)
			temp_play = Main->at(i);
	temp_play >> temp_id;
	temp_db = temp_id;
	Main->SimpleSearch(temp_db);

	ui->text_id->setText(QString::fromStdString(temp_db.GetId()));
	ui->text_name->setText(QString::fromStdString(temp_db.GetName()));
	ui->text_singer->setText(QString::fromStdString(temp_db.GetPlayer()));
	string genre;
	if (temp_db.GetGenre() == 0)
		genre = "Unknown";
	if (temp_db.GetGenre() == 1)
		genre = "Pop";
	if (temp_db.GetGenre() == 2)
		genre = "Ballad";
	if (temp_db.GetGenre() == 3)
		genre = "Rock";
	if (temp_db.GetGenre() == 4)
		genre = "HipHop";
	if (temp_db.GetGenre() == 5)
		genre = "EDM";
	if (temp_db.GetGenre() == 7)
		genre = "Jazz";
	if (temp_db.GetGenre() == 10)
		genre = "Classic";
	if (temp_db.GetGenre() == 12)
		genre = "NewAge";
	ui->text_genre->setText(QString::fromStdString(genre));


	connect(ui->now_info, &QPushButton::clicked, this, &PlayListWidget::onClicked_nowInfo);

	connect(ui->now_next, &QPushButton::clicked, this, &PlayListWidget::onClicked_insert);
		
	//ui에 정보 띄우기
	temp_db.Play();
	Main->Play(temp_id, play_index, temp_db);



}
void PlayListWidget::onClicked_nowInfo()
{
	QWidget *w = qobject_cast<QWidget *>(sender()->parent());

	QString data = ui->text_id->text();
	ItemType temp;
	temp.SetId(data.toStdString());
	Main->SimpleSearch(temp);
	Info infowidget(temp);
	infowidget.exec();
}
void PlayListWidget::onClicked_insert()
{
	play_index++;
	if (play_index > Main->GetPlayListSize() && Main->CheckRepeatability() == true)
		play_index = 1;//마지막까지 돌았을 때 처음으로 돌아가는 부분.
	else if (play_index > Main->GetPlayListSize() && Main->CheckRepeatability() == false)
		return;
	PlayItem temp_play;
	string temp_id;

	ItemType temp_db;
	for (int i = 0; i < Main->GetPlayListSize(); i++)
		if (Main->at(i) == play_index)
			temp_play = Main->at(i);
	temp_play >> temp_id;
	temp_db = temp_id;
	Main->SimpleSearch(temp_db);

	ui->text_id->setText(QString::fromStdString(temp_db.GetId()));
	ui->text_name->setText(QString::fromStdString(temp_db.GetName()));
	ui->text_singer->setText(QString::fromStdString(temp_db.GetPlayer()));
	string genre;
	if (temp_db.GetGenre() == 0)
		genre = "Unknown";
	if (temp_db.GetGenre() == 1)
		genre = "Pop";
	if (temp_db.GetGenre() == 2)
		genre = "Ballad";
	if (temp_db.GetGenre() == 3)
		genre = "Rock";
	if (temp_db.GetGenre() == 4)
		genre = "HipHop";
	if (temp_db.GetGenre() == 5)
		genre = "EDM";
	if (temp_db.GetGenre() == 7)
		genre = "Jazz";
	if (temp_db.GetGenre() == 10)
		genre = "Classic";
	if (temp_db.GetGenre() == 12)
		genre = "NewAge";
	ui->text_genre->setText(QString::fromStdString(genre));

	//ui에 정보 띄우기
	temp_db.Play();
	Main->Play(temp_id, play_index, temp_db);
}
void PlayListWidget::on_push_pfrequency_clicked()
{
	ui->now_info->disconnect();
	ui->now_next->disconnect();
	int index = 0;
	if (!PriorityList->IsEmpty())
		while (!PriorityList->IsEmpty())
			PriorityList->Dequeue();
	CountType temp;
	string temp_id;
	for (int i = 0; i < Main->GetPlayListSize(); i++)
	{
		Main->at(i) >> now_play;
		Main->at(i) >> temp_id;
		temp = float(now_play);
		temp = temp_id;
		PriorityList->Add(temp);
		index = i;
	}
	ItemType temp_db;
	temp = PriorityList->Dequeue();
	temp >> temp_id;
	temp_db = temp_id;
	Main->SimpleSearch(temp_db);

	ui->text_id->setText(QString::fromStdString(temp_db.GetId()));
	ui->text_name->setText(QString::fromStdString(temp_db.GetName()));
	ui->text_singer->setText(QString::fromStdString(temp_db.GetPlayer()));
	string genre;
	if (temp_db.GetGenre() == 0)
		genre = "Unknown";
	if (temp_db.GetGenre() == 1)
		genre = "Pop";
	if (temp_db.GetGenre() == 2)
		genre = "Ballad";
	if (temp_db.GetGenre() == 3)
		genre = "Rock";
	if (temp_db.GetGenre() == 4)
		genre = "HipHop";
	if (temp_db.GetGenre() == 5)
		genre = "EDM";
	if (temp_db.GetGenre() == 7)
		genre = "Jazz";
	if (temp_db.GetGenre() == 10)
		genre = "Classic";
	if (temp_db.GetGenre() == 12)
		genre = "NewAge";
	ui->text_genre->setText(QString::fromStdString(genre));


	connect(ui->now_info, &QPushButton::clicked, this, &PlayListWidget::onClicked_nowInfo);

	connect(ui->now_next, &QPushButton::clicked, this, &PlayListWidget::onClicked_frequency);

	temp_db.Play();
	Main->Play(temp_id, index, temp_db);

	
}
void PlayListWidget::onClicked_frequency()
{
	int index = 0;
	if (PriorityList->IsEmpty() && Main->CheckRepeatability() == true)
	{
		CountType temp;
		string temp_id;
		for (int i = 0; i < Main->GetPlayListSize(); i++)
		{
			Main->at(i) >> now_play;
			Main->at(i) >> temp_id;
			temp = float(now_play);
			temp = temp_id;
			PriorityList->Add(temp);
			index = i;
		}
	}
	else if (PriorityList->IsEmpty() && Main->CheckRepeatability() == false)
		return;
	CountType temp;
	string temp_id;
	ItemType temp_db;
	temp = PriorityList->Dequeue();
	temp >> temp_id;
	temp_db = temp_id;
	Main->SimpleSearch(temp_db);

	ui->text_id->setText(QString::fromStdString(temp_db.GetId()));
	ui->text_name->setText(QString::fromStdString(temp_db.GetName()));
	ui->text_singer->setText(QString::fromStdString(temp_db.GetPlayer()));
	string genre;
	if (temp_db.GetGenre() == 0)
		genre = "Unknown";
	if (temp_db.GetGenre() == 1)
		genre = "Pop";
	if (temp_db.GetGenre() == 2)
		genre = "Ballad";
	if (temp_db.GetGenre() == 3)
		genre = "Rock";
	if (temp_db.GetGenre() == 4)
		genre = "HipHop";
	if (temp_db.GetGenre() == 5)
		genre = "EDM";
	if (temp_db.GetGenre() == 7)
		genre = "Jazz";
	if (temp_db.GetGenre() == 10)
		genre = "Classic";
	if (temp_db.GetGenre() == 12)
		genre = "NewAge";
	ui->text_genre->setText(QString::fromStdString(genre));



	temp_db.Play();
	Main->Play(temp_id, index, temp_db);

}
void PlayListWidget::on_push_random_clicked()
{
	ui->now_info->disconnect();
	ui->now_next->disconnect();
	if (Main->GetPlayCount() == Main->GetPlayListSize())
	{
		for (int i = 0; i < Main->GetPlayListSize(); i++)
			!Main->at(i);
		Main->SetPlayCount(0);
	}
	srand(time(NULL));
	PlayItem temp_play;
	string temp_id;
	int play_index = rand() % Main->GetPlayListSize();

	ItemType temp_db;
	int count = 0;
	while (Main->at(play_index) == true)
	{
		if (count == 50)
			break;
		play_index = rand() % Main->GetPlayListSize();
		if (play_index == pre_index)
			continue;
		count++;
	}

	if(count==50&&order==1)
		for (int i = 0; i < Main->GetPlayListSize(); i++)
		{
			if (Main->at(i) == false && i != pre_index)
			{
				play_index = i;
				count = 0;
				order = 2;
				break;
			}
		}
	else if(count == 50 && order == 2)
		for (int i = Main->GetPlayListSize() - 1; i >= 0; i--)
		{
			if (Main->at(i) == false && i != pre_index)
			{
				play_index = i;
				count = 0;
				order = 1;
				break;
			}
		}
	pre_index = play_index;
	temp_play = Main->at(play_index);
	temp_play >> temp_id;
	temp_db = temp_id;
	Main->SimpleSearch(temp_db);

	ui->text_id->setText(QString::fromStdString(temp_db.GetId()));
	ui->text_name->setText(QString::fromStdString(temp_db.GetName()));
	ui->text_singer->setText(QString::fromStdString(temp_db.GetPlayer()));
	string genre;
	if (temp_db.GetGenre() == 0)
		genre = "Unknown";
	if (temp_db.GetGenre() == 1)
		genre = "Pop";
	if (temp_db.GetGenre() == 2)
		genre = "Ballad";
	if (temp_db.GetGenre() == 3)
		genre = "Rock";
	if (temp_db.GetGenre() == 4)
		genre = "HipHop";
	if (temp_db.GetGenre() == 5)
		genre = "EDM";
	if (temp_db.GetGenre() == 7)
		genre = "Jazz";
	if (temp_db.GetGenre() == 10)
		genre = "Classic";
	if (temp_db.GetGenre() == 12)
		genre = "NewAge";
	ui->text_genre->setText(QString::fromStdString(genre));


	connect(ui->now_info, &QPushButton::clicked, this, &PlayListWidget::onClicked_nowInfo);

	connect(ui->now_next, &QPushButton::clicked, this, &PlayListWidget::onClicked_random);

	//ui에 정보 띄우기
	temp_db.Play();
	Main->Play(temp_id, play_index, temp_db);
	if (Main->GetPlayCount() == Main->GetPlayListSize())
	{
		if (Main->CheckRepeatability() == false)
			return;
		for (int i = 0; i < Main->GetPlayListSize(); i++)
			!Main->at(i);
		Main->SetPlayCount(0);
	}
}
void PlayListWidget::onClicked_random()
{
	if (Main->GetPlayCount() == Main->GetPlayListSize())
	{
		for (int i = 0; i < Main->GetPlayListSize(); i++)
			!Main->at(i);
		Main->SetPlayCount(0);
	}
	srand(time(NULL));
	PlayItem temp_play;
	string temp_id;
	int play_index = rand() % Main->GetPlayListSize();

	ItemType temp_db;
	int count = 0;
	while (Main->at(play_index) == true)
	{
		if (count == 50)
			break;
		play_index = rand() % Main->GetPlayListSize();
		count++;
	}
	if (count == 50 && order == 1)
		for (int i = 0; i < Main->GetPlayListSize(); i++)
		{
			if (Main->at(i) == false)
			{
				play_index = i;
				count = 0;
				order = 2;
				break;
			}
		}
	else if (count == 50 && order == 2)
		for (int i = Main->GetPlayListSize() - 1; i >= 0; i--)
		{
			if (Main->at(i) == false)
			{
				play_index = i;
				count = 0;
				order = 1;
				break;
			}
		}
	temp_play = Main->at(play_index);
	temp_play >> temp_id;
	temp_db = temp_id;
	Main->SimpleSearch(temp_db);

	ui->text_id->setText(QString::fromStdString(temp_db.GetId()));
	ui->text_name->setText(QString::fromStdString(temp_db.GetName()));
	ui->text_singer->setText(QString::fromStdString(temp_db.GetPlayer()));
	string genre;
	if (temp_db.GetGenre() == 0)
		genre = "Unknown";
	if (temp_db.GetGenre() == 1)
		genre = "Pop";
	if (temp_db.GetGenre() == 2)
		genre = "Ballad";
	if (temp_db.GetGenre() == 3)
		genre = "Rock";
	if (temp_db.GetGenre() == 4)
		genre = "HipHop";
	if (temp_db.GetGenre() == 5)
		genre = "EDM";
	if (temp_db.GetGenre() == 7)
		genre = "Jazz";
	if (temp_db.GetGenre() == 10)
		genre = "Classic";
	if (temp_db.GetGenre() == 12)
		genre = "NewAge";
	ui->text_genre->setText(QString::fromStdString(genre));


	temp_db.Play();
	Main->Play(temp_id, play_index, temp_db);
	if (Main->GetPlayCount() == Main->GetPlayListSize())
	{
		if (Main->CheckRepeatability() == false)
			return;
		for (int i = 0; i < Main->GetPlayListSize(); i++)
			!Main->at(i);
		Main->SetPlayCount(0);
	}
}
void PlayListWidget::on_push_repeat_clicked()
{
	int det = Main->ChangeRepeatability();
	if (det == true)
		ui->push_repeat->setText("On");
	else
		ui->push_repeat->setText("Off");
}


