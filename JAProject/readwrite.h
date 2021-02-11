#pragma once
#include "JAProject.h"

// Funtion, which is changing polish letters for different representation of characters by using ACII table.
wint_t inchangePolishLetters(wint_t wch);

// Funtion, which is changing different representation of characters for polish letters by using ACII table.
wint_t backchangePolishLetters(wint_t wch);

// Function, which is appending char to array
char* appendCharToArray(char* byteArray, char wch);

// Function, which is reading letters from file
void readFile(const std::wstring& inputfilePath, char*& bytePasswordArray, char*& byteArray);

// Function, which save the coded text to the file
void writeToFile(char*& bytePasswordArray, char*& byteArray);

void calculateArrayDisplacement(char*& byteArray, char*& disByteArray);