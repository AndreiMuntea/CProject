#include <stdlib.h>

#include "vectorController.h"
#include "../controllerStatuses.h"
#include "../Heap/heapController.h"

STATUS VectorControllerCreate(PVECTOR_CONTROLLER* vectorController)
{
   STATUS status;
   PVECTOR_CONTROLLER tempController;
   int i;

   i = 0;
   tempController = NULL;
   status = ZERO_EXIT_STATUS;

   if (NULL == vectorController)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempController = (PVECTOR_CONTROLLER)malloc(sizeof(VECTOR_CONTROLLER));
   if (NULL == tempController)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   for (i = 0; i < MAX_VECTOR_STRUCTS; ++i)
   {
      tempController->vectors[i] = NULL;
   }

   tempController->currentVector = VECTOR_NOT_SET;
   tempController->size = 0;
   *vectorController = tempController;

EXIT:
   if (!SUCCESS(status))
   {
      VectorControllerDestroy(&tempController);
   }
   return status;
}

void VectorControllerDestroy(PVECTOR_CONTROLLER* vectorController)
{
   PVECTOR_CONTROLLER temp;
   int i;

   i = 0;
   temp = NULL;

   if (NULL == vectorController)
   {
      goto EXIT;
   }

   temp = *vectorController;
   if (NULL == temp)
   {
      goto EXIT;
   }

   for (i = 0; i < MAX_VECTOR_STRUCTS; ++i)
   {
      MyVectorDestroy(&(temp->vectors[i]));
   }

   free(*vectorController);
   *vectorController = NULL;

EXIT:
   return;
}

STATUS VectorRead(PVECTOR_CONTROLLER vectorController, PPARSER parser)
{
   STATUS status;
   int itemsFound;
   int element;
   int currentPosition;

   status = ZERO_EXIT_STATUS;
   itemsFound = 0;
   currentPosition = vectorController->currentVector;

   ++vectorController->size;
   vectorController->currentVector = vectorController->size - 1;

   if (vectorController->size> MAX_VECTOR_STRUCTS)
   {
      status = STRUCTS_LIMIT_REACHED;
      goto EXIT;
   }

   status = MyVectorCreate(&(vectorController->vectors[vectorController->currentVector]));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = ParserNextInt(parser, &element);
   while (SUCCESS(status) && itemsFound <= MAX_VECTOR_CAPACITY)
   {
      itemsFound++;
      status = MyVectorInsert(vectorController->vectors[vectorController->currentVector], element);
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
      else if (itemsFound > MAX_VECTOR_CAPACITY)
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
      if (vectorController->size <= MAX_VECTOR_STRUCTS)
      {
         MyVectorDestroy(&(vectorController->vectors[vectorController->currentVector--]));
      }
      vectorController->size--;
      vectorController->currentVector = currentPosition;
   }
   return status;
}

STATUS VectorPrint(PVECTOR_CONTROLLER vectorController, FILE* outputFile)
{
   STATUS status;

   status = ZERO_EXIT_STATUS;

   if (vectorController->currentVector == VECTOR_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (vectorController->currentVector >= vectorController->size)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   
   status = MyVectorPrint(vectorController->vectors[vectorController->currentVector], outputFile);

EXIT:
   return status;
}

STATUS VectorGoTo(PVECTOR_CONTROLLER vectorController, PPARSER parser)
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

   if (pos < 0 || pos >= MAX_VECTOR_STRUCTS)
   {
      status = INVALID_INDEX;
      goto EXIT;
   }

   vectorController->currentVector = pos;

EXIT:
   return status;
}

STATUS VectorLength(PVECTOR_CONTROLLER vectorController, FILE* outputFile)
{
   STATUS status;
   int err;

   err = 0;
   status = ZERO_EXIT_STATUS;

   if (vectorController->currentVector == VECTOR_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (vectorController->currentVector >= vectorController->size)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   err = fprintf_s(outputFile, "%d\n", MyVectorLength(vectorController->vectors[vectorController->currentVector]));
   if (err < 0)
   {
      status = FILE_IO_ERROR;
      goto EXIT;
   }

EXIT:
   return status;
}

STATUS VectorSearch(PVECTOR_CONTROLLER vectorController, PPARSER parser, FILE* outputFile)
{
   STATUS status;
   int element;
   int pos;
   int err;
   BOOLEAN ans;

   pos = 0;
   status = ZERO_EXIT_STATUS;
   err = 0;
   element = 0;

   if (vectorController->currentVector == VECTOR_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (vectorController->currentVector >= vectorController->size)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   status = ParserNextInt(parser, &element);
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

   status = MyVectorGetFirstEntry(vectorController->vectors[vectorController->currentVector], element, &pos);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   err = fprintf_s(outputFile, "%d\n", pos);
   if (err < 0)
   {
      status = FILE_IO_ERROR;
      goto EXIT;
   }


EXIT:
   return status;
}

STATUS VectorRemovePosition(PVECTOR_CONTROLLER vectorController, PPARSER parser)
{
   STATUS status;
   int pos;
   BOOLEAN ans;


   pos = 0;
   status = ZERO_EXIT_STATUS;

   if (vectorController->currentVector == VECTOR_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }


   if (vectorController->currentVector >= vectorController->size)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

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

   status = MyVectorRemovePosition(vectorController->vectors[vectorController->currentVector], pos);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


EXIT:
   return status;
}

STATUS VectorRemoveValue(PVECTOR_CONTROLLER vectorController, PPARSER parser)
{
   STATUS status;
   int value;
   BOOLEAN ans;

   value = 0;
   status = ZERO_EXIT_STATUS;

   if (vectorController->currentVector == VECTOR_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (vectorController->currentVector >= vectorController->size)
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

   status = MyVectorRemoveValue(vectorController->vectors[vectorController->currentVector],value);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


EXIT:
   return status;
}

STATUS VectorAdd(PVECTOR_CONTROLLER vectorController, PPARSER parser)
{
   STATUS status;
   int value;
   BOOLEAN ans;

   value = 0;
   status = ZERO_EXIT_STATUS;

   if (vectorController->currentVector == VECTOR_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (vectorController->currentVector >= vectorController->size)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (MyVectorLength(vectorController->vectors[vectorController->currentVector]) + 1 > MAX_VECTOR_CAPACITY)
   {
      status = CAPACITY_LIMIT_REACHED;
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

   status = MyVectorInsert(vectorController->vectors[vectorController->currentVector], value);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


EXIT:
   return status;
}