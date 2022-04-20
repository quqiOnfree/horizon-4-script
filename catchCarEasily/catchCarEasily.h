#pragma once

#include <QtWidgets/QWidget>
#include "ui_catchCarEasily.h"

class catchCarEasily : public QWidget
{
	Q_OBJECT

public:
	catchCarEasily(QWidget* parent = Q_NULLPTR);

	void startThread();
	void closeThread();

private:
	Ui::catchCarEasilyClass ui;
};
