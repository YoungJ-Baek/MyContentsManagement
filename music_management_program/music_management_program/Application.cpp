#include "Application.h"
#include <ctime>
#include <Windows.h>
#include <direct.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

//Constructor.
Application::Application()
{
	m_Command = 0;
	checkMasterList = false;
	count = 0;
	play_count = 0;
	r_PlayList = false;
}

//Destructor.
Application::~Application() {}

void Application::MakeUserData()
{
	ofstream user;
	string ID;
	string PW;
	user.open("user.txt");
	cout << "\t-----Resisger-----\n";
	cout << "\tID\t: ";
	cin >> ID;
	cout << "\tPW\t: ";
	cin >> PW;
	user << ID << endl;
	user << PW << endl;
	DWORD attributes = GetFileAttributes("user.txt");
	SetFileAttributes("user.txt", attributes + FILE_ATTRIBUTE_HIDDEN);
	user.close();
}

void Application::LogIn(ifstream& user)
{
	string ID;
	string PW;
	string input_ID;
	string input_PW;
	user >> ID;
	user >> PW;
	cout << "\t-----Log In-----\n";
	cout << "\tID\t: ";
	cin >> input_ID;
	cout << "\tPW\t: ";
	cin >> input_PW;
	if (ID == input_ID && PW == input_PW)
		cout << "\tLog In Complete\n";
	else
		exit(100);
}

//Program driver.
void Application::Run()
{
	_mkdir("./DB/");
	_mkdir("./MasterList/");
	_mkdir("./PlayList/");
	ifstream user;
	user.open("user.txt");
	if (user.is_open() == false)
		MakeUserData();
	else
		LogIn(user);
	user.close();
	while (1) {
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:
			Run_MasterList();
			break;
		case 2:
			Run_PlayList();
			break;
		case 0:
			exit(0);
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

//Display program command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\tMain Menu" << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Master List" << endl;
	cout << "\t   2 : Play List" << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\tChoose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

//MasterList driver.
void Application::Run_MasterList()
{
	if (checkMasterList == false) {
		AllocateMasterList();	// 디폴트 값이나 사용자 입력으로 리스트 동적 할당
		checkMasterList = true;
	}
	while (1) {
		m_Command = GetCommandMasterList();

		switch (m_Command)
		{
		case 1:		// 곡 정보를 입력 받아 리스트에 추가					
			AddMusic();
			break;
		case 2:		// 곡의 고유번호를 입력 받아 리스트에서 삭제					
			DeleteMusic();
			break;
		case 3:		// 곡 정보를 입력 받아서 리스트에서 해당 곡 정보를 갱신			
			ReplaceMusic();
			break;
		case 4:		// 입력된 정보로 리스트에서 곡을 찾아서 화면에 출력		
			Search();
			break;
		case 5:		// 리스트에 저장된 모든 곡을 화면에 출력
			Display();
			break;
		case 6: 	// 리스트에 입력된 모든 곡을 삭제
			MakeEmpty();
			break;
		case 7:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 8:		// save list data into a file.
			WriteDataToFile();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;

		}
	}
}

//Display Master List command on screen and get a input from keyboard.
int Application::GetCommandMasterList()
{
	int command;
	cout << endl << endl;
	cout << "\tMaster List" << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add Music" << endl;
	cout << "\t   2 : Delete Music" << endl;
	cout << "\t   3 : Replace Music" << endl;
	cout << "\t   4 : Search Music" << endl;
	cout << "\t   5 : Display " << endl;
	cout << "\t   6 : Make Empty" << endl;
	cout << "\t   7 : Get from file " << endl;
	cout << "\t   8 : Put to file " << endl;
	cout << "\t   0 : Back to Main Menu" << endl;

	cout << endl << "\tChoose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

//Dynamic Allocation of Master List.
void Application::AllocateMasterList()
{
	int input;
	cout << "\n\t1. Default\t2.Custom\n";
	cout << "\tInput: ";
	cin >> input;
	switch (input) {
	case 1:
		m_List = new SortedList<ItemType>();
		CountList = new SortedList<CountType>();
		RecentList = new CircularQueueType<SongType>();
		PriorityList = new CMaxHeap<CountType>(10);
		break;
	case 2:
		cout << "\n\tSize: ";
		cin >> input;
		m_List = new SortedList <ItemType>(input);
		CountList = new SortedList<CountType>(input);
		RecentList = new CircularQueueType<SongType>(input);
		PriorityList = new CMaxHeap<CountType>(input);
		break;
	default:
		cout << "\n\tIllegal selection...\n";
		cout << "\tDefault Setting...\n";
		m_List = new SortedList<ItemType>();
		CountList = new SortedList<CountType>();
		RecentList = new CircularQueueType<SongType>();
		PriorityList = new CMaxHeap<CountType>(10);
		break;
	}
}

//PlayList driver.
void Application::Run_PlayList()
{
	if (checkMasterList == false) {
		cout << "\n\tYou should make your Master List first...\n";
		Run();
	}
	while (1) {
		m_Command = GetCommandPlayList();

		switch (m_Command)
		{
		case 1:
			AddSongToPL();
			break;
		case 2:
			DisplayPlayList();
			break;
		case 3:
			DeleteSongFrPL();
			break;
		case 4:
			Play();
			break;
		case 5:
			PLReadDataFromFile();
			break;
		case 6:
			PLWriteDataToFile();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

//Display Play List command on screen and get a input from keyboard.
int Application::GetCommandPlayList()
{
	int command;
	cout << endl << endl;
	cout << "\tPlay List" << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add Music" << endl;
	cout << "\t   2 : Display All Music" << endl;
	cout << "\t   3 : Delete Music" << endl;
	cout << "\t   4 : Play" << endl;
	cout << "\t   5 : Get from file" << endl;
	cout << "\t   6 : Put to file" << endl;
	cout << "\t   0 : Back to Main Menu" << endl;

	cout << endl << "\tChoose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


//Master List Command.
//Add new record into list.
int Application::AddMusic()
{
	//check if list is full, if true, print warning message.
	//추가를 하지 않을 경우 가이드라인을 띄우지 않아도 된다고 생각해 꽉 찼을 경우 경고 문구를 띄우는 것을 이 위치에 삽입하였습니다.
	if (m_List->IsFull())
	{
		cout << "\tthe list is full" << endl;
		return 0;
	}
	int check = 0;//id 직접 입력 기능 추가 -> 자신의 리스트를 만들 때 사용하면 편할 것으로 예상
	while (check != 1 && check != 2) {
		cout << "\n\tAdd New Song\n\n\t\t\t1.Enter the ID\t\t2.Make own ID\n\n\tInput: ";
		cin >> check;
	}
	ItemType add;
	CountType temp;
	//Guideline for user about entering type, genre.
	cout << "\n\tGuide " << endl << endl;
	cout << "\tType\n\t\t1.Pop Music\t2.Instrumental Music" << endl;
	cout << "\tGenre" << endl;
	cout << "\t\tPop Music:\t\t0.Dance / Pop\t1.Ballad\t2.Rock / Metal\t3.Hiphop / Rap\t4.EDM\t5.Jazz\t6.Country\t7.Fork / Aquastic\t8.Idol\t9.R&B / Soul" << endl;
	cout << "\t\tInstrumental Music:\t10.Classic\t11.OST\t12.New Age\t13.World Music\t14.Traditional Music\t15.CCM" << endl << endl;
	add.SetRecordFromKB();
	if (check == 1)
		add.SetIdFromKB();
	add.SetFileTypeFromKB();
	add.SetFileNameFromKB();
	bool addition = m_List->Add(add);
	//Add Song in Slist.
	if (addition)
	{
		int temp_ID;
		AddSong(add);
		add >> temp_ID;
		temp = to_string(temp_ID);
		CountList->Add(temp);

		cout << endl;
		DisplayAllMusic();
		return 1;
	}
	//display all music after addition.
	else
		return 0;
}


//Delete record from list.
int Application::DeleteMusic()
{
	bool check_singer = false;
	bool check_tag = false;
	ItemType temp;//검색용 임시 변수
	temp.SetIdFromKB();
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
	return 1;
}

//Replace record in list.
int Application::ReplaceMusic()
{
	ItemType temp;//검색용 임시 변수
	temp.SetIdFromKB();
	cout << "\n\tEnter the information " << endl;
	temp.SetRecordFromKB();//set record for replacement
	m_List->Replace(temp);
	return 1;
}

//Open display tool.
void Application::Display()
{
	int input;
	cout << "\t1.Display All Music\n\t2.Display Recent Music\n\t3.Display Priority Music List\n\t4.Display Recommend Songs for you in MasterList\n\n" << "\tInput: ";
	cin >> input;
	switch (input) {
	case 1:
		DisplayAllMusic();
		break;
	case 2:
		DisplayRecentMusic();
		break;
	case 3:
		DisplayPriorityMusic();
		break;
	case 4:
		RecommendSong();
		break;
	default:
		cout << "\tWrong Input!" << endl;
		Display();
	}
}

//Display all records in the list on screen
void Application::DisplayAllMusic()
{
	ItemType temp;
	cout << "\n\tCurrent List" << endl << endl;
	m_List->ResetList();
	int master_count = 1;
	while (m_List->GetNextItem(temp) != -1)
	{
		cout << "\n\t#" << master_count << ".\n";
		temp.DisplayRecordOnScreen();
		master_count++;
	}
}

//Display recent records in the list on screen
void Application::DisplayRecentMusic()
{
	if (RecentList->IsEmpty())
		return;
	RecentList->Print();
}

//Display records in the list of priority.
void Application::DisplayPriorityMusic()
{
	CountType temp;
	CountList->ResetList();
	while (CountList->GetNextItem(temp) != -1)
	{
		PriorityList->Add(temp);
	}
	int index = 1;
	while (PriorityList->IsEmpty() != true)
	{
		ItemType temp_db;
		string temp_id;
		temp = PriorityList->Dequeue();
		temp >> temp_id;
		temp_db = temp_id;
		m_List->Retrieve_Binary(temp_db);
		cout << "\t#1" << endl;
		temp_db.DisplayRecordOnScreen();
		index++;
	}
}

//Make list empty.
void Application::MakeEmpty()
{
	m_List->MakeEmpty();
	cout << "\n\tThe List is empty.\n";
}

//Recommend Songs.
void Application::RecommendSong()
{
	CountType temp;
	CountList->ResetList();
	while (CountList->GetNextItem(temp) != -1)
	{
		PriorityList->Add(temp);
	}
	if (PriorityList->IsEmpty() != true)
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
			cout << endl;
			cout << "\n\tSong List...\n" << endl;
			genre.ResetList();
			genre >> id;
			temp_db = to_string(id);
			while (id != 0)
			{
				if (id != atoi(temp_id.c_str()))
				{
					m_List->Retrieve_Binary(temp_db);
					temp_db.DisplayRecordOnScreen();
				}
				genre >> id;
				temp_db = to_string(id);
				temp_db.SetName("");
			}
		}
	}
	while (!PriorityList->IsEmpty())
		PriorityList->Dequeue();
}

//Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName)
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

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
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

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	//ItemType data;	// 읽기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename))
	{
		cout << "\n\tThere is no file named " << filename << endl << endl;
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
		bool addition = m_List->Add(data);/*
		if (addition)
			AddSong(data);*/
		if (addition)
		{
			CountType temp;
			int temp_ID;
			float temp_nplay;
			AddSong(data);
			data >> temp_ID;
			data >> temp_nplay;
			temp = to_string(temp_ID);
			temp = temp_nplay;
			CountList->Add(temp);
		}
	}

	m_InFile.close();	// file close

	// 현재 list 출력
	DisplayAllMusic();

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType temp;// 쓰기용 임시 변수
	char filename[100];
	cout << "\tEnter the name of file: ";
	cin >> filename;

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

//Search function, call one of two functions, search by id or name, by user's input.
void Application::Search()
{
	int input;
	cout << "\t\t1.ID\t2.Name\t3.Player\t4.Genre\t5.Lyrics\t6.Tag\n\n" << "\tInput: ";
	cin >> input;
	switch (input) {
	case 1:
		SearchById_SequenS();
		break;
	case 2:
		SearchByName();
		break;
	case 3:
		SearchBySinger();
		break;
	case 4:
		SearchByGenre();
		break;
	case 5:
		SearchByLyrics();
		break;
	case 6:
		SearchByTag();
		break;
	default:
		cout << "\tWrong Input!" << endl;
		Search();
	}
}

//Search music by id.
int Application::SearchById_SequenS()
{
	ItemType temp;//검색용 임시 변수
	temp.SetIdFromKB();

	//search success
	if (m_List->Retrieve_Binary(temp) != -1)
	{
		cout << endl << "\tResult\n" << endl;
		temp.DisplayRecordOnScreen();//print search result.
		return 1;
	}
	else
	{
		cout << endl << "\tThere's no record with your id.\n";
		return 0;
	}
}

//Search music by Name.
int Application::SearchByName()
{
	m_List->ResetList();
	ItemType temp;//검색용 임시 변수
	string input;
	bool check = false;
	cout << "\tEnter the word: ";
	cin >> input;

	cout << "\n\tResult\n\n";

	while (m_List->GetNextItem(temp) != -1) {
		//check if there's input word in data.
		if (temp != input) {
			temp.DisplayRecordOnScreen();
			check = true;
		}
	}
	//search fails.
	if (check == false) {
		cout << "\n\tThere's no record with your word.\n";
		return 0;
	}
	return 1;
}

//Search music by Lyrics.
int Application::SearchByLyrics()
{
	m_List->ResetList();
	ItemType temp;//검색용 임시 변수
	string inLyrics;
	bool check = false;
	cout << "\tEnter the word: ";
	cin.ignore(256, '\n');
	getline(cin, inLyrics);

	while (m_List->GetNextItem(temp) != -1) {
		//check if there's input word in data.
		if (temp == inLyrics) {
			cout << "\n\tResult\n\n";
			temp.DisplayRecordOnScreen();
			check = true;
		}
	}
	//search fails.
	if (check == false) {
		cout << "\n\tThere's no record with your word.\n";
		return 0;
	}
	return 1;
}

//Search SList by name.
int Application::SearchBySinger()
{
	SingerType temp_singer;//검색용 변수
	bool check_singer = false;
	temp_singer.SetNameFromKB();
	SList.RetrieveItem(temp_singer, check_singer);
	if (check_singer == true) {
		cout << endl;
		temp_singer.DisplayRecord();
		cout << "\n\tSong List...\n" << endl;
		ItemType temp;//검색용 변수
		int temp_ID;
		temp_singer.ResetList();
		temp_singer >> temp_ID;
		temp = to_string(temp_ID);
		while (temp_ID != 0)
		{
			m_List->Retrieve_Binary(temp);
			temp.DisplayRecordOnScreen();
			temp_singer >> temp_ID;
			temp = to_string(temp_ID);
			temp.SetName("");
		}
		return 1;
	}
	else {
		cout << "\n\tThere's no singer with your input..." << endl;
		return 0;
	}
}

//Search GList by number.
int Application::SearchByGenre()
{
	GenreType temp_genre;//검색용 변수
	temp_genre.SetNumFromKB();
	if (GList.Get(temp_genre)) {
		cout << endl;
		cout << "\n\tSong List...\n" << endl;
		ItemType temp;//검색용 변수
		int temp_ID;
		temp_genre.ResetList();
		temp_genre >> temp_ID;
		temp = to_string(temp_ID);
		while (temp_ID != 0)
		{
			m_List->Retrieve_Binary(temp);
			temp.DisplayRecordOnScreen();
			temp_genre >> temp_ID;
			temp = to_string(temp_ID);
			temp.SetName("");
		}
		return 1;
	}
	else {
		cout << "\n\tThere's no genre with your input..." << endl;
		return 0;
	}
}

//Search TList by tag.
int Application::SearchByTag()
{
	TagType tag;
	tag.SetTagFromKB();
	if (TList.Get(tag))
	{
		cout << endl;
		cout << "\n\tSong List...\n" << endl;
		ItemType temp;//검색용 변수
		int temp_ID;
		tag.ResetList();
		tag >> temp_ID;
		temp = to_string(temp_ID);
		while (temp_ID != 0)
		{
			m_List->Retrieve_Binary(temp);
			temp.DisplayRecordOnScreen();
			tag >> temp_ID;
			temp = to_string(temp_ID);
			temp.SetName("");
		}
		return 1;
	}
	else
		return 0;
}



//Add Genre in Genre List.
void Application::AddGenre(GenreType data)
{
	GList.Add(data);
}

//Add Singer in Singer List.
void Application::AddSinger(SingerType data)
{
	cout << "\n\tPlease fill in singer's info..." << endl;
	data.SetRecordFromKB();
	SList.Add(data);
}

//Add Tag in Tag List.
void Application::AddTag(TagType data)
{
	TList.Add(data);
}

//Add Song in Search Lists.
int Application::AddSong(ItemType data)
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
		AddGenre(genre);
		cout << endl;
		//AddSong(data);
		genre.Add(data);
		check_genre = true;
	}
	SList.RetrieveItem(singer, check_singer);
	//가수가 이미 있는 경우
	if (check_singer == true)
		singer.Add(data);
	//가수가 없는 경우
	else {
		AddSinger(singer);
		cout << endl;
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
			AddTag(tag);
			cout << endl;
			tag.Add(data);
			check_tag = true;
		}
	}
	if (check_genre == true && check_singer == true && check_tag == true)
		return 1;
	else
		return 0;
}


//Play List Operation.
//Add Song in Play List.
int Application::AddSongToPL()
{
	int temp_id;//아이디
	ItemType temp;
	PlayItem temp_insert;//추가할 노래
	temp.SetIdFromKB();//추가할 아이디 입력
	temp >> temp_id;//temp ID should not be '0'.
	temp_insert = to_string(temp_id);//아이디 할당
	
	if (m_List->Retrieve_Binary(temp) != -1)
	{
		if (PlayList.Add(temp_insert)!=0)
		{
			count++;//저장된 개수 증가.
			temp_insert = count;
			PlayList.Replace(temp_insert);
			cout << "\n\tAddition Complete\n\n";
			temp.DisplayRecordOnScreen();
			return 1;
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

//Delete Song in Play List.
int Application::DeleteSongFrPL()
{
	PlayItem temp;
	temp.SetIdFromKB();
	if (PlayList.Delete(temp) == 1) {
		cout << "\n\tDelete complete" << endl;
		count--;
		return 1;
	}
	else
		return 0;
}

//Display Play List.
void Application::DisplayPlayList()
{
	PlayList.DisplayItem();
}

//Open Play tool.
void Application::Play()
{
	int input;
	cout << "\t\t1.Insert Order\t2. Frequency\t3. Random\n\n" << "\tInput: ";
	cin >> input;
	switch (input) {
	case 1:
		PlayIOAddTime();
		break;
	case 2:
		PlayIOFreq();
		break;
	case 3:
		PlayIORandom();
		break;
	default:
		cout << "\tWrong Input!" << endl;
		Play();
	}
}

//추가한 순으로 재생.
void Application::PlayIOAddTime()
{
	int input;
	PlayItem temp_play;
	SongType temp_song;
	string temp_id;
	int play_index = 1;
	while (1) {
		cout << "\n\tPlay Next Song : 1\t\tStop : 0\t\tChange Repeatability ( now : ";
		if (r_PlayList == true)
			cout << "ON ) : 10\n";
		else
			cout << "OFF ) : 10\n";
		cout << "\n\tInput: ";
		cin >> input;
		ItemType temp_db;
		CountType temp_count;
		switch (input)
		{
		case 1:
			for (int i = 0; i < count; i++)
				if (PlayList[i] == play_index)
					temp_play = PlayList[i];
			temp_play >> temp_id;
			temp_db = temp_id;
			m_List->Retrieve_Binary(temp_db);
			cout << "\n\tNow Playing...\n\n";
			temp_db.DisplayRecordOnScreen();
			temp_db.Play();

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
			play_index++;//index 하나 감소.
			if (play_index > count&&r_PlayList == true)
				play_index = 1;//마지막까지 돌았을 때 처음으로 돌아가는 부분.
			else if (play_index > count&&r_PlayList == false)
				return;
			break;
		case 0:
			return;
		case 10:
			ChangeRepeatability();
			break;
		default:
			cout << "\n\tIllegal Selection...\n";
			return;
		}
	}
}

//재생 빈도순으로 재생.
void Application::PlayIOFreq()
{
	int input;
	PlayItem temp_play;
	SongType temp_song;
	int max_play = -1;//최대 빈도.
	int max_index = 0;//최대 빈도의 index.
	int now_play = 0;//검색 위한 변수.
	int pre_max = 1000;//이전 재생 제외하고 검색하기 위해 설정.
	int pre_index = 0;//이전 재생 제외하고 검색하기 위해 설정.
	string temp_id;
	while (1) {
		if (max_play == -1 && pre_max != 1000)//한번씩 다 재생했을 경우 다시 가장 많은 빈도수부터 재생.
		{
			if (r_PlayList == true)
				pre_max = 1000;
			else
				return;
		}
		else
		{
			cout << "\n\tPlay Next Song : 1\t\tStop : 0\t\tChange Repeatability ( now : ";
			if (r_PlayList == true)
				cout << "ON ) : 10\n";
			else
				cout << "OFF ) : 10\n";
			cout << "\n\tInput: ";
			cin >> input;
		}
		max_play = -1;
		max_index = 0;
		ItemType temp_db;
		CountType temp_count;
		switch (input)
		{
		case 1:
			for (int i = 0; i < count; i++)
			{
				PlayList[i] >> now_play;
				if (now_play > max_play&&now_play <= pre_max&&i!=pre_index)//중복 재생 피한다.
				{
					max_index = i;
					max_play = now_play;
					temp_play = PlayList[i];
				}
			}
			if (max_play == -1)
				break;
			temp_play >> temp_id;
			temp_db = temp_id;
			m_List->Retrieve_Binary(temp_db);
			cout << "\n\tNow Playing...\n\n";
			temp_db.DisplayRecordOnScreen();
			temp_db.Play();

			float temp_nplay;
			temp_count = temp_id;
			temp_db >> temp_nplay;
			temp_count = temp_nplay;
			CountList->Replace(temp_count);

			if (PlayList[max_play] == false) {
				!PlayList[max_play];//재생상태변화.
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
			++(PlayList[max_index]);
			pre_max = max_play;
			pre_index = max_index;
			break;
		case 0:
			return;
		case 10:
			ChangeRepeatability();
			break;
		default:
			cout << "\n\tIllegal Selection...\n";
			return;
		}
	}
}

//랜덤 순서로 재생. 다른 재생보다 먼저 실행될 경우 오류 발생.
void Application::PlayIORandom()
{
	int order = 1;
	int randcount = 0;
	int pre_index = -1;
	if (play_count == count) {
		for (int i = 0; i < count; i++)
			!PlayList[i];//모두 한번씩 재생 마치면 초기화.
		play_count = 0;
	}
	srand(time(NULL));
	int input;
	PlayItem temp_play;
	SongType temp_song;
	string temp_id;
	int play_index = rand() % count;//랜덤으로 시작지 선택.
	while (1) {
		cout << "\n\tPlay Next Song : 1\t\tStop : 0\t\tChange Repeatability ( now : ";
		if (r_PlayList == true)
			cout << "ON ) : 10\n";
		else
			cout << "OFF ) : 10\n";
		cout << "\n\tInput: ";
		cin >> input;
		ItemType temp_db;
		CountType temp_count;
		switch (input)
		{
		case 1:
			play_index = rand() % count;
			while (PlayList[play_index] == true) 
			{
				if (randcount == 50)
					break;
				play_index = rand() % count;
				if (play_index == pre_index)
					continue;
				randcount++;
			}//재생 안한 값을 얻을 때까지 반복.
			if(randcount==50&&order==1)
				for (int i = 0; i < count; i++)
				{
					if (PlayList[i] == false && i != pre_index)
					{
						play_index = i;
						randcount = 0;
						order = 2;
						break;
					}
				}
			else if (randcount == 50 && order == 2)
				for (int i = count-1; i >=0; i--)
				{
					if (PlayList[i] == false && i != pre_index)
					{
						play_index = i;
						randcount = 0;
						order = 1;
						break;
					}
				}
			temp_play = PlayList[play_index];
			temp_play >> temp_id;
			temp_db = temp_id;
			m_List->Retrieve_Binary(temp_db);
			cout << "\n\tNow Playing...\n\n";
			temp_db.DisplayRecordOnScreen();
			temp_db.Play();

			float temp_nplay;
			temp_count = temp_id;
			temp_db >> temp_nplay;
			temp_count = temp_nplay;
			CountList->Replace(temp_count);

			++(PlayList[play_index]);//재생 횟수 증가
			!PlayList[play_index];//재생한 상태로 변화.
			play_count++;
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
			if (play_count == count) {
				if (r_PlayList == false)
					return;
				for (int i = 0; i < count; i++)
					!PlayList[i];//모두 한번씩 재생 마치면 초기화.
				play_count = 0;
			}
			break;
		case 0:
			return;
		case 10:
			ChangeRepeatability();
			break;
		default:
			cout << "\n\tIllegal Selection...\n";
			return;
		}
	}
}

//반복 재생 on/off ( default : on )
void Application::ChangeRepeatability()
{
	if (r_PlayList == true)
		r_PlayList = false;
	else
		r_PlayList = true;
}



//Open a file by file descriptor as an input file.
int Application::PLOpenInFile(char *fileName)
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

// Open a file by file descriptor as an output file.
int Application::PLOpenOutFile(char *fileName)
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

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::PLReadDataFromFile()
{
	int index = 0;
	PlayItem data;	// 읽기용 임시 변수
	string temp_ID;

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!PLOpenInFile(filename))
	{
		cout << "\n\tThere is no file named " << filename << endl << endl;
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
				cout << "\n\tAddition Complete\n\n";
				temp.DisplayRecordOnScreen();
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

// Open a file as a write mode, and write all data into the file,
int Application::PLWriteDataToFile()
{
	char filename[100];
	cout << "\tEnter the name of file: ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!PLOpenOutFile(filename))
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
