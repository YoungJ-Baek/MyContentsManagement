#pragma once
#include <string>
#include "ItemType.h"

using namespace std;

/**
*	playitem class for music playlist(item class).
*/
class PlayItem
{
private:
	string p_ID;		//Song ID.
	int p_numPlay;		//재생 횟수
	int p_inTime;		//곡이 play list에 삽입된 시간(이 과제에서는 들어온 순서를 사용) 
	bool play;			//이미 재생했는지 확인
public:

	/**
	*	default constructor.
	*/
	PlayItem();

	/**
	*	default destructor.
	*/
	~PlayItem();

	/**
	*	@brief	Set music id from keyboard.
	*	@pre	none.
	*	@post	music id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Set record from keyboard except ID.
	*	@pre	none.
	*	@post	item record is set.
	*/
	void SetRecordFromKB();

	//Read & Write File
	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	music record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new music record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well
	*/
	int WriteDataToFile(ofstream& fout);

	/**
	*	@brief	Assign data's insert order to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by value.
	*/
	void operator=(const int& temp_Count);

	/**
	*	@brief	Assign data's ID to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by value.
	*/
	void operator=(const string& temp_id);

	/**
	*	@brief	Assign parameter ID by record.
	*	@pre	object should be initialized.
	*	@post	prarameter record is set by value.
	*/
	void operator>>(string& temp_ID);

	/**
	*	@brief	Assign parameter frequency by record.
	*	@pre	object should be initialized.
	*	@post	prarameter record is set by value.
	*/
	void operator>>(int& temp_freq);

	/**
	*	Compare two PlayItem if they are same.
	*	@brief	Compare two playitem types if thery are same by id.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.(equality)
	*	@param	data	target object for comparing.
	*	@return return true if they have same id, otherwise, return false.
	*/
	bool operator==(PlayItem &data);

	/**
	*	@brief	Check play.
	*	@pre	self is initialized, and check is initialized.
	*	@post	check play state.
	*	@param	check	true : play is true state		false : play is false state.
	*	@return	return true if play is same as check, otherwise,
	*			return false.
	*/
	bool operator==(bool check);

	/**
	*	@brief	Check order.
	*	@pre	self is initialized, and check is initialized.
	*	@post	check insert order.
	*	@param	order	check insert order.
	*	@return	return true if p_inTime is same as order, otherwise,
	*			return false.
	*/
	bool operator==(int order);

	/**
	*	@brief	Increase 실행 횟수.
	*	@pre	object should be initialized.
	*	@post	p_numplay +1.
	*	@return	return this pointer ( p_numplay + 1 ).
	*/
	PlayItem& operator++();

	/**
	*	@brief	Compare two item types if left one is late.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.
	*	@param	data	target item for comparing.
	*	@return return true if left one has late order, otherwise, return false.
	*/
	bool operator>(PlayItem &data);

	/**
	*	@brief	Compare two item types if right one is late.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.
	*	@param	data	target item for comparing.
	*	@return return true if right one has late order, otherwise, return false.
	*/
	bool operator<(PlayItem &data);

	/**
	*	@brief	Change play state.
	*	@pre	none.
	*	@post	change play state.
	*/
	void operator!();

	/**
	*	@brief	Display record on screen.
	*	@pre	brief records are set.
	*	@post	record is on screen.
	*/
	friend ostream& operator<<(ostream& os, const PlayItem& data);
};

