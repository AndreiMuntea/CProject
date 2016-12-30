#include <stdlib.h>

#include "../include/myhashtable.h"

_inline int HashCode(int element)
{
   return (HASH_SLOTS - 1) & element;
}

STATUS MyHashTableCreate(PMY_HASHTABLE* hash)
{
   STATUS status;
   PMY_HASHTABLE tempHash;
   int i;

   status = ZERO_EXIT_STATUS;
   tempHash = NULL;
   i = 0;

   if (NULL == hash)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempHash = (PMY_HASHTABLE)malloc(sizeof(MY_HASHTABLE));
   if (NULL == tempHash)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   for (i = 0; i < HASH_SLOTS; ++i)
   {
      status = MyDoubleLinkedListCreate(&(tempHash->table[i]));
      if (!SUCCESS(status))
      {
         goto EXIT;
      }
   }

   tempHash->size = 0;
   *hash = tempHash;

EXIT:
   if (!SUCCESS(status))
   {
      MyHashTableDestroy(&tempHash);
   }
   return status;
}

void MyHashTableDestroy(PMY_HASHTABLE* hash)
{
   PMY_HASHTABLE tempHash;
   int i;

   i = 0;
   tempHash = NULL;
   
   if (NULL == hash)
   {
      goto EXIT;
   }

   tempHash = *hash;
   if (NULL == tempHash)
   {
      goto EXIT;
   }

   for (i = 0; i < HASH_SLOTS; ++i)
   {
      MyDoubleLinkedListDestroy(&(tempHash->table[i]));
   }

   free(*hash);
   *hash = NULL;

EXIT:
   return;
}

STATUS MyHashTableInsert(PMY_HASHTABLE hash, int element)
{
   STATUS status;
   int hashCode;

   hashCode = HashCode(element);

   status = MyDoubleLinkedListInsertAtTail(hash->table[hashCode], element);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   hash->size++;

EXIT:
   return status;
}

BOOLEAN MyHashTableSearch(PMY_HASHTABLE hash, int element)
{
   int hashCode;

   hashCode = HashCode(element);
   return MyDoubleLinkedListSearchElement(hash->table[hashCode], element);
}

int MyHashTableLength(PMY_HASHTABLE hash)
{
   return hash->size;
}