#pragma once
#include <string>
#include <iostream>

using namespace std;

class CountType
{
private:
	string c_ID;		//Song ID.
	float c_numPlay;	//Play Count ( float type for weight ).
public:
	/**
	*	default constructor.
	*/
	CountType();
	/**
	*	default destructor.
	*/
	~CountType();

	/**
	*	@brief	Increase c_numPlay.
	*	@pre	object should be initialized.
	*	@post	c_numplay +1.
	*	@return	return this pointer ( c_numplay + 1 ).
	*/
	CountType& operator++();

	/**
	*	@brief	Compare two item types if left one is more played.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.
	*	@param	data	target item for comparing.
	*	@return return true if left one played more, otherwise, return false.
	*/
	bool operator>(CountType &data);

	/**
	*	@brief	Compare two item types if right one is more played.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.
	*	@param	data	target item for comparing.
	*	@return return true if right one played more, otherwise, return false.
	*/
	bool operator<(CountType &data);

	/**
	*	@brief	Assign data's record to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by data's
	*	@return CountType with record being filled.
	*/
	CountType& operator=(const string& data);

	/**
	*	@brief	Assign data's record to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by data's
	*	@return CountType with record being filled.
	*/
	CountType& operator=(const float& data);

	/**
	*	@brief	Assign data's record to self's record.
	*	@pre	data should be initialized.
	*	@post	record is set by data's
	*	@return CountType with record being filled.
	*/
	CountType& operator=(const CountType& data);

	/**
	*	Compare two counttype if they are same.
	*	@brief	Compare two item types if thery are same by item id.
	*	@pre	two item types should be initialized.
	*	@post	show two item types' relationship.(equality)
	*	@param	data	target item for comparing.
	*	@return return true if they have same id, otherwise, return false.
	*/
	bool operator==(CountType &data);

	/**
	*	@brief	출력 연산자 오버로딩 <<
	*	@pre	CountType의 정보를 호출한다.
	*	@post	호출한 CountType의 정보를 출력한다.
	*	@param	item	CountType형 변수.
	*/
	void operator<<(CountType item) { cout << "\tPlay : " << c_numPlay << endl; }

	/**
	*	@brief	Substitute ID record to temp_ID.
	*	@pre	object should be initialized.
	*	@post	prarameter ID is set by record.
	*/
	void operator>>(string& temp_ID);

	/**
	*	@brief	Tell if item type is empty.
	*	@pre	none.
	*	@post	know item type's emptiness.
	*	@return	return true if it is empty, otherwise, return false.
	*/
	bool operator!();
};
