#include "CountType.h"
#include "ItemType.h"


//Constructor.
CountType::CountType()
{
	c_ID = "";
	c_numPlay = 0;
}

//Default Destructor.
CountType::~CountType()
{
}

//Increase play count.
CountType& CountType::operator++()
{
	c_numPlay++;
	return *this;
}

//Compare if left one is more played.
bool CountType::operator>(CountType &data)
{
		if (this->c_numPlay > data.c_numPlay)
			return true;
		else
			return false;
}

//Compare if right one is more played.
bool CountType::operator<(CountType &data)
{
	if (this->c_numPlay < data.c_numPlay)
		return true;
	else
		return false;
}

//Assign data.
CountType& CountType::operator=(const string& data)
{
	c_ID = data;
	return *this;
}

//Assign data.
CountType& CountType::operator=(const CountType& data)
{
	c_ID = data.c_ID;
	c_numPlay = data.c_numPlay;
	return *this;
}

//Assign data.
CountType& CountType::operator=(const float& data)
{
	c_numPlay = (int)data;
	return *this;
}

//Compare data.
bool CountType::operator==(CountType &data)
{
	if (c_ID == data.c_ID)
		return true;
	else
		return false;
}

//Extract ID
void CountType::operator>>(string& temp_ID)
{
	temp_ID = c_ID;
}

bool CountType::operator!()
{
	if (c_numPlay == 0)
		return true;
	else
		return false;
}