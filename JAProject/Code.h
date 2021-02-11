#pragma once

#include <QWidget>
#include "ui_Code.h"

class Code : public QWidget, public Ui::Code
{
	Q_OBJECT

public:
	Code(QWidget *parent = Q_NULLPTR);
	~Code();
};
