
#include "readwrite.h"
#include "password.h"

// Polish letters (9) are gonna be represented in ascii table by different char
// char letter -> dec ascii : char 
// ¥ -> 56 : 8                ¹ -> 91 : [   
// Æ -> 57 : 9                æ -> 92 : \   
// Ê -> 58 : :                ê -> 93 : ]
// £ -> 59 : ;                ³ -> 94 : ^
// Ñ -> 60 : <                ñ -> 95 : _
// Ó -> 61 : =                ó -> 96 : `
// Œ -> 62 : >                œ -> 97 : a
//  -> 63 : ?                Ÿ -> 98 : b
// ¯ -> 64 : @                ¿ -> 99 : c

// Funtion, which is changing polish letters for different representation of characters by using ACII table.
wint_t inchangePolishLetters(wint_t wch)
{
    switch (wch) {
        // Capital letters
    case 260: // ¥
    {   return 56; break; }
    case 262: // Æ
    {   return 57; break; }
    case 280: // Ê
    {   return 58; break; }
    case 321: // £
    {   return 59; break; }
    case 323: // Ñ
    {   return 60; break; }
    case 211: // Ó
    {   return 61; break; }
    case 346: // Œ
    {   return 62; break; }
    case 377: // 
    {   return 63; break; }
    case 379: // ¯
    {   return 64; break; }
        // Lower letters
    case 261: // ¹
    {   return 91; break; }
    case 263: // æ
    {   return 92; break; }
    case 281: // ê
    {   return 93; break; }
    case 322: // ³
    {   return 94; break; }
    case 324: // ñ
    {   return 95; break; }
    case 243: // ó
    {   return 96; break; }
    case 347: // œ
    {   return 97; break; }
    case 378: // Ÿ
    {   return 98; break; }
    case 380: // ¿
    {   return 99; break; }

    default: { return wch; }
    }
}

// Funtion, which is changing different representation of characters for polish letters by using ACII table.
wint_t backchangePolishLetters(wint_t wch)
{
    switch (wch) {
        // Capital letters
    case 56: // ¥
    {   return 260; break; }
    case 57: // Æ
    {   return 262; break; }
    case 58: // Ê
    {   return 280; break; }
    case 59: // £
    {   return 321; break; }
    case 60: // Ñ
    {   return 323; break; }
    case 61: // Ó
    {   return 211; break; }
    case 62: // Œ
    {   return 346; break; }
    case 63: // 
    {   return 377; break; }
    case 64: // ¯
    {   return 379; break; }
        // Lower letters
    case 91: // ¹
    {   return 261; break; }
    case 92: // æ
    {   return 263; break; }
    case 93: // ê
    {   return 281; break; }
    case 94: // ³
    {   return 322; break; }
    case 95: // ñ
    {   return 324; break; }
    case 96: // ó
    {   return 243; break; }
    case 97: // œ
    {   return 347; break; }
    case 98: // Ÿ
    {   return 378; break; }
    case 99: // ¿
    {   return 380; break; }

    default: { return wch; }
    }
}

// Function, which is appending char to array
char* appendCharToArray(char* byteArray, char wch)
{
    size_t len = strlen(byteArray); // Check size of the actual byteArray
    char* newArray = new char[len + 2]; // Create new one which size is bigger
    strcpy(newArray, byteArray); // Copy the values
    newArray[len] = wch; // Add the new character
    newArray[len + 1] = '\0';
    return newArray; 
}

// Function, which is reading letters from file
void readFile(const std::wstring& inputfilePath, char*& bytePasswordArray,char *& byteArray ) {

    const wchar_t* wcs = inputfilePath.c_str();
    FILE* fileIn = _wfopen(wcs, L"r,ccs=UNICODE");
    std::wifstream inputStream(fileIn);

    // Read the file contents
    wchar_t wch;
    int i = 0;
    std::wstring line;
    if (codeOrUncode == 1) {
        getline(inputStream, line);
        readPasswordFromFile(line, bytePasswordArray);
    }
    while (inputStream.get(wch))
    {
            if (wch > 178) { // Changing the polish letters for different representation 
                char cc = inchangePolishLetters(wch);
                byteArray = appendCharToArray(byteArray, cc);
            }
            else if (!((wch >= 65 && wch <= 90) || (wch >= 97 && wch <= 122))) { // Ignoring all characters which are different then space or new line
                if (wch == 10 || wch  == 32) { // Adding that character to the array
                    char cc = (int)wch;
                    byteArray = appendCharToArray(byteArray, cc);
                }
            }
            else if (wch >= 65 && wch <= 90) { // Adding the capital letters straightaway
                char cc = (int)wch;
                byteArray = appendCharToArray(byteArray, cc);
            }
            else { // For lower letters it has to be displacement included
                wch = wch + 3;
                char cc = (int)wch;
                byteArray = appendCharToArray(byteArray, cc);
            }
            i++;
     }
    inputStream.close();
}

//  Function, which is saving coded text to the file
void writeToFile(char*& bytePasswordArray, char*& byteOutputArray)
{
    FILE* outputStream;
    // Open the file as Unicode for writing
    if (codeOrUncode == 0) {
        outputStream = _wfopen(L"coding.txt", L"w,ccs=UNICODE");
    }
    else {
        outputStream = _wfopen(L"uncoding.txt", L"w,ccs=UNICODE");
    }
    std::wofstream output(outputStream);

    // Write to the file
    wchar_t wch;
    for (int i = 0; i < passwordSize; i++)
    {
        wch = bytePasswordArray[i]; // Get the letter from output array
        if (wch >= 56 && wch <= 64) { // For the range has to be made a uncoding for polish letters - password only ussing capital letters
            wch = backchangePolishLetters(wch);
        }
        fputwc(wch, outputStream); // Write characters from password to the file
    }
    wch = L';';
    fputwc(wch, outputStream);
    wch = L'\n';
    fputwc(wch, outputStream);

    // Write array to the file
    for (int i = 0; i < fileSize; i++)
    {
        wch = byteOutputArray[i];
        if ((wch >= 56 && wch <= 64) || (wch >= 91 && wch <= 99)) {
            wch = backchangePolishLetters(wch); // For the range has to be made a uncoding for polish letters
        }
        else if (wch >= 99 && wch <= 125) {
            wch = wch - 3;
        }
       
        fputwc(wch, outputStream); // Write characters from output array to the file
    }
    output.close();
}

// Funtion, which generate a random password and according to the code type calculates and generetes the displacement array
void calculateArrayDisplacement(char*& byteArray,char *& disByteArray)
{
    for (int i = 0; i < fileSize; i++) {
        char tsign = byteArray[i];
        if (tsign == 10 || tsign == 32) {
                disByteArray[i] = 0; // For different characters
                disPasswordArray[i] = 0;
        }
        else {
            if (tsign < 91) { // For capital letters
                disByteArray[i] = 56; // Displacement in regard to ASCII table 
            }
            else { // For lower letters
                disByteArray[i] = 91;// Displacement in regard to ASCII table
            }
        }
    }
}