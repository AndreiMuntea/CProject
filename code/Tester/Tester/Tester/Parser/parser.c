#include <stdlib.h>

#include "parser.h"
#include "../Helper/stringhelper.h"


_inline BOOLEAN IsDelimiter(char c)
{
   return (c == ' ' || c == '\t' || c == '\n' || c == '\0') ? TRUE : FALSE;
}

_inline BOOLEAN IsEndOfLine(char c)
{
   return (c == '\n' || c == '\0') ? TRUE : FALSE;
}

_inline BOOLEAN IsSpace(char c)
{
   return (c == ' ' || c == '\t') ? TRUE : FALSE;
}

_inline BOOLEAN IsDigit(char c)
{
   return (c >= '0' && c <= '9') ? TRUE : FALSE;
}

BOOLEAN EndOfFile(PPARSER parser)
{
   return (feof(parser->file) && parser->bufferSize  == 0) ? TRUE : FALSE;
}

BOOLEAN EndOfLine(PPARSER parser)
{
   return IsEndOfLine(parser->buffer[parser->currentIndex]);
}

void ResetBuffer(PPARSER parser)
{
   SetZero(parser->buffer, BUFFER_SIZE);
   parser->bufferSize = 0;
   parser->currentIndex = 0;
}


STATUS Read(PPARSER parser)
{
   STATUS status;
   int read;

   status = ZERO_EXIT_STATUS;
   read = 0;

   ResetBuffer(parser);


   read = fread_s(parser->buffer, BUFFER_SIZE, ELEMENT_SIZE, MAX_COUNT, parser->file);
   if (read < MAX_COUNT && !feof(parser->file))
   {
      status = FILE_IO_ERROR;
      ResetBuffer(parser);
      goto EXIT;
   }

   parser->bufferSize = read;

EXIT:
   return status;
}

STATUS ParserSkipSpaces(PPARSER parser)
{
   STATUS status;
   BOOLEAN skipped;

   skipped = FALSE;
   status = ZERO_EXIT_STATUS;

   while (skipped == FALSE)
   {
      if (parser->currentIndex == parser->bufferSize)
      {
         status = Read(parser);
         if (!SUCCESS(status))
         {
            goto EXIT;
         }
      }

      if (parser->bufferSize == 0)
      {
         skipped = TRUE;
      }

      if (IsSpace(parser->buffer[parser->currentIndex]))
      {
         parser->currentIndex++;
      }
      else
      {
         skipped = TRUE;
      }
   }


EXIT:
   return status;
}

STATUS ParserNextInt(PPARSER parser, int* element)
{
   const char* MIN_INT_VALUE = "-2147483648";
   const char* MAX_INT_VALUE = "2147483647";

   STATUS status;
   char number[12];
   int size;
   int digitCount;

   size = 0;
   digitCount = 0;
   SetZero(number, 12);
   status = ZERO_EXIT_STATUS;

   if (NULL == element)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   // skip whitespaces
   status = ParserSkipSpaces(parser);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   if (parser->bufferSize == 0)
   {
      status = END_OF_FILE;
      goto EXIT;
   }

   // we got a negative number here
   if (parser->buffer[parser->currentIndex] == '-')
   {
      parser->currentIndex++;
      number[0] = '-';
      size = 1;
   }

   while (1)
   {
      // end of buffer 
      if (parser->currentIndex == parser->bufferSize)
      {
         status = Read(parser);
         if (!SUCCESS(status))
         {
            goto EXIT;
         }
      }

      // we got a delimiter
      if (parser->bufferSize == 0 || IsDelimiter(parser->buffer[parser->currentIndex]) == TRUE)
      {
         break;
      }

      // we got a digit
      if (IsDigit(parser->buffer[parser->currentIndex]) == TRUE)
      {
         // full buffer => we can't add
         if (size == 11)
         {
            status = BUFFER_OVERFLOW;
            goto EXIT;
         }

         number[size++] = parser->buffer[parser->currentIndex];
         digitCount++;
         parser->currentIndex++;
      }
      // we got a non-digit char
      else
      {
         status = INVALID_INPUT;
         goto EXIT;
      }
   }

   // we got no digit at all in our number
   if (digitCount == 0)
   {
      status = INVALID_INPUT;
      goto EXIT;
   }

   // number exceeds int dimensions if the min int value is greater than the number or the max int value is lower
   if (CompareNumbers(MIN_INT_VALUE, number) == 1 ||
      CompareNumbers(MAX_INT_VALUE, number) == -1)
   {
      status = BUFFER_OVERFLOW;
      goto EXIT;
   }

   *element = ToInt(number);

EXIT:
   return status;
}

