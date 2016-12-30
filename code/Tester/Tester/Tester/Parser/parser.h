#ifndef PARSER_H
#define PARSER_H


#include <stdio.h>

#include "parserStatuses.h"


#define BUFFER_SIZE     256
#define ELEMENT_SIZE    sizeof(char)
#define MAX_COUNT       BUFFER_SIZE


typedef struct _PARSER
{
   char buffer[BUFFER_SIZE];
   FILE* file;
   int bufferSize;
   int currentIndex;

}PARSER, *PPARSER;

STATUS ParserCreate(PPARSER* parser, const char* fileName);

void ParserDestroy(PPARSER* parser);

STATUS ParserSkipSpaces(PPARSER parser);

STATUS ParserNextInt(PPARSER parser, int* element);

STATUS ParserNextString(PPARSER parser, char** buffer, int maxBufferSize);

STATUS ParserFlushLine(PPARSER parser);

BOOLEAN EndOfFile(PPARSER parser);

BOOLEAN EndOfLine(PPARSER parser);

STATUS ParserEmptyLine(PPARSER parser, BOOLEAN* answer);

#endif //PARSER_H