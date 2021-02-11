#pragma once
#include "JAProject.h"
#include "password.h"
#include "readwrite.h"
#include "timecal.h"

// Global variables
std::string fileNameStdString; // Path to the file
int threads = 0; // Number of threads avaiable for user

size_t fileSize = 0; // File size
size_t passwordSize = 0; // Password size
int codeOrUncode = 0; // Variable, which contains the decision of the user

char* byteArray = "";// Byte array
char* disByteArray = NULL; // Displacement array
char* bytePasswordArray = NULL; // Byte password array
char* disPasswordArray = NULL; // Displacement password array
char* byteOutputArray = NULL; // Byte output array

typedef void(CALLBACK* CODINGPROC)(int fileSize, char* password, char* text, char* distext, char*& output, int displacement);
typedef void(CALLBACK* CODINGASMPROC)(char* password, char* text, char* distext, char* output, int fileSize);

HINSTANCE hDLL; // For cheking if dll is here
CODINGPROC codingPtr; // For checking if dll c++ contains functions
CODINGASMPROC codingAsmPtr; // For checking if dll asm contains functions

Timer dllTime;
Timer totalTime;

// Funtion, which gets amount of cores
int getNumCores() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}

// Function, which is actives threads
void threadFunction(int algtype) {

    dllTime.start();
    dllTime.pause();
    DWORDLONG splitValue = fileSize / threads; // Seperating the filesize according to number of threads
    DWORDLONG extra = fileSize - (threads * splitValue); // If the division had left part of text unallocated to thread
    std::vector<std::thread> threadVector; // Vector of threads

    // Algtype = 0/1 -> Asm / c++
   
        if (algtype == 0) {
            dllTime.resume();
            for (int i = 0; i < threads; i++) {
                int size = splitValue + extra;

                if (i + 1 == threads) { // Adding extra to the last thread
                    std::thread th(codingAsmPtr, (disPasswordArray + i * splitValue), (byteArray + i * splitValue), (disByteArray + i * splitValue), (byteOutputArray + i * splitValue), size);
                    threadVector.push_back(std::move(th));
                }
                else {
                    std::thread th(codingAsmPtr, (disPasswordArray + i * splitValue), (byteArray + i * splitValue), (disByteArray + i * splitValue), (byteOutputArray + i * splitValue), size);
                    threadVector.push_back(std::move(th));
                }
            }
        }
        else {

            dllTime.resume();
            for (int i = 0; i < threads; i++) {
                if (i + 1 == threads) { // Adding extra to the last thread
                
                    std::thread th(codingPtr, (splitValue + extra), (disPasswordArray + i * splitValue), (byteArray + i * splitValue), (disByteArray + i * splitValue), std::ref(byteOutputArray), (i * splitValue));
                    threadVector.push_back(std::move(th));
                }
                else {
                 
                    std::thread th(codingPtr, splitValue, (disPasswordArray + i * splitValue), (byteArray + i * splitValue), (disByteArray + i * splitValue), std::ref(byteOutputArray), (i * splitValue));
                    threadVector.push_back(std::move(th));
                }
            }
        }
    
    for (std::thread& th : threadVector) // Waiting for all thread to end
    {
        th.join();
    }
    dllTime.pause();
}

// Funtion for starting the QUI
JAProject::JAProject(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

// User choose the .txt file, which content will be loaded to byte array.
void JAProject::on_chooseButton_clicked() {

    bool tf = false; // For checking if the file path has been set correctly
    while (!tf) {
        // Qt file dialog for searching only txt files
        QString fileName = QFileDialog::getOpenFileName(this, tr("Wybierz plik txt"), "", "*.txt");
        QFile file(fileName);

        // Checking if the chosen file can be opened or if it isn't empty
        if ((!file.open(QFile::ReadOnly | QFile::Text)) || (fileName.isEmpty())){
            tf = false;
            QMessageBox::warning(this, "Blad", "Niepoprawna sciezka do pliku lub plik nie zostal otwarty poprawnie");
        }
        else {
            file.close();
            tf = true; // File has been opened correctly
            // Setting the file path
            fileNameStdString = fileName.toStdString(); // Converting QString to String
            CA2W ss(fileNameStdString.c_str());
            std::wstring wfilePath = ss; // Converting for wstring

            //Reading the file
            readFile(wfilePath, bytePasswordArray,byteArray);
            fileSize = strlen(byteArray); // Setting file size according to byteArray, which has been filled in line before
        }
    }
}

// User generate the coded text
void JAProject::on_doButton_clicked() {

    bool flag = false; // Flag in case of wrong parametrs
    bool critical = false; // Flag in case of dll issue
    totalTime.start();
    if (!fileNameStdString.empty()) { // Checking if the user had chosen the file path

        byteOutputArray = new char[fileSize]; // Setting the size of output array
        disPasswordArray = new char[fileSize]; // Setting the temporary password array
        disByteArray = new char[fileSize]; // Setting  the displacement array
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        if (ui.threadButton_1->isChecked()) { // User chosen to input own value of threads

            QString threadstring = ui.lineEdit->text(); // Getting the input string
            bool ok;
            int number = threadstring.toInt(&ok);
            if (!ok) { // Conversion to check if the input is a int
                QMessageBox::warning(this, "Blad", "Niepoprawny format. Prosze wpisac liczbe od 1 do 64");
                flag = true;
                goto GETOUT; // Break of the all loops in case of incorret parametr
            }
            if ((number < 1) || (number > 64)) { // Cheking if input int is in range 1 to 64
                QMessageBox::warning(this, "Blad", "Niepoprawny zakres. Prosze wpisac liczbe od 1 do 64");
                flag = true;
                goto GETOUT; // Break of the all loops in case of incorret parametr
            }
            else { threads = number; } // Initialization amount of threads
        }
        else { // User chosen to automatic set value of threads
            threads = getNumCores();
        }

        if (codeOrUncode == 0) {

            /////////////////////////////////////////////////////////////////////////////////////////////////////
            // Password generation
            if (ui.codeButton_1->isChecked()) { // One-time pad code

                passwordSize = fileSize; // Setting size of password array
                generatePassword(passwordSize, 0);
            }
            else {  // Vigenere code

                passwordSize = sizeOfPassword(fileSize); // Setting size of password array
                generatePassword(passwordSize, 1);
            }

            calculateArrayDisplacement(byteArray, disByteArray);
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            // Chosing the type of coding
            if (ui.libButton_1->isChecked()) { // Assemmbly

                hDLL = LoadLibraryA("AsmDLL");
                if (hDLL == NULL) { // Checking if DLL is there
                    flag = true;
                    FreeLibrary(hDLL);
                    goto DLL_EXIT; // Break of the all loops in case of incorret parametr
                }
                else {
                    codingAsmPtr = (CODINGASMPROC)GetProcAddress(hDLL, "asmTextCoding"); 
                    threadFunction(0);
                }
            }
            else { // C++

                hDLL = LoadLibraryA("CLib");
                if (hDLL == NULL) { // Checking if DLL is there
                    flag = true;
                    FreeLibrary(hDLL);
                    goto DLL_EXIT; // Break of the all loops in case of incorret parametr
                }
                else {
                    codingPtr = (CODINGPROC)GetProcAddress(hDLL, "cppTextCoding");
                    threadFunction(1);
                }
            }
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        else { // For uncoding the text

          
            threads = getNumCores();
            if (passwordSize < fileSize) {
                generatePassword(passwordSize, 1); // Vigenere code
            }
            else {
                generatePassword(passwordSize, 0); // One-time pad code
            }
            calculateArrayDisplacement(byteArray, disByteArray);

            if (ui.libButton_1->isChecked()) { // Assemmbly

                hDLL = LoadLibraryA("AsmDLL");
                if (hDLL == NULL) { // Checking if DLL is there
                    flag = true;
                    FreeLibrary(hDLL);
                    goto DLL_EXIT; // Break of the all loops in case of incorret parametr
                }
                else {
                    codingAsmPtr = (CODINGASMPROC)GetProcAddress(hDLL, "asmTextUncoding");
                    threadFunction(0);
                }
            }
            else {

                hDLL = LoadLibraryA("CLib");
                if (hDLL == NULL) { // Checking if DLL is there
                    flag = true;
                    FreeLibrary(hDLL);
                    goto DLL_EXIT; // Break of the all loops in case of incorret parametr
                }
                else {
                    codingPtr = (CODINGPROC)GetProcAddress(hDLL, "cppTextUncoding");
                    threadFunction(1);
                }
            }
        }

        writeToFile(bytePasswordArray,byteOutputArray); // Write output array to the file
        totalTime.stop();
        double secTotalTimeResult = (totalTime.getCounterTotalTicks() * 1000.0) / totalTime.getCounterFrequency();
        double secDllTimeResult = (dllTime.getCounterTotalTicks() * 1000.0) / dllTime.getCounterFrequency();
        std::string totalTimeResult(" Pelny czas:  " + std::to_string(secTotalTimeResult) + " ms");
        std::string dllTimeResult(" DLL czas:  " + std::to_string(secDllTimeResult) + " ms");
        std::string returnString = totalTimeResult + "\n" + dllTimeResult;
        QString qstr = QString::fromStdString(returnString);

        if (codeOrUncode == 0) {
            QMessageBox::warning(this, "Koniec", " Tekst zostal poprawnie zakodowany \n" + qstr);
        }
        else {
            QMessageBox::warning(this, "Koniec", " Tekst zostal poprawnie odkodowany \n" + qstr);
        }

        ui.codeButton->setEnabled(true);
        ui.uncodeButton->setEnabled(true);
        ui.doButton->setEnabled(false);
        ui.chooseButton->setEnabled(false);
        ui.threadButton_1->setEnabled(false);
        ui.threadButton_2->setEnabled(false);
        ui.codeButton_1->setEnabled(false);
        ui.codeButton_2->setEnabled(false);
        ui.libButton_1->setEnabled(false);
        ui.libButton_2->setEnabled(false);
        ui.lineEdit->setEnabled(false);

        /////////////////////////////////////////////////////////////////////////////////////////////////////
  // Cleaning the memory
        delete[] byteArray;
        delete[] disByteArray;
        delete[] bytePasswordArray;
        delete[] disPasswordArray;
        delete[] byteOutputArray;

        byteArray = "";
        disByteArray = "";
        bytePasswordArray = "";
        disPasswordArray = "";
        byteOutputArray = "";
        passwordSize = 0;
        fileSize = 0;
        fileNameStdString = "";
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    else { 
    QMessageBox::warning(this, "Blad", "Musisz wybrac plik wejsciowy .txt"); // Path to the file hasn't been chosen
    totalTime.stop();
    } 

    if (flag) { GETOUT: QMessageBox::warning(this, "Blad", " Sprobuj ponownie "); totalTime.stop();} // Incorrect parraments in program
    if (critical) { DLL_EXIT: QMessageBox::warning(this, "Blad", " DLL plik nie zosta³ znaleziony!"); totalTime.stop();} // Incorrect dll in program

 
}

// User had chosen to code text
void JAProject::on_codeButton_clicked()
{ 
    codeOrUncode = 0;
    ui.uncodeButton->setEnabled(false);
    ui.doButton->setEnabled(true);
    ui.chooseButton->setEnabled(true);
    ui.threadButton_1->setEnabled(true);
    ui.threadButton_2->setEnabled(true);
    ui.codeButton_1->setEnabled(true);
    ui.codeButton_2->setEnabled(true);
    ui.libButton_1->setEnabled(true);
    ui.libButton_2->setEnabled(true);
    ui.lineEdit->setEnabled(true);
}

// User had chosen to uncode the text
void JAProject::on_uncodeButton_clicked()
{
    codeOrUncode = 1;
    ui.codeButton->setEnabled(false);
    ui.doButton->setEnabled(true);
    ui.chooseButton->setEnabled(true);
    ui.threadButton_1->setEnabled(true);
    ui.threadButton_2->setEnabled(true);
    ui.codeButton_1->setEnabled(false);
    ui.codeButton_2->setEnabled(false);
    ui.libButton_1->setEnabled(true);
    ui.libButton_2->setEnabled(true);
    ui.lineEdit->setEnabled(true);
}

