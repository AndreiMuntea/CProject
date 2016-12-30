#include <stdlib.h>

#include "heapController.h"
#include "../controllerStatuses.h"

STATUS HeapControllerCreate(PHEAP_CONTROLLER* heapController)
{
   STATUS status;
   PHEAP_CONTROLLER tempController;
   int i;

   i = 0;
   tempController = NULL;
   status = ZERO_EXIT_STATUS;

   if (NULL == heapController)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempController = (PHEAP_CONTROLLER)malloc(sizeof(HEAP_CONTROLLER));
   if (NULL == tempController)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   for (i = 0; i < MAX_HEAP_STRUCTS; ++i)
   {
      tempController->heap[i] = NULL;
   }

   tempController->currentHeap = HEAP_NOT_SET;
   tempController->size = 0;
   *heapController = tempController;

EXIT:
   if (!SUCCESS(status))
   {
      HeapControllerDestroy(&tempController);
   }
   return status;
}

void HeapControllerDestroy(PHEAP_CONTROLLER* heapController)
{
   PHEAP_CONTROLLER temp;
   int i;

   i = 0;
   temp = NULL;

   if (NULL == heapController)
   {
      goto EXIT;
   }

   temp = *heapController;
   if (NULL == temp)
   {
      goto EXIT;
   }

   for (i = 0; i < MAX_HEAP_STRUCTS; ++i)
   {
      MyHeapDestroy(&(temp->heap[i]));
   }

   free(*heapController);
   *heapController = NULL;

EXIT:
   return;
}

STATUS HeapInsert(PHEAP_CONTROLLER heapController, PPARSER parser)
{
   STATUS status;
   int value;
   BOOLEAN ans;

   value = 0;
   status = ZERO_EXIT_STATUS;


   if (heapController->currentHeap == HEAP_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (MyHeapLength(heapController->heap[heapController->currentHeap]) + 1 >= MAX_HEAP_CAPACITY)
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
      status = INVALID_COMMAND;
      goto EXIT;
   }

   status = MyHeapInsert(heapController->heap[heapController->currentHeap], value);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


EXIT:
   return status;
}

STATUS HeapRead(PHEAP_CONTROLLER heapController, PPARSER parser)
{
   STATUS status;
   int itemsFound;
   int element;

   status = ZERO_EXIT_STATUS;
   itemsFound = 0;

   ++heapController->size;
   heapController->currentHeap = heapController->size - 1;

   if (heapController->size >= MAX_HEAP_STRUCTS)
   {
      status = STRUCTS_LIMIT_REACHED;
      goto EXIT;
   }

   status = MyHeapCreate(&(heapController->heap[heapController->currentHeap]));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = ParserNextInt(parser, &element);
   while (SUCCESS(status))
   {
      itemsFound++;
      status = MyHeapInsert(heapController->heap[heapController->currentHeap], element);
      if (!SUCCESS(status))
      {
         goto EXIT;
      }
      status = ParserNextInt(parser, &element);
   }

   if (EndOfLine(parser) == TRUE)
   {
      if (itemsFound == 0 || itemsFound >= MAX_HEAP_CAPACITY)
      {
         status = INVALID_COMMAND;
      }
      else
      {
         status = ZERO_EXIT_STATUS;
      }
      goto EXIT;
   }
   else
   {
      status = INVALID_COMMAND;
   }

EXIT:
   if (!SUCCESS(status))
   {
      MyHeapDestroy(&(heapController->heap[heapController->currentHeap--]));
      heapController->size--;
   }
   return status;
}

STATUS HeapRemove(PHEAP_CONTROLLER heapController, FILE* outputFile)
{
   STATUS status;
   int value;
   int err;

   status = ZERO_EXIT_STATUS;


   if (heapController->currentHeap == HEAP_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   status = MyHeapGetMin(heapController->heap[heapController->currentHeap], &value);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   err = fprintf_s(outputFile, "%d\n", value);
   if (err < 0)
   {
      status = FILE_IO_ERROR;
      goto EXIT;
   }

   status = MyHeapRemove(heapController->heap[heapController->currentHeap]);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


EXIT:
   return status;
}