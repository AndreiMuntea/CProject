#include <stdlib.h>

#include "hashTableController.h"
#include "../controllerStatuses.h"
#include "../Heap/heapController.h"

STATUS HashTableControllerCreate(PMY_HASHTABLE_CONTROLLER* hashController)
{
   STATUS status;
   PMY_HASHTABLE_CONTROLLER tempController;
   int i;

   i = 0;
   status = ZERO_EXIT_STATUS;
   tempController = NULL;

   if (NULL == hashController)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempController = (PMY_HASHTABLE_CONTROLLER)malloc(sizeof(MY_HASHTABLE_CONTROLLER));
   if (NULL == tempController)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   for (i = 0; i < MAX_HASH_STRUCTS; ++i)
   {
      tempController->hash[i] = NULL;
   }

   tempController->currentHash = HASH_NOT_SET;
   tempController->size = 0;
   *hashController = tempController;

EXIT:
   if (!SUCCESS(status))
   {
      HashTableControllerDestroy(&tempController);
   }
   return status;
}

void HashTableControllerDestroy(PMY_HASHTABLE_CONTROLLER* hashController)
{
   PMY_HASHTABLE_CONTROLLER tempController;
   int i;

   i = 0;
   tempController = NULL;

   if (NULL == hashController)
   {
      goto EXIT;
   }

   if (NULL == *hashController)
   {
      goto EXIT;
   }

   tempController = *hashController;

   for (i = 0; i < MAX_HASH_STRUCTS; ++i)
   {
      MyHashTableDestroy(&(tempController->hash[i]));
   }

   free(*hashController);
   *hashController = NULL;

EXIT:
   return;
}

STATUS HashTableRead(PMY_HASHTABLE_CONTROLLER hashController, PPARSER parser)
{
   STATUS status;
   int itemsFound;
   int element;
   int currentPosition;

   status = ZERO_EXIT_STATUS;
   itemsFound = 0;
   currentPosition = hashController->currentHash;

   ++hashController->size;
   hashController->currentHash = hashController->size - 1;

   if (hashController->size > MAX_HASH_STRUCTS)
   {
      status = STRUCTS_LIMIT_REACHED;
      goto EXIT;
   }


   status = MyHashTableCreate(&(hashController->hash[hashController->currentHash]));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = ParserNextInt(parser, &element);
   while (SUCCESS(status) && itemsFound <= MAX_HASH_CAPACITY)
   {
      itemsFound++;
      status = MyHashTableInsert(hashController->hash[hashController->currentHash], element);
      if (!SUCCESS(status))
      {
         goto EXIT;
      }
      status = ParserNextInt(parser, &element);
   }

   if (EndOfLine(parser) == TRUE)
   {
      if (itemsFound == 0)
      {
         status = INVALID_INPUT;
      }
      else if (itemsFound > MAX_HASH_CAPACITY)
      {
         status = CAPACITY_LIMIT_REACHED;
      }
      else
      {
         status = ZERO_EXIT_STATUS;
      }
   }
   else
   {
      status = INVALID_INPUT;
   }

EXIT:
   if (!SUCCESS(status))
   {
      if (hashController->size <= MAX_HASH_STRUCTS)
      {
         MyHashTableDestroy(&(hashController->hash[hashController->currentHash--]));
      }
      hashController->size--;
      hashController->currentHash = currentPosition;
   }
   return status;
}

STATUS HashTableSearch(PMY_HASHTABLE_CONTROLLER hashController, PPARSER parser, FILE* outputFile)
{
   STATUS status;
   BOOLEAN ans;
   int value;
   int err;

   err = 0;
   status = ZERO_EXIT_STATUS;
   ans = TRUE;
   value = 0;

   if(hashController->currentHash == HASH_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (hashController->currentHash >= hashController->size)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   status = ParserNextInt(parser, &value);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


   status = ParserEmptyLine(parser, &ans);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   if (ans == FALSE)
   {
      status = INVALID_INPUT;
      goto EXIT;
   }

   ans = MyHashTableSearch(hashController->hash[hashController->currentHash], value);
   
   err = (ans == TRUE) ? fprintf_s(outputFile, "FOUND\n") : fprintf_s(outputFile, "NOT_FOUND\n");
   if (err < 0)
   {
      status = FILE_IO_ERROR;
      goto EXIT;
   }



EXIT:
   return status;
}

STATUS HashTableGoTo(PMY_HASHTABLE_CONTROLLER hashController, PPARSER parser)
{
   STATUS status;
   BOOLEAN ans;
   int pos;

   status = ZERO_EXIT_STATUS;

   status = ParserNextInt(parser, &pos);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = ParserEmptyLine(parser, &ans);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   if (ans == FALSE)
   {
      status = INVALID_INPUT;
      goto EXIT;
   }

   if (pos < 0 || pos >= MAX_HASH_STRUCTS)
   {
      status = INVALID_INDEX;
      goto EXIT;
   }

   hashController->currentHash = pos;

EXIT:
   return status;
}