#pragma once
// CLib.h - Contains declarations of coding functions

#ifdef CLIBRARY
#define CLIBRARY __declspec(dllexport)
#else
#define CLIBRARY __declspec(dllimport)
#endif

extern "C" CLIBRARY void cppTextCoding(int fileSize, char* password, char* text, char* distext, char *& output, int displacement);

extern "C" CLIBRARY void cppTextUncoding(int fileSize, char* password, char* text, char* distext, char*& output, int displacement);

