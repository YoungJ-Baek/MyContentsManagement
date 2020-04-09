#pragma once

#include <QVBoxLayout>
#include <QDialog>
#include <QWidget>
#include "ui_Info.h"
#include "ItemType.h"

namespace Ui {
	class Info;
}

class Info : public QDialog
{
	Q_OBJECT

public:
	Info(ItemType item, QWidget *parent = Q_NULLPTR);
	~Info();

private slots:
	void on_push_close_clicked();

private:
	Ui::Info *ui;
	QVBoxLayout *layout;
};
