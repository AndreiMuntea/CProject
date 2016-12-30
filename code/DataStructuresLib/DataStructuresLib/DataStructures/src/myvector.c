#include <stdlib.h>

#include "../include/myvector.h"


STATUS MyVectorEnsureCapacity(PMY_VECTOR vector)
{
   int* tempItems;
   STATUS status;
   int i;

   tempItems = NULL;
   status = ZERO_EXIT_STATUS;
   i = 0;

   if (vector->size < vector->capacity)
   {
      goto EXIT;
   }

   vector->capacity *= 2;

   tempItems = (int*)malloc(vector->capacity * sizeof(int));
   if (NULL == tempItems)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   for (i = 0; i < vector->size; ++i)
   {
      tempItems[i] = vector->items[i];
   }

   free(vector->items);
   vector->items = tempItems;

EXIT:
   return status;
}


STATUS MyVectorCreate(PMY_VECTOR* vector)
{
   STATUS status;
   PMY_VECTOR tempVector;

   status = ZERO_EXIT_STATUS;
   tempVector = NULL;

   if (NULL == vector)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempVector = (PMY_VECTOR)malloc(sizeof(MY_VECTOR));
   if (NULL == tempVector)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   tempVector->items = (int*)malloc(sizeof(int));
   if (NULL == tempVector->items)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   tempVector->capacity = 1;
   tempVector->size = 0;
   *vector = tempVector;

EXIT:
   if (!SUCCESS(status))
   {
      MyVectorDestroy(&tempVector);
   }
   return status;
}

void MyVectorDestroy(PMY_VECTOR* vector)
{
   PMY_VECTOR tempVector;

   tempVector = NULL;
   
   if (NULL == vector)
   {
      goto EXIT;
   }

   tempVector = (*vector);
   if (NULL == tempVector)
   {
      goto EXIT;
   }

   if (NULL == tempVector->items)
   {
      goto CLEAR_VECTOR;
   }
   
   free(tempVector->items);
   tempVector->items = NULL;

CLEAR_VECTOR:
   free(*vector);
   *vector = NULL;

EXIT:
   return;
}

STATUS MyVectorInsert(PMY_VECTOR vector, int element)
{
   STATUS status;

   status = MyVectorEnsureCapacity(vector);
   
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   vector->items[vector->size++] = element;

EXIT:
   return status;
}

int MyVectorLength(PMY_VECTOR vector)
{
   return vector->size;
}

STATUS MyVectorRemovePosition(PMY_VECTOR vector, int position)
{
   STATUS status;
   int i;

   i = 0;
   status = ZERO_EXIT_STATUS;

   if (position < 0 || position >= vector->size)
   {
      status = INVALID_INDEX;
      goto EXIT;
   }


   for (i = position + 1; i < vector->size; ++i)
   {
      vector->items[i - 1] = vector->items[i];
   }

   --vector->size;

EXIT:
   return status;
}

STATUS MyVectorRemoveValue(PMY_VECTOR vector, int value)
{
   STATUS status;
   int i;
   BOOLEAN found;

   found = FALSE;
   i = 0;
   status = ZERO_EXIT_STATUS;

   while (i < vector->size)
   {
      if (vector->items[i] == value)
      {
         found = TRUE;
         MyVectorRemovePosition(vector, i);
      }
      else
      {
         ++i;
      }
   }

   if (found == FALSE)
   {
      status = ITEM_NOT_FOUND;
   }

   return status;
}

STATUS MyVectorGetElement(PMY_VECTOR vector, int position, int* element)
{
   STATUS status;
   int i;

   i = 0;
   status = ZERO_EXIT_STATUS;

   if (position < 0 || position >= vector->size)
   {
      status = INVALID_INDEX;
      goto EXIT;
   }

   if (NULL == element)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   *element = vector->items[position];

EXIT:
   return status;
}

STATUS MyVectorSetElement(PMY_VECTOR vector, int position, int element)
{
   STATUS status;
   int i;

   i = 0;
   status = ZERO_EXIT_STATUS;

   if (position < 0 || position >= vector->size)
   {
      status = INVALID_INDEX;
      goto EXIT;
   }

   vector->items[position] = element;

EXIT:
   return status;
}

STATUS MyVectorGetFirstEntry(PMY_VECTOR vector, int element, int* position)
{
   STATUS status;
   BOOLEAN found;
   int i;

   i = 0;
   status = ZERO_EXIT_STATUS;
   found = FALSE;

   if (NULL == position)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   while (i < vector->size && found == FALSE)
   {
      if (vector->items[i] == element)
      {
         *position = i;
         found = TRUE;
      }
      else
      {
         ++i;
      }
   }

   if (found == FALSE)
   {
      status = ITEM_NOT_FOUND;
   }


EXIT:
   return status;
}

STATUS MyVectorPrint(PMY_VECTOR vector, FILE* file)
{
   STATUS status;
   int i;
   int err;
   
   err = 0;
   i = 0;
   status = ZERO_EXIT_STATUS;

   for (i = 0; i < vector->size; ++i)
   {
      err = fprintf_s(file, "%d ", vector->items[i]);
      if (err < 0)
      {
         status = FILE_IO_ERROR;
         goto EXIT;
      }
   }

   err = fprintf_s(file, "\n");
   if (err < 0)
   {
      status = FILE_IO_ERROR;
      goto EXIT;
   }

EXIT:
   return status;
}