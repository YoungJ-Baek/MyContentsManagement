#include "MusicManagement.h"
#include <QtWidgets/QApplication>
#include <direct.h>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	_mkdir("./DB/");
	_mkdir("./MasterList/");
	_mkdir("./PlayList/");
	ifstream user;
	user.open("user.txt");
	if (user.is_open() == false)
	{
		Register userdata;
		int det = userdata.exec();
		if (det == QDialog::Rejected)
			return 0;
	}

	LogIn userdata;
	int det = userdata.exec();
	int m_ListSize = userdata.GetSize();
	if (det == QDialog::Rejected)
		return 0;
	
	MusicManagement w(m_ListSize);
	w.show();
	return a.exec();
}
