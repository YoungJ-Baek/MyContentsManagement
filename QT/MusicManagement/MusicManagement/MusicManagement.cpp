#include "MusicManagement.h"
MusicManagement *Main;

MusicManagement::MusicManagement(int m_ListSize, QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MusicManagementClass)
{
	Main = this;
	ui->setupUi(this);

	m_List = new SortedList <ItemType>(m_ListSize);
	CountList = new SortedList<CountType>(m_ListSize);
	RecentList = new CircularQueueType<SongType>(m_ListSize);
	PriorityList = new CMaxHeap<CountType>(m_ListSize);

	checkboxMapper = new QSignalMapper(this);
	ui->MasterList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->MasterList->setRowCount(0);
	ui->MasterList->setColumnWidth(ID, 50);
	ui->MasterList->setColumnWidth(TITLE, 100);
	ui->MasterList->setColumnWidth(ARTIST, 100);
	ui->MasterList->setColumnWidth(GENRE, 70);
	ui->MasterList->setColumnWidth(ADD, 90);
	ui->MasterList->setColumnWidth(INFO, 90);

	ui->ResultList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->ResultList->setRowCount(0);
	ui->ResultList->setColumnWidth(ID, 50);
	ui->ResultList->setColumnWidth(TITLE, 100);
	ui->ResultList->setColumnWidth(ARTIST, 100);
	ui->ResultList->setColumnWidth(GENRE, 70);

	count = 0;
	play_count = 0;
	r_PlayList = false;
	index = -1;

	DisplayAll();
}

MusicManagement::~MusicManagement()
{
	delete ui;
}

void MusicManagement::DisplayAll()
{
	ui->MasterList->setRowCount(0);
	if (m_List->IsEmpty())
	{
		ui->MasterList->setRowCount(0);
		ui->MasterList->setItem(0, 0, new QTableWidgetItem("Empty"));
	}
	else
	{
		m_List->ResetList();
		ItemType temp;
		while (m_List->GetNextItem(temp) != -1)
		{
			//basic information
			ui->MasterList->insertRow(ui->MasterList->rowCount());
			int index = ui->MasterList->rowCount() - 1;

			string genre;
			QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp.GetId().c_str())));
			QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp.GetName()));
			QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp.GetPlayer()));
			if (temp.GetGenre() == 0)
				genre = "Unknown";
			if (temp.GetGenre() == 1)
				genre = "Pop";
			if (temp.GetGenre() == 2)
				genre = "Ballad";
			if (temp.GetGenre() == 3)
				genre = "Rock";
			if (temp.GetGenre() == 4)
				genre = "HipHop";
			if (temp.GetGenre() == 5)
				genre = "EDM";
			if (temp.GetGenre() == 7)
				genre = "Jazz";
			if (temp.GetGenre() == 10)
				genre = "Classic";
			if (temp.GetGenre() == 12)
				genre = "NewAge";
			QTableWidgetItem* pgenre = new QTableWidgetItem(QString::fromStdString(genre));
			id->setTextAlignment(Qt::AlignCenter);
			name->setTextAlignment(Qt::AlignCenter);
			player->setTextAlignment(Qt::AlignCenter);
			pgenre->setTextAlignment(Qt::AlignCenter);

			//info button
			pWidget_Info = new QWidget();
			btn_Info = new QPushButton();
			btn_Info->setText("More");
			connect(btn_Info, &QPushButton::clicked, this, &MusicManagement::onClicked_Info);
			QHBoxLayout* pLayout = new QHBoxLayout(pWidget_Info);
			pLayout->addWidget(btn_Info);
			pLayout->setAlignment(Qt::AlignCenter);
			pLayout->setContentsMargins(0, 0, 0, 0);
			pWidget_Info->setLayout(pLayout);

			//Playlist Add
			pWidget_add = new QWidget();
			btn_add = new QPushButton();
			btn_add->setText("+Add+");
			connect(btn_add, &QPushButton::clicked, this, &MusicManagement::onClicked_AddToPlaylist);
			QHBoxLayout* AddLayout = new QHBoxLayout(pWidget_add);
			AddLayout->addWidget(btn_add);
			AddLayout->setAlignment(Qt::AlignCenter);
			AddLayout->setContentsMargins(0, 0, 0, 0);
			pWidget_add->setLayout(AddLayout);

			ui->MasterList->setItem(index, ID, id);
			ui->MasterList->setItem(index, TITLE, name);
			ui->MasterList->setItem(index, ARTIST, player);
			ui->MasterList->setItem(index, GENRE, pgenre);
			ui->MasterList->setCellWidget(index, INFO, pWidget_Info);
			ui->MasterList->setCellWidget(index, ADD, pWidget_add);
		}
	}

}

bool MusicManagement::CheckPlayList()
{
	if (PlayList.IsEmpty())
	{
		return true;
	}
	else
		return false;
}
void MusicManagement::resetPlayList()
{
	index = -1;
}
int MusicManagement::GetNextPlayItem(PlayItem& temp)
{
	index++;
	if (index == count)
		return -1;
	else
	{
		temp = PlayList[index];
		return index;
	}
}
int MusicManagement::SimpleSearch(ItemType& temp)
{
	if (m_List->Retrieve_Binary(temp) != -1)
		return 1;
	else
		return 0;
}
PlayItem& MusicManagement::at(int index)
{
	return PlayList[index];
}
int MusicManagement::PLOpenInFile(char *fileName)
{
	char dir[FILENAMESIZE + 12] = "./PlayList/";
	strcat_s(dir, fileName);
	p_InFile.open(dir);	// file open for reading.
	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (p_InFile)
		return 1;
	else
		return 0;
}
int MusicManagement::PLOpenOutFile(char* fileName)
{
	char dir[FILENAMESIZE + 12] = "./PlayList/";
	strcat_s(dir, fileName);
	p_OutFile.open(dir);// file open for writing.
	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (p_OutFile)
		return 1;
	else
		return 0;
}
int MusicManagement::PLReadDataFromFile(char* fileName)
{
	int index = 0;
	PlayItem data;	// 읽기용 임시 변수
	string temp_ID;

	// file open, open error가 발생하면 0을 리턴
	if (!PLOpenInFile(fileName))
	{
		return 0;
	}

	// 파일의 모든 내용을 읽어 list에 추가
	while (!p_InFile.eof())
	{
		ItemType temp;	// Master List 있는지 여부 확인용 변수
		// array에 학생들의 정보가 들어있는 structure 저장
		int input = data.ReadDataFromFile(p_InFile);
		if (input == 0)
			break;
		data >> temp_ID;
		temp = temp_ID;
		if (m_List->Retrieve_Binary(temp) != -1)
		{
			if (PlayList.Add(data) != 0)
			{
				count++;//저장된 개수 증가.
				data = count;
				PlayList.Replace(data);
			}
			else
			{
				cout << "\n\tYou already have song in your Play List.\n";
				return 0;
			}
		}
		else {
			cout << "\n\tThere's no song with your ID.\n";
			return 0;
		}

	}

	p_InFile.close();	// file close

	return 1;
}
int MusicManagement::PLWriteDataToFile(char* fileName)
{
	

	// file open, open error가 발생하면 0을 리턴
	if (!PLOpenOutFile(fileName))
	{
		cout << "\n\tWrong Format" << endl << endl;
		return 0;
	}

	//list의 모든 데이터를 파일에 쓰기
	for (int i = 0; i < count; i++)
		PlayList[i].WriteDataToFile(p_OutFile);
	cout << endl << "\tUploading Complete" << endl;
	p_OutFile.close();
	return 1;
}
int MusicManagement::AddSongToPL(string& temp_id)
{
	ItemType temp;
	PlayItem temp_insert;
	temp.SetId(temp_id);
	temp_insert = temp_id;
	if (m_List->Retrieve_Binary(temp) != -1)
	{
		if (PlayList.Add(temp_insert) != 0)
		{
			count++;
			temp_insert = count;
			PlayList.Replace(temp_insert);
			return 1;
		}
		else
		{
			QMessageBox::information(this, "Error!", "Same ID exists!");
			return 0;
		}
	}
	else
	{
		QMessageBox::information(this, "Error!", "No Song!");
		return 0;
	}
}
int MusicManagement::DeleteSongFrPL(string& temp_id)
{
	PlayItem temp;
	temp.SetId(temp_id);
	if (PlayList.Delete(temp) == 1)
	{
		count--;
		return 1;
	}
	else
		return 0;
}
bool MusicManagement::ChangeRepeatability()
{
	if (r_PlayList == true)
		r_PlayList = false;
	else
		r_PlayList = true;
	return r_PlayList;
}
void MusicManagement::Play(string temp_id, int play_index, ItemType& temp_db)
{
	CountType temp_count;
	SongType temp_song;
	float temp_nplay;
	temp_count = temp_id;
	temp_db >> temp_nplay;
	temp_count = temp_nplay;
	CountList->Replace(temp_count);
	if (PlayList[play_index] == false) {
		!PlayList[play_index];//재생 상태 변화.
		play_count++;
	}
	temp_song = temp_db;
	if (RecentList->Delete(temp_song) == 1)
		RecentList->EnQueue(temp_song);
	else
	{
		if (RecentList->IsFull())
		{
			SongType temp;
			RecentList->DeQueue(temp);
			RecentList->EnQueue(temp_song);
		}
		else
			RecentList->EnQueue(temp_song);
	}
	++temp_db;
	m_List->Replace(temp_db);
	++(PlayList[play_index]);//재생 횟수 증가
}

