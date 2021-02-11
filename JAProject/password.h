#pragma once
// All functions needed to create a password array

// Function, which is generating random capital letters 
char getRandomChar();
 
// Function for Vigenere code, which generete the size of password according to filesize
size_t sizeOfPassword(size_t size);

// Funtion, which generate a random password and according to the code type calculates and generetes the displacement array
void generatePassword(size_t size, int codetype);

// Funciton, which is reading the password from file
void readPasswordFromFile(std::wstring line, char *& bytePasswordArray);