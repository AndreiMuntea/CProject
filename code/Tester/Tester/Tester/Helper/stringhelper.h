#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <definitions.h>

int ToInt(const char* buffer);

/*
0   - firstNumber = secondNumber;
1   - firstNumber > secondNumber;
-1   - firstNumber < secondNumber;
*/
int CompareNumbers(const char* firstNumber, const char* secondNumber);

BOOLEAN EqualStrings(const char* firstString, const char* secondString);

void SetZero(char* buffer, int bufferSize);

STATUS StringCopy(char** destination, const char* source);

STATUS StringAppend(char** destination, const char* source);

int Length(const char* buffer);


#endif //STRINGHELPER_H