// Text coding or uncoding for one - time pad code or Vigenere code, version 0.0
// Author: Sara Witek
// Subject: Jezyki Assemblerowe
// Year: 2020/2021
// Compiler: MSVC_x64
// File containing coding and uncoding algorithms.
// The main idea of the algorith is: 
// Calculate the displacement of the character from text
// Add the displacement from password
// Checking what character is going to represent coded character - modulo operation due to 35 available characters
// Setting back again ASCII position
// All operations available for capital and lower letters, different letters are rewritten

#include "pch.h"
#include <utility>
#include <limits.h>
#include "CLib.h"

// Parameters are: 
// fileSize - size of the part of file, which is executed by particular thread
// password - beginning of password array calculated for particular thread
// text - beginning of text array calculated for articular thread
// output - beginning of output array
// displacement - displacement according to the beggining of the array

void cppTextCoding(int fileSize, char* password, char* text, char *distext, char*& output, int displacement)
{
    int position = 0;
    int sign = 0;
   
    while (position < fileSize) { // Checking actual position if it is lower than size of the part of file for processing

        sign = text[position]; // Rewrite text character 
        sign -= distext[position];  // Calculate displacement for character from text
        sign += password[position];  // Movement to the right according to the password displacement
        sign = sign % 35; // Modulo operation due to 35 available characters - checking what character is going to represent coded character
        sign += distext[position]; // Setting back to the ASCII position
        output[position + displacement] = sign; // Write that sign to the right place in output array
        position++; // Move forward
    }
}

// Parameters are: 
// fileSize - size of the part of file, which is executed by particular thread
// password - beginning of password array calculated for particular thread
// text - beginning of text array calculated for articular thread
// output - beginning of output array
// displacement - displacement according to the beggining of the array

// Calculate the character before coding by reversing instruction
void cppTextUncoding(int fileSize, char* password, char* text, char* distext, char*& output, int displacement)
{
    int position = 0;
    int sign = 0;
   
    while (position < fileSize) { // Checking actual position if it is lower than size of the part of file for processing
        sign = text[position]; // Rewrite text character
        sign -= distext[position];  // Calculate displacement for character from text
        sign -= password[position];  // Movement to the right according to the password displacement
        if (sign < 0) { // Cheking if the value if below 0
                sign = 35 + sign; // Calculate the character by subtracting from maximum value of dispalement (35) the absolute value of actual displacemnt 
        }
        sign += distext[position]; // Setting back to the ASCII position
        output[position + displacement] = sign; // Write that sign to the right place in output array
        position++; // Move forward
    }
}