int MusicManagement::OpenInFile(char *fileName)
{
	char dir[FILENAMESIZE + 14] = "./MasterList/";
	strcat_s(dir, fileName);
	m_InFile.open(dir);	// file open for reading.
	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (m_InFile)
		return 1;
	else
		return 0;
}
int MusicManagement::OpenOutFile(char *fileName)
{
	char dir[FILENAMESIZE + 14] = "./MasterList/";
	strcat_s(dir, fileName);
	m_OutFile.open(dir);// file open for writing.
	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (m_OutFile)
		return 1;
	else
		return 0;
}

void MusicManagement::on_edit_fstream_textChanged(const QString &arg1)
{
	fstream_keyword = arg1.toStdString();
}
int MusicManagement::on_push_open_clicked()
{
	int index = 0;
	//ItemType data;	// 읽기용 임시 변수

	char *filename = new char[fstream_keyword.size() + 1];
	copy(fstream_keyword.begin(), fstream_keyword.end(), filename);
	filename[fstream_keyword.size()] = '\0';

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename))
	{
		QMessageBox::information(this, "Error!", "No file with your input.");
		return 0;
	}

	// 파일의 모든 내용을 읽어 list에 추가
	while (!m_InFile.eof())
	{
		ItemType data;	// 읽기용 임시 변수
		// array에 학생들의 정보가 들어있는 structure 저장
		int input = data.ReadDataFromFile(m_InFile);
		if (input == 0)
			break;
		bool addition = m_List->Add(data);
		if (addition)
		{
			CountType temp;
			int temp_ID;
			float temp_nplay;
			Addsong(data);
			data >> temp_ID;
			data >> temp_nplay;
			temp = to_string(temp_ID);
			temp = temp_nplay;
			CountList->Add(temp);
		}
	}

	m_InFile.close();	// file close
	delete filename;

	DisplayAll();

	return 1;
}
int MusicManagement::on_push_save_clicked()
{
	ItemType temp;// 쓰기용 임시 변수
	char *filename = new char[fstream_keyword.size() + 1];
	copy(fstream_keyword.begin(), fstream_keyword.end(), filename);
	filename[fstream_keyword.size()] = '\0';

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename))
	{
		cout << "\n\tWrong Format" << endl << endl;
		return 0;
	}

	// list 포인터를 초기화
	m_List->ResetList();

	//list의 모든 데이터를 파일에 쓰기
	while (m_List->GetNextItem(temp) != -1)
	{
		temp.WriteDataToFile(m_OutFile);
	}
	cout << endl << "\tUploading Complete" << endl;
	m_OutFile.close();
	return 1;
}

int MusicManagement::AddMusic(ItemType add)
{
	if (m_List->IsFull())
	{
		QMessageBox::information(this, "Error!", "The List is Full!");
		return 0;
	}
	CountType temp;
	bool addition = m_List->Add(add);
	if (addition)
	{
		int temp_ID;
		Addsong(add);
		add >> temp_ID;
		temp = to_string(temp_ID);
		CountList->Add(temp);
		return 1;
	}
	else
	{
		QMessageBox::information(this, "Error!", "Same Id Already Exists");
		return 0;
	}
}

void MusicManagement::Addsong(ItemType data)
{
	bool check_genre = false;
	bool check_singer = false;
	bool check_tag = false;
	SingerType singer;
	GenreType genre;
	TagType tag;
	string temp_Player;
	unsigned int temp_Genre;
	data >> temp_Player;
	data >> temp_Genre;
	singer = temp_Player;
	genre = temp_Genre;
	if (GList.Get(genre)) {
		genre.Add(data);
		check_genre = true;
	}
	else {
		GList.Add(genre);
		genre.Add(data);
		check_genre = true;
	}
	SList.RetrieveItem(singer, check_singer);
	//가수가 이미 있는 경우
	if (check_singer == true)
		singer.Add(data);
	//가수가 없는 경우
	else {
		singer.SetRecordFromKB();
		SList.Add(singer);
		//AddSong(data);
		singer.Add(data);
		check_singer = true;
	}
	string temp_tag;
	data.ResetTagList();
	while (data.GetNextTag(temp_tag) != -1)
	{
		tag = temp_tag;
		//TList.RetrieveItem(tag, check_tag);
		if (TList.Get(tag)) {
			//if (check_tag == true)
			tag.Add(data);
			check_tag = true;
		}
		else
		{
			TList.Add(tag);
			tag.Add(data);
			check_tag = true;
		}
	}
}

void MusicManagement::onClicked_Info()
{
	QWidget *w = qobject_cast<QWidget *>(sender()->parent());

	int row = ui->MasterList->indexAt(w->pos()).row();
	ItemType temp = m_List->at(row);
	Info Infowidget(temp);
	Infowidget.exec();
}

void MusicManagement::onClicked_AddToPlaylist()
{
	QWidget *w = qobject_cast<QWidget *>(sender()->parent());

	int row = ui->MasterList->indexAt(w->pos()).row();
	PlayItem add_item;
	add_item.SetId(m_List->at(row).GetId());
	int det = PlayList.Add(add_item);
	if (det != 0)
	{
		count++;
		add_item = count;
		PlayList.Replace(add_item);
	}
	if (det == 1)
		QMessageBox::information(this, "Add_to_PlayList", "Add Complete!");
	else
		QMessageBox::information(this, "Error", "Add Fail:Already Exists");
}


void MusicManagement::on_push_exit_clicked()
{
	close();
}

void MusicManagement::on_push_add_clicked()
{
	AddSong addwidget;
	addwidget.setModal(true);
	addwidget.exec();

	DisplayAll();
}


void MusicManagement::on_edit_delete_textChanged(const QString &arg1)
{
	delete_ID = arg1.toStdString();
}

void MusicManagement::DeleteMusic()
{
	bool check_singer = false;
	bool check_tag = false;
	ItemType temp;//검색용 임시 변수
	temp.SetId(delete_ID);
	m_List->Retrieve_Binary(temp);
	if (m_List->Delete(temp))
	{
		check_singer = true;
		CountType temp1;
		GenreType genre;
		SingerType singer;
		TagType tag;
		string temp_player;
		unsigned int temp_Genre;
		int temp_count;
		temp >> temp_count;
		temp >> temp_player;
		temp >> temp_Genre;
		temp1 = to_string(temp_count);
		singer = temp_player;
		genre = temp_Genre;
		CountList->Delete(temp1);
		SList.RetrieveItem(singer, check_singer);
		singer.Delete(temp);
		GList.Get(genre);
		genre.Delete(temp);
		int index = 0;
		string temp_tag;
		while (temp.GetIndexTag(index, temp_tag) != 0)
		{
			tag = temp_tag;
			TList.Get(tag);
			tag.Delete(temp);
		}
	}
}

void MusicManagement::on_push_delete_clicked()
{
	DeleteMusic();
	DisplayAll();
}

void MusicManagement::on_push_modify_clicked()
{
	DeleteMusic();
	Modify modifywidget(delete_ID);
	modifywidget.setModal(true);
	modifywidget.exec();

	DisplayAll();
}

void MusicManagement::on_push_make_empty_clicked()
{
	m_List->MakeEmpty();
	DisplayAll();
}

void MusicManagement::on_push_playlist_clicked()
{
	PlayListWidget playlistwidget;
	playlistwidget.exec();
}
void MusicManagement::on_push_recent_clicked()
{
	ui->ResultList->setRowCount(0);
	if (RecentList->IsEmpty())
	{
		ui->ResultList->setRowCount(0);
		ui->ResultList->setItem(0, 0, new QTableWidgetItem("No Result"));
	}
		
	////////////////////////////////////////////////////////
	SongType temp;
	RecentList->ReadyForRecent();
	while (RecentList->GetRecentItem(temp) != -1)
	{
		ItemType temp_db;
		string temp_id = temp.GetID();
		temp_db = temp_id;
		m_List->Retrieve_Binary(temp_db);

		ui->ResultList->insertRow(ui->ResultList->rowCount());
		int index = ui->ResultList->rowCount() - 1;

		QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp_db.GetId().c_str())));
		QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp_db.GetName()));
		QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp_db.GetPlayer()));
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
		QTableWidgetItem* pgenre = new QTableWidgetItem(QString::fromStdString(genre));

		id->setTextAlignment(Qt::AlignCenter);
		name->setTextAlignment(Qt::AlignCenter);
		player->setTextAlignment(Qt::AlignCenter);
		pgenre->setTextAlignment(Qt::AlignCenter);

		ui->ResultList->setItem(index, ID, id);
		ui->ResultList->setItem(index, TITLE, name);
		ui->ResultList->setItem(index, ARTIST, player);
		ui->ResultList->setItem(index, GENRE, pgenre);

	}

}
void MusicManagement::on_push_priority_clicked()
{
	ui->ResultList->setRowCount(0);
	CountType temp;
	CountList->ResetList();
	while (CountList->GetNextItem(temp) != -1)
	{
		PriorityList->Add(temp);
	}
	if (PriorityList->IsEmpty())
	{
		ui->ResultList->setRowCount(0);
		ui->ResultList->setItem(0, 0, new QTableWidgetItem("No Result"));
	}
	else
	{
		while (PriorityList->IsEmpty() != true)
		{
			ItemType temp_db;
			string temp_id;
			temp = PriorityList->Dequeue();
			temp >> temp_id;
			temp_db = temp_id;
			m_List->Retrieve_Binary(temp_db);

			ui->ResultList->insertRow(ui->ResultList->rowCount());
			int index = ui->ResultList->rowCount() - 1;

			QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp_db.GetId().c_str())));
			QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp_db.GetName()));
			QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp_db.GetPlayer()));
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
			QTableWidgetItem* pgenre = new QTableWidgetItem(QString::fromStdString(genre));

			id->setTextAlignment(Qt::AlignCenter);
			name->setTextAlignment(Qt::AlignCenter);
			player->setTextAlignment(Qt::AlignCenter);
			pgenre->setTextAlignment(Qt::AlignCenter);

			ui->ResultList->setItem(index, ID, id);
			ui->ResultList->setItem(index, TITLE, name);
			ui->ResultList->setItem(index, ARTIST, player);
			ui->ResultList->setItem(index, GENRE, pgenre);

		}
	}
	
}
void MusicManagement::on_push_recommend_clicked()
{
	ui->ResultList->setRowCount(0);
	CountType temp;
	CountList->ResetList();
	while (CountList->GetNextItem(temp) != -1)
	{
		PriorityList->Add(temp);
	}
	if (PriorityList->IsEmpty())
	{
		ui->ResultList->setRowCount(0);
		ui->ResultList->setItem(0, 0, new QTableWidgetItem("No Result"));
	}
	else
	{
		ItemType temp_db;
		GenreType genre;
		string temp_id;
		unsigned int temp_genre;
		temp = PriorityList->Dequeue();
		temp >> temp_id;
		temp_db = temp_id;
		m_List->Retrieve_Binary(temp_db);
		temp_db >> temp_genre;
		genre = temp_genre;
		if (GList.Get(genre))
		{
			int id;
			genre.ResetList();
			genre >> id;
			temp_db = to_string(id);
			while (id != 0)
			{
				if (id != atoi(temp_id.c_str()))
				{
					m_List->Retrieve_Binary(temp_db);
					ui->ResultList->insertRow(ui->ResultList->rowCount());
					int index = ui->ResultList->rowCount() - 1;

					QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp_db.GetId().c_str())));
					QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp_db.GetName()));
					QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp_db.GetPlayer()));
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
					QTableWidgetItem* pgenre = new QTableWidgetItem(QString::fromStdString(genre));
					id->setTextAlignment(Qt::AlignCenter);
					name->setTextAlignment(Qt::AlignCenter);
					player->setTextAlignment(Qt::AlignCenter);
					pgenre->setTextAlignment(Qt::AlignCenter);

					ui->ResultList->setItem(index, ID, id);
					ui->ResultList->setItem(index, TITLE, name);
					ui->ResultList->setItem(index, ARTIST, player);
					ui->ResultList->setItem(index, GENRE, pgenre);
				}
				genre >> id;
				temp_db = to_string(id);
				temp_db.SetName("");
			}
		}
		while (PriorityList->IsEmpty() != true)
			PriorityList->Dequeue();
		

	}
}

void MusicManagement::on_search_type_activated(const QString &arg1)
{
	search_type = arg1.toStdString();
}

void MusicManagement::on_push_search_clicked()
{
	if (search_type == "ID")
		SearchByID();
	else if (search_type == "Name")
		SearchByName();
	else if (search_type == "Singer")
		SearchBySinger();
	else if (search_type == "Genre")
		SearchByGenre();
	else if (search_type == "Tag")
		SearchByTag();
	else if (search_type == "Lyrics")
		SearchByLyrics();

}

void MusicManagement::on_edit_search_textChanged(const QString &arg1)
{
	search_keyword = arg1.toStdString();
}

void MusicManagement::SearchByID()
{
	ui->ResultList->setRowCount(0);
	ItemType temp;//검색용 임시 변수
	temp.SetId(search_keyword);

	//search success
	if (m_List->Retrieve_Binary(temp) != -1)
	{
		ui->ResultList->insertRow(ui->ResultList->rowCount());
		int index = ui->ResultList->rowCount() - 1;

		QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp.GetId().c_str())));
		QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp.GetName()));
		QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp.GetPlayer()));
		QTableWidgetItem* genre = new QTableWidgetItem(QString::number(temp.GetGenre()));

		id->setTextAlignment(Qt::AlignCenter);
		name->setTextAlignment(Qt::AlignCenter);
		player->setTextAlignment(Qt::AlignCenter);

		ui->ResultList->setItem(index, ID, id);
		ui->ResultList->setItem(index, TITLE, name);
		ui->ResultList->setItem(index, ARTIST, player);
		ui->ResultList->setItem(index, GENRE, genre);
	}
	else
	{
		QMessageBox::information(this, "Error!", "No Result!");
	}
}

void MusicManagement::SearchByName()
{
	ui->ResultList->setRowCount(0);
	m_List->ResetList();
	ItemType temp;//검색용 임시 변수
	string input;
	bool check = false;

	while (m_List->GetNextItem(temp) != -1) {
		//check if there's input word in data.
		if (temp != search_keyword) {
			ui->ResultList->insertRow(ui->ResultList->rowCount());
			int index = ui->ResultList->rowCount() - 1;

			QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp.GetId().c_str())));
			QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp.GetName()));
			QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp.GetPlayer()));
			QTableWidgetItem* genre = new QTableWidgetItem(QString::number(temp.GetGenre()));

			id->setTextAlignment(Qt::AlignCenter);
			name->setTextAlignment(Qt::AlignCenter);
			player->setTextAlignment(Qt::AlignCenter);

			ui->ResultList->setItem(index, ID, id);
			ui->ResultList->setItem(index, TITLE, name);
			ui->ResultList->setItem(index, ARTIST, player);
			ui->ResultList->setItem(index, GENRE, genre);
			check = true;
		}
	}
	//search fails.
	if (check == false) {
		QMessageBox::information(this, "Error!", "No Result!");
	}
}
void MusicManagement::SearchBySinger()
{
	ui->ResultList->setRowCount(0);
	SingerType temp_singer;//검색용 변수
	bool check_singer = false;
	temp_singer.SetName(search_keyword);
	SList.RetrieveItem(temp_singer, check_singer);
	if (check_singer == true) {
		ItemType temp;//검색용 변수
		int temp_ID;
		temp_singer.ResetList();
		temp_singer >> temp_ID;
		temp = to_string(temp_ID);
		while (temp_ID != 0)
		{

			m_List->Retrieve_Binary(temp);
			ui->ResultList->insertRow(ui->ResultList->rowCount());
			int index = ui->ResultList->rowCount() - 1;

			QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp.GetId().c_str())));
			QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp.GetName()));
			QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp.GetPlayer()));
			QTableWidgetItem* genre = new QTableWidgetItem(QString::number(temp.GetGenre()));

			id->setTextAlignment(Qt::AlignCenter);
			name->setTextAlignment(Qt::AlignCenter);
			player->setTextAlignment(Qt::AlignCenter);

			ui->ResultList->setItem(index, ID, id);
			ui->ResultList->setItem(index, TITLE, name);
			ui->ResultList->setItem(index, ARTIST, player);
			ui->ResultList->setItem(index, GENRE, genre);
			temp_singer >> temp_ID;
			temp = to_string(temp_ID);
			temp.SetName("");
		}
	}
	else 
		ui->ResultList->setItem(0, 0, new QTableWidgetItem("No Result"));
}
void MusicManagement::SearchByGenre()
{
	ui->ResultList->setRowCount(0);
	GenreType temp_genre;//검색용 변수
	temp_genre.SetNum(atoi(search_keyword.c_str()));
	if (GList.Get(temp_genre)) {
		ItemType temp;//검색용 변수
		int temp_ID;
		temp_genre.ResetList();
		temp_genre >> temp_ID;
		temp = to_string(temp_ID);
		while (temp_ID != 0)
		{
			m_List->Retrieve_Binary(temp);
			ui->ResultList->insertRow(ui->ResultList->rowCount());
			int index = ui->ResultList->rowCount() - 1;

			QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp.GetId().c_str())));
			QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp.GetName()));
			QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp.GetPlayer()));
			QTableWidgetItem* genre = new QTableWidgetItem(QString::number(temp.GetGenre()));

			id->setTextAlignment(Qt::AlignCenter);
			name->setTextAlignment(Qt::AlignCenter);
			player->setTextAlignment(Qt::AlignCenter);

			ui->ResultList->setItem(index, ID, id);
			ui->ResultList->setItem(index, TITLE, name);
			ui->ResultList->setItem(index, ARTIST, player);
			ui->ResultList->setItem(index, GENRE, genre);
			temp_genre >> temp_ID;
			temp = to_string(temp_ID);
			temp.SetName("");
		}
	}
	else 
		ui->ResultList->setItem(0, 0, new QTableWidgetItem("No Result"));
}
void MusicManagement::SearchByTag()
{
	ui->ResultList->setRowCount(0);
	TagType tag;
	tag.SetTag(search_keyword);
	if (TList.Get(tag))
	{
		
		ItemType temp;//검색용 변수
		int temp_ID;
		tag.ResetList();
		tag >> temp_ID;
		temp = to_string(temp_ID);
		while (temp_ID != 0)
		{
			m_List->Retrieve_Binary(temp);
			ui->ResultList->insertRow(ui->ResultList->rowCount());
			int index = ui->ResultList->rowCount() - 1;

			QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp.GetId().c_str())));
			QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp.GetName()));
			QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp.GetPlayer()));
			QTableWidgetItem* genre = new QTableWidgetItem(QString::number(temp.GetGenre()));

			id->setTextAlignment(Qt::AlignCenter);
			name->setTextAlignment(Qt::AlignCenter);
			player->setTextAlignment(Qt::AlignCenter);

			ui->ResultList->setItem(index, ID, id);
			ui->ResultList->setItem(index, TITLE, name);
			ui->ResultList->setItem(index, ARTIST, player);
			ui->ResultList->setItem(index, GENRE, genre);
			tag >> temp_ID;
			temp = to_string(temp_ID);
			temp.SetName("");
		}
		
	}
	else
		ui->ResultList->setItem(0, 0, new QTableWidgetItem("No Result"));
}
void MusicManagement::SearchByLyrics()
{
	ui->ResultList->setRowCount(0);
	m_List->ResetList();
	ItemType temp;//검색용 임시 변수
	string inLyrics = search_keyword;
	bool check = false;

	while (m_List->GetNextItem(temp) != -1) {
		//check if there's input word in data.
		if (temp == inLyrics) {
			ui->ResultList->insertRow(ui->ResultList->rowCount());
			int index = ui->ResultList->rowCount() - 1;

			QTableWidgetItem* id = new QTableWidgetItem(QString::number(atoi(temp.GetId().c_str())));
			QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(temp.GetName()));
			QTableWidgetItem* player = new QTableWidgetItem(QString::fromStdString(temp.GetPlayer()));
			QTableWidgetItem* genre = new QTableWidgetItem(QString::number(temp.GetGenre()));

			id->setTextAlignment(Qt::AlignCenter);
			name->setTextAlignment(Qt::AlignCenter);
			player->setTextAlignment(Qt::AlignCenter);

			ui->ResultList->setItem(index, ID, id);
			ui->ResultList->setItem(index, TITLE, name);
			ui->ResultList->setItem(index, ARTIST, player);
			ui->ResultList->setItem(index, GENRE, genre);
			check = true;
		}
	}
	//search fails.
	if (check == false) 
		ui->ResultList->setItem(0, 0, new QTableWidgetItem("No Result"));
}