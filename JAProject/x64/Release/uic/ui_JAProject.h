/********************************************************************************
** Form generated from reading UI file 'JAProject.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JAPROJECT_H
#define UI_JAPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JAProjectClass
{
public:
    QAction *actionZaszyfrowanie;
    QAction *actionOdszyfrowanie;
    QWidget *centralWidget;
    QLabel *label_3;
    QPushButton *chooseButton;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *doButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *libButton_1;
    QRadioButton *libButton_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *codeButton_1;
    QRadioButton *codeButton_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *threadButton_1;
    QRadioButton *threadButton_2;
    QPushButton *codeButton;
    QPushButton *uncodeButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *JAProjectClass)
    {
        if (JAProjectClass->objectName().isEmpty())
            JAProjectClass->setObjectName(QString::fromUtf8("JAProjectClass"));
        JAProjectClass->resize(867, 470);
        QFont font;
        font.setPointSize(11);
        JAProjectClass->setFont(font);
        actionZaszyfrowanie = new QAction(JAProjectClass);
        actionZaszyfrowanie->setObjectName(QString::fromUtf8("actionZaszyfrowanie"));
        actionZaszyfrowanie->setCheckable(true);
        actionZaszyfrowanie->setChecked(false);
        actionZaszyfrowanie->setEnabled(true);
        actionZaszyfrowanie->setFont(font);
        actionOdszyfrowanie = new QAction(JAProjectClass);
        actionOdszyfrowanie->setObjectName(QString::fromUtf8("actionOdszyfrowanie"));
        actionOdszyfrowanie->setCheckable(true);
        actionOdszyfrowanie->setFont(font);
        centralWidget = new QWidget(JAProjectClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(560, 61, 170, 24));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        chooseButton = new QPushButton(centralWidget);
        chooseButton->setObjectName(QString::fromUtf8("chooseButton"));
        chooseButton->setEnabled(false);
        chooseButton->setGeometry(QRect(90, 290, 251, 60));
        chooseButton->setMinimumSize(QSize(120, 60));
        chooseButton->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(345, 61, 101, 24));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(85, 61, 139, 24));
        label->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(647, 115, 137, 24));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        lineEdit->setMaxLength(2);
        doButton = new QPushButton(centralWidget);
        doButton->setObjectName(QString::fromUtf8("doButton"));
        doButton->setEnabled(false);
        doButton->setGeometry(QRect(520, 290, 241, 60));
        doButton->setMinimumSize(QSize(120, 60));
        doButton->setMaximumSize(QSize(1677215, 16777215));
        doButton->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setEnabled(true);
        layoutWidget->setGeometry(QRect(338, 116, 103, 61));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        libButton_1 = new QRadioButton(layoutWidget);
        libButton_1->setObjectName(QString::fromUtf8("libButton_1"));
        libButton_1->setEnabled(false);
        libButton_1->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        libButton_1->setChecked(true);

        verticalLayout->addWidget(libButton_1);

        libButton_2 = new QRadioButton(layoutWidget);
        libButton_2->setObjectName(QString::fromUtf8("libButton_2"));
        libButton_2->setEnabled(false);
        libButton_2->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));

        verticalLayout->addWidget(libButton_2);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setEnabled(true);
        layoutWidget1->setGeometry(QRect(85, 116, 131, 61));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        codeButton_1 = new QRadioButton(layoutWidget1);
        codeButton_1->setObjectName(QString::fromUtf8("codeButton_1"));
        codeButton_1->setEnabled(false);
        codeButton_1->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        codeButton_1->setChecked(true);

        verticalLayout_2->addWidget(codeButton_1);

        codeButton_2 = new QRadioButton(layoutWidget1);
        codeButton_2->setObjectName(QString::fromUtf8("codeButton_2"));
        codeButton_2->setEnabled(false);
        codeButton_2->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));

        verticalLayout_2->addWidget(codeButton_2);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setEnabled(true);
        layoutWidget2->setGeometry(QRect(557, 115, 140, 61));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        threadButton_1 = new QRadioButton(layoutWidget2);
        threadButton_1->setObjectName(QString::fromUtf8("threadButton_1"));
        threadButton_1->setEnabled(false);
        threadButton_1->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        threadButton_1->setChecked(true);

        verticalLayout_3->addWidget(threadButton_1);

        threadButton_2 = new QRadioButton(layoutWidget2);
        threadButton_2->setObjectName(QString::fromUtf8("threadButton_2"));
        threadButton_2->setEnabled(false);
        threadButton_2->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));

        verticalLayout_3->addWidget(threadButton_2);

        codeButton = new QPushButton(centralWidget);
        codeButton->setObjectName(QString::fromUtf8("codeButton"));
        codeButton->setGeometry(QRect(180, 220, 251, 41));
        codeButton->setMinimumSize(QSize(120, 40));
        codeButton->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        uncodeButton = new QPushButton(centralWidget);
        uncodeButton->setObjectName(QString::fromUtf8("uncodeButton"));
        uncodeButton->setGeometry(QRect(460, 220, 251, 41));
        uncodeButton->setMinimumSize(QSize(120, 40));
        uncodeButton->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));
        JAProjectClass->setCentralWidget(centralWidget);
        layoutWidget2->raise();
        layoutWidget2->raise();
        layoutWidget2->raise();
        label->raise();
        label_2->raise();
        chooseButton->raise();
        lineEdit->raise();
        label_3->raise();
        doButton->raise();
        codeButton->raise();
        uncodeButton->raise();
        menuBar = new QMenuBar(JAProjectClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 867, 31));
        JAProjectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(JAProjectClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        JAProjectClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(JAProjectClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        JAProjectClass->setStatusBar(statusBar);

        retranslateUi(JAProjectClass);

        QMetaObject::connectSlotsByName(JAProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *JAProjectClass)
    {
        JAProjectClass->setWindowTitle(QCoreApplication::translate("JAProjectClass", "JAProject", nullptr));
        actionZaszyfrowanie->setText(QCoreApplication::translate("JAProjectClass", "Zaszyfrowanie", nullptr));
        actionOdszyfrowanie->setText(QCoreApplication::translate("JAProjectClass", "Odszyfrowanie", nullptr));
        label_3->setText(QCoreApplication::translate("JAProjectClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Wielow\304\205tkowo\305\233\304\207</span></p></body></html>", nullptr));
        chooseButton->setText(QCoreApplication::translate("JAProjectClass", "Wybierz plik", nullptr));
        label_2->setText(QCoreApplication::translate("JAProjectClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Biblioteka</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("JAProjectClass", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Rodzaj szyfru</span></p></body></html>", nullptr));
        doButton->setText(QCoreApplication::translate("JAProjectClass", "Wykonaj", nullptr));
        libButton_1->setText(QCoreApplication::translate("JAProjectClass", "Assembly", nullptr));
        libButton_2->setText(QCoreApplication::translate("JAProjectClass", "C++", nullptr));
        codeButton_1->setText(QCoreApplication::translate("JAProjectClass", "Jednorazowy", nullptr));
        codeButton_2->setText(QCoreApplication::translate("JAProjectClass", "Vigenere", nullptr));
        threadButton_1->setText(QCoreApplication::translate("JAProjectClass", "W\305\202asne", nullptr));
        threadButton_2->setText(QCoreApplication::translate("JAProjectClass", "Automatyczne", nullptr));
        codeButton->setText(QCoreApplication::translate("JAProjectClass", "Zaszyfrowanie", nullptr));
        uncodeButton->setText(QCoreApplication::translate("JAProjectClass", "Odszyfrowanie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JAProjectClass: public Ui_JAProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JAPROJECT_H