STATUS ParserNextString(PPARSER parser, char** buffer, int maxBufferSize)
{
   STATUS status;
   int size;
   char* buff;

   size = 0;
   status = ZERO_EXIT_STATUS;
   buff = NULL;

   if (NULL == buffer)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   buff = (char*)malloc(maxBufferSize * sizeof(char));
   if (NULL == buff)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   SetZero(buff, maxBufferSize);

   while (1)
   {
      // end of file buffer 
      if (parser->currentIndex == parser->bufferSize)
      {
         status = Read(parser);
         if (!SUCCESS(status))
         {
            goto EXIT;
         }
      }

      // we got a delimiter
      if (parser->bufferSize == 0 || IsEndOfLine(parser->buffer[parser->currentIndex]) == TRUE)
      {
         break;
      }

      if (size == maxBufferSize)
      {
         status = BUFFER_OVERFLOW;
         goto EXIT;
      }

      buff[size++] = parser->buffer[parser->currentIndex++];
   }

   *buffer = buff;

EXIT:
   if (!SUCCESS(status))
   {
      free(buff);
      buff = NULL;
   }
   return status;
}

STATUS ParserCreate(PPARSER* parser, const char* fileName)
{
   STATUS status;
   PPARSER tempParser;
   FILE* file;
   int i;
   int err;

   err = 0;
   i = 0;
   file = NULL;
   tempParser = NULL;
   status = ZERO_EXIT_STATUS;

   if (NULL == parser)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   if (NULL == fileName)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempParser = (PPARSER)malloc(sizeof(PARSER));
   if (NULL == tempParser)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   err = fopen_s(&file, fileName, "r");
   if (err != 0)
   {
      tempParser->file = NULL;
      status = OPEN_FILE_ERROR;
      goto EXIT;
   }

   tempParser->file = file;
   tempParser->bufferSize = 0;
   tempParser->currentIndex = 0;
   SetZero(tempParser->buffer, BUFFER_SIZE);

   *parser = tempParser;

EXIT:
   if (!SUCCESS(status))
   {
      ParserDestroy(&tempParser);
   }
   return status;
}

void ParserDestroy(PPARSER* parser)
{
   PPARSER tempParser;

   tempParser = NULL;

   if (NULL == parser)
   {
      goto EXIT;
   }

   if (NULL == *parser)
   {
      goto EXIT;
   }

   tempParser = *parser;
   if (NULL != tempParser->file)
   {
      fclose(tempParser->file);
   }

   free(*parser);
   *parser = NULL;

EXIT:
   return;
}

STATUS ParserFlushLine(PPARSER parser)
{
   STATUS status;

   status = ZERO_EXIT_STATUS;

   while (1)
   {
      if (parser->currentIndex == parser->bufferSize)
      {
         status = Read(parser);
         if (!SUCCESS(status))
         {
            goto EXIT;
         }
      }

      if (parser->bufferSize == 0 || parser->buffer[parser->currentIndex] == '\n')
      {
         parser->currentIndex++;
         break;
      }

      parser->currentIndex++;
   }

EXIT:
   return status;
}


STATUS ParserEmptyLine(PPARSER parser, BOOLEAN* answer)
{
   STATUS status;
   BOOLEAN ans;

   status = ZERO_EXIT_STATUS;
   ans = TRUE;

   status = ParserSkipSpaces(parser);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   ans = EndOfLine(parser);
   *answer = ans;

EXIT:
   return status;
}