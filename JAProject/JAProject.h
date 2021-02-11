#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <locale.h>
#include <regex>
#include <ctime> 
#include <windows.h>
#include <stdio.h>
#include <thread>

#include <cstdio>  // for _fileno
#include <locale>
#include <codecvt>
#include <AtlBase.h>
#include <atlconv.h>
#include <io.h>
#include "ui_JAProject.h"
#include "CLib.h"

extern "C" int asmTextCoding();

extern size_t fileSize;
extern size_t passwordSize;
extern int codeOrUncode;
extern char * byteArray;
extern char * disPasswordArray;
extern char* bytePasswordArray;

extern char*pp;


class JAProject : public QMainWindow
{
    Q_OBJECT

public:
    JAProject(QWidget *parent = Q_NULLPTR);
 
private slots:
    void on_chooseButton_clicked(); 
    void on_doButton_clicked();
    void on_codeButton_clicked();
    void on_uncodeButton_clicked();
private:
    Ui::JAProjectClass ui;
};
