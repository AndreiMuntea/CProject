#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <definitions.h>

/*
 * @Brief:   Converts a number given as a char* to int
 * @Params:  buffer - a const char*, the number as an array of chars
 * @Returns: int    - the int representing the value from buffer
 * @Warning: The value from buffer SHOULD be a valid integer
 */
int ToInt(const char* buffer);

/*
 * @Brief:   Compare two numbers given as array of chars
 * @Params:  firstNumber  - a const char*, first number
 *           secondNumber - a const char*, second number
 * @Returns: int: 0   - firstNumber = secondNumber;
 *                1   - firstNumber > secondNumber;
 *               -1   - firstNumber < secondNumber;             
 */
int CompareNumbers(const char* firstNumber, const char* secondNumber);

/**
 * @Brief:   Check if two given strings have the same characters
 * @Params:  firstString:  - a const char*, first given string
 *           secondString: - a const char*, second given string
 * @Returns: BOOLEAN:      - TRUE,  if the strings have the same characters
 *                         - FALSE, otherwise
 */
BOOLEAN EqualStrings(const char* firstString, const char* secondString);

/**
 * @Brief:   Fill a given buffer with zeros
 * @Params:  buffer     - a char* the buffer to be filled with 0
 *           bufferSize - an int, the size of the buffer
 * @Returns: void
 */
void SetZero(char* buffer, int bufferSize);

/*
 * @Brief:   Copy a given string into another
 * @Params:  destination  - a char**, the copy of given string
 *           source       - a char*, given string
 * @Returns: Status:      - ZERO_EXIT_STATUS, if the copy was successful
 *                        - NULL_POINTER if destination was NULL
 *                        - BAD_ALLOCATION if the wasn't enough memory
 */
STATUS StringCopy(char** destination, const char* source);

/*
* @Brief:   Append a given string at the end of another
* @Params:  destination  - a char**
*           source       - a char*, the string to be appended
* @Returns: Status:      - ZERO_EXIT_STATUS, if the append operation was successful
*                        - NULL_POINTER if destination was NULL
*                        - BAD_ALLOCATION if the wasn't enough memory
*/
STATUS StringAppend(char** destination, const char* source);

/*
 * @Brief:   Converts a number into an array of chars
 * @Params:  number  - an int, the number to be converted
 *           result  - a char**, the result
 * @Returns: Status:      - ZERO_EXIT_STATUS, if the append operation was successful
 *                        - NULL_POINTER if destination was NULL
 *                        - BAD_ALLOCATION if the wasn't enough memory
 */
STATUS ToString(int number, char** result);

/*
 * @Brief:   Returns the number of characters in a given buffer until a '\0' is encountered
 * @Params:  buffer - a char*, given buffer
 * @Returns: int    - the number of characters in buffer
 */
int Length(const char* buffer);


#endif //STRINGHELPER_H