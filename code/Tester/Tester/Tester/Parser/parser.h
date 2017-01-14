#ifndef PARSER_H
#define PARSER_H


#include <stdio.h>

#include "parserStatuses.h"


#define BUFFER_SIZE     4096           //2 ^ 12
#define ELEMENT_SIZE    sizeof(char)
#define MAX_COUNT       BUFFER_SIZE


typedef struct _PARSER
{
   char buffer[BUFFER_SIZE];
   FILE* file;
   int bufferSize;
   int currentIndex;

}PARSER, *PPARSER;

/*
 * @Brief:   Creates a PARSER on a file
 * @Params:  parser   - a PPARSER*
 *           fileName - a const char*, the name of the file
 * @Returns: Status:  - ZERO_EXIT_STATUS, if the operation was successful
 *                    - NULL_POINTER if parser or fileName were NULL
 *                    - BAD_ALLOCATION if the wasn't enough memory
 *                    - OPEN_FILE_ERROR if the file couldn't be opened in read mode
 */
STATUS ParserCreate(PPARSER* parser, const char* fileName);

/**
 * @Brief:   Destroys a given PARSER
 * @Params:  parser - a PPARSER*, parser to be destroyed
 * @Returns: void
 */
void ParserDestroy(PPARSER* parser);

/*
 * @Brief:   Read until the end of file is reached or a non space character is encountered
 * @Params:  parser - a PPARSER
 * @Returns: Status:  - ZERO_EXIT_STATUS, if the operation was successful
 *                    - FILE_IO_ERROR if there was a read error
 */
STATUS ParserSkipSpaces(PPARSER parser);

/*
* @Brief:   Returns the next int value
* @Params:  parser   - a PPARSER
*           element  - an int*, the result
* @Returns: Status:  - ZERO_EXIT_STATUS, if the operation was successful
*                    - FILE_IO_ERROR if there was a read error
*                    - INVALID_INPUT if there wasn't a valid integer
*/
STATUS ParserNextInt(PPARSER parser, int* element);

/*
* @Brief:   Returns the next string value until a delimiter is encountered
* @Params:  parser         - a PPARSER
*           buffer         - a char**, the result
*           maxBufferSize  - an int, the maximum number of characters
* @Returns: Status:        - ZERO_EXIT_STATUS, if the operation was successful
*                          - NULL_POINTER if buffer was NULL
*                          - FILE_IO_ERROR if there was a read error
*                          - INVALID_INPUT if there were more than maxBufferSize characters
*/
STATUS ParserNextString(PPARSER parser, char** buffer, int maxBufferSize);

/**
 * @Brief:    Flushes a line.
 * @Params:   parser  - a PPARSER
 * @Returns:  Status: - ZERO_EXIT_STATUS, if the operation was successful
 *                    - NULL_POINTER if buffer was NULL
 *                    - FILE_IO_ERROR if there was a read error
 */
STATUS ParserFlushLine(PPARSER parser);

/**
* @Brief:   Checks if the end of file is reached
* @Params:  parser   - a PPARSER
* @Returns: BOOLEAN: - TRUE,  if the end of file was reached
*                    - FALSE, otherwise 
*/
BOOLEAN EndOfFile(PPARSER parser);

/**
* @Brief:   Checks if the end of line is reached
* @Params:  parser   - a PPARSER
* @Returns: BOOLEAN: - TRUE,  if the end of line was reached
*                    - FALSE, otherwise
*/
BOOLEAN EndOfLine(PPARSER parser);

/**
* @Brief:   Checks if the line contains only spaces untill the end
* @Params:  parser  - a PPARSER
*           answer  - a BOOLEAN*, the result
* @Returns: Status: - ZERO_EXIT_STATUS, if the operation was successful
*                   - NULL_POINTER if answer was NULL
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS ParserEmptyLine(PPARSER parser, BOOLEAN* answer);

#endif //PARSER_H