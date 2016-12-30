#include "stringhelper.h"

#include <stdlib.h>

int ToInt(const char* buffer)
{
   int result;
   int i;
   BOOLEAN negative;
   int size;

   size = Length(buffer);
   i = 0;
   result = 0;
   negative = FALSE;

   if (buffer[0] == '-')
   {
      negative = TRUE;
      i = 1;
   }

   for (; i < size; ++i)
   {
      result = (result * 10) + (buffer[i] - '0');
   }

   if (negative == TRUE)
   {
      result = -result;
   }

   return result;

}

int CompareNumbers(const char* firstNumber, const char* secondNumber)
{
   BOOLEAN reversedResult;
   int index;
   int result;
   int firstNumberSize;
   int secondNumberSize;

   reversedResult = FALSE;
   index = 0;
   result = 0;
   firstNumberSize = Length(firstNumber);
   secondNumberSize = Length(secondNumber);

   if (firstNumber[0] == '-' && secondNumber[0] != '-')
   {
      result = -1;
      goto EXIT;
   }

   if (firstNumber[0] != '-' && secondNumber[0] == '-')
   {
      result = 1;
      goto EXIT;
   }

   if (firstNumber[0] == '-' && secondNumber[0] == '-')
   {
      index = 1;
      reversedResult = TRUE;
   }

   if (firstNumberSize < secondNumberSize)
   {
      result = (reversedResult == TRUE) ? 1 : -1;
      goto EXIT;
   }

   if (firstNumberSize > secondNumberSize)
   {
      result = (reversedResult == TRUE) ? -1 : 1;
      goto EXIT;
   }

   for (; index < firstNumberSize; ++index)
   {
      if (firstNumber[index] < secondNumber[index])
      {
         result = (reversedResult == TRUE) ? 1 : -1;
         goto EXIT;
      }
      else if (firstNumber[index] > secondNumber[index])
      {
         result = (reversedResult == TRUE) ? -1 : 1;
         goto EXIT;
      }
   }

   result = 0;

EXIT:
   return result;
}

void SetZero(char* buffer, int bufferSize)
{
   int i;

   for (i = 0; i < bufferSize; ++i)
   {
      buffer[i] = 0;
   }
}

int Length(const char* buffer)
{
   int size;

   size = 0;

   while (buffer[size] != '\0') ++size;

   return size;
}

BOOLEAN EqualStrings(const char* firstString, const char* secondString)
{
   BOOLEAN equals;
   int firstStringLength;
   int secondStringLength;
   int index;

   equals = TRUE;
   firstStringLength = Length(firstString);
   secondStringLength = Length(secondString);
   index = 0;

   if (firstStringLength != secondStringLength)
   {
      equals = FALSE;
   }

   while (equals == TRUE && index < firstStringLength)
   {
      if (firstString[index] != secondString[index])
      {
         equals = FALSE;
      }
      ++index;
   }

   return equals;

}

STATUS StringCopy(char** destination, const char* source)
{
   STATUS status;
   char* tmp;
   int size;
   int i;

   size = 0;
   i = 0;
   status = ZERO_EXIT_STATUS;
   tmp = NULL;

   if (NULL == destination)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   size = Length(source) + 1;
   
   tmp = (char*)malloc(size * sizeof(char));
   if (NULL == tmp)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   SetZero(tmp, size);

   for (i = 0; i < size; ++i)
   {
      tmp[i] = source[i];
   }

   *destination = tmp;

EXIT:
   return status;
}

STATUS StringAppend(char** destination, const char* source)
{
   STATUS status;
   char* temp; 
   char* origin;
   int size;
   int i;
   int destinationLength;

   i = 0;
   status = ZERO_EXIT_STATUS;
   temp = NULL;
   origin = NULL;
   size = 0;
   destinationLength = 0;

   if (NULL == destination)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   destinationLength = Length(*destination);
   size = destinationLength + Length(source) + 1;
   
   temp = (char*)malloc(size * sizeof(char));
   if (NULL == temp)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   SetZero(temp, size);
   origin = *destination;

   for (i = 0; i < destinationLength; ++i)
   {
      temp[i] = origin[i];
   }

   for (i = destinationLength; i < size; ++i)
   {
      temp[i] = source[i - destinationLength];
   }

   free(origin);
   *destination = temp;

EXIT:
   return status;
}