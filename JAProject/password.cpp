#pragma once
#include "JAProject.h"
#include "password.h"
#include "readwrite.h"

// Function, which is generating random capital letters  
char getRandomChar()
{
    char c = '8'+ (rand() % 35); // Return a letters from range 56-90 in ASCII
    return c;
}

// Function for Vigenere code, which generete the size of password according to filesize
size_t sizeOfPassword(size_t size)
{
    size_t tsize = 0;
    if (size > 10000) { tsize = 200; }
    else if (size > 5000) { tsize = 100; }
    else if (size > 1000) { tsize = 50; }
    else if (size > 100) { tsize = 10; }
    else if (size > 10) { tsize = 5; }
    else if (size > 0) { tsize = size; }
    return tsize;
}

// Funtion, which generate a random password and according to the code type calculates and generetes the displacement array
void generatePassword(size_t size, int codetype)
{
    if (codeOrUncode == 0) {
        // Filling the password array by the random character genereted by function getRandomChar()
        bytePasswordArray = new char[size];
        for (int i = 0; i < size; i++) {
            bytePasswordArray[i] = getRandomChar();
        }
    }
    // Filling the displacement array according to the password array
    if (codetype == 0) {
        // For one-time pad code the password is the same size like filesize, so password is rewriten with taking into account the displacement
        for (int i = 0; i < fileSize; i++) {
            disPasswordArray[i] = bytePasswordArray[i] - 56;      // Caltulation the displacement between letters 
        }
    }
    else {
        // For Vigenere code the password is rewriten in the loop until it reached the filesize and it also taking into account the displacement
        int pos = 0;
        for (int i = 0; i < fileSize; i++) {
            disPasswordArray[i] = bytePasswordArray[pos] - 56;      // Caltulation the displacement between letters 
            pos++;
            if (pos >= passwordSize) { // If the password ends, repeat loading the password until it reached the size of filesize
                pos = 0;
            }
        }
    }
}

// Funciton, which is reading the password from file
void readPasswordFromFile(std::wstring line, char *& bytePasswordArray) { 
    std::size_t length = line.size() * sizeof line[0];
    length = (length / 2)-1;
    passwordSize = length;
    bytePasswordArray = new char[length];
    for (int i = 0; i < length; i++) {

        wchar_t wch = line[i];
        if (wch > 178) { // Changing the polish letters for different representation 
            wch = inchangePolishLetters(wch);
            char c = (int)wch;
            bytePasswordArray[i] = c;
        }
        else if (wch >= 65 && wch <= 90) { // Adding the capital letters straightaway
            char c = (int)wch;
            bytePasswordArray[i] = c;
        }
    }
}
