#include "doubleLinkedListController.h"

#include <stdlib.h>

#include "../controllerStatuses.h"

STATUS DoubleLinkedListControllerCreate(PDOUBLE_LINKED_LIST_CONTROLLER* listController)
{
   STATUS status;
   PDOUBLE_LINKED_LIST_CONTROLLER tempController;
   int i;

   i = 0;
   status = ZERO_EXIT_STATUS;
   tempController = NULL;

   if (NULL == listController)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempController = (PDOUBLE_LINKED_LIST_CONTROLLER)malloc(sizeof(DOUBLE_LINKED_LIST_CONTROLLER));
   if (NULL == tempController)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   for (i = 0; i < MAX_LIST_STRUCTS; ++i)
   {
      tempController->lists[i] = NULL;
   }

   tempController->currentList = LIST_NOT_SET;
   tempController->size = 0;
   *listController = tempController;

EXIT:
   if (!SUCCESS(status))
   {
      DoubleLinkedListControllerDestroy(&tempController);
   }
   return status;
}

void DoubleLinkedListControllerDestroy(PDOUBLE_LINKED_LIST_CONTROLLER* listController)
{
   PDOUBLE_LINKED_LIST_CONTROLLER tempController;
   int i;

   tempController = NULL;
   i = 0;

   if (NULL == listController)
   {
      goto EXIT;
   }

   if (NULL == *listController)
   {
      goto EXIT;
   }

   tempController = *listController;

   for (i = 0; i < MAX_LIST_STRUCTS; ++i)
   {
      MyDoubleLinkedListDestroy(&(tempController->lists[i]));
   }

   free(*listController);
   *listController = NULL;

EXIT:
   return;
}

STATUS ListRead(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser)
{
   STATUS status;
   int itemsFound;
   int element;

   status = ZERO_EXIT_STATUS;
   itemsFound = 0;

   ++listController->size;
   listController->currentList = listController->size - 1;

   if (listController->size >= MAX_LIST_STRUCTS)
   {
      status = STRUCTS_LIMIT_REACHED;
      goto EXIT;
   }

   status = MyDoubleLinkedListCreate(&(listController->lists[listController->currentList]));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = ParserNextInt(parser, &element);
   while (SUCCESS(status))
   {
      itemsFound++;
      status = MyDoubleLinkedListInsertAtTail(listController->lists[listController->currentList], element);
      if (!SUCCESS(status))
      {
         goto EXIT;
      }
      status = ParserNextInt(parser, &element);
   }

   if (EndOfLine(parser) == TRUE)
   {
      if (itemsFound == 0 || itemsFound >= MAX_LIST_CAPACITY)
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
      MyDoubleLinkedListDestroy(&(listController->lists[listController->currentList--]));
      listController->size--;
   }
   return status;
}

STATUS ListGoTo(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser)
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
      status = INVALID_COMMAND;
      goto EXIT;
   }

   if (pos < 0 || pos >= listController->size)
   {
      status = INVALID_INDEX;
      goto EXIT;
   }

   listController->currentList = pos;

EXIT:
   return status;
}

STATUS ListPrint(PDOUBLE_LINKED_LIST_CONTROLLER listController, FILE* outputFile)
{
   STATUS status;

   status = ZERO_EXIT_STATUS;

   if (listController->currentList == LIST_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   status = MyDoubleLinkedListPrint(listController->lists[listController->currentList], outputFile);

EXIT:
   return status;
}

STATUS ListMerge(PDOUBLE_LINKED_LIST_CONTROLLER listController)
{
   STATUS status;
   PMY_DOUBLE_LINKED_LIST res;

   status = ZERO_EXIT_STATUS;
   res = NULL;

   if (listController->currentList < 0)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (listController->currentList < 1)
   {
      status = PREVIOUS_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if(listController->size + 1 >= MAX_LIST_STRUCTS)
   {
      status = STRUCTS_LIMIT_REACHED;
      goto EXIT;
   }

   status = MyDoubleLinkedListMerge(listController->lists[listController->currentList], listController->lists[listController->currentList - 1], &res);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   if (MyDoubleLinkedListLength(res) >= MAX_LIST_CAPACITY)
   {
      status = CAPACITY_LIMIT_REACHED;
      goto EXIT;
   }

   ++listController->size;
   listController->currentList = listController->size - 1;
   listController->lists[listController->currentList] = res;

EXIT:
   if (!SUCCESS(status))
   {
      MyDoubleLinkedListDestroy(&res);
   }
   return status;
}

STATUS ListSort(PDOUBLE_LINKED_LIST_CONTROLLER listController)
{
   STATUS status;
   PMY_DOUBLE_LINKED_LIST res;

   status = ZERO_EXIT_STATUS;
   res = NULL;

   if (listController->currentList == LIST_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }


   status = MyDoubleLinkedListSort(listController->lists[listController->currentList], &res);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   MyDoubleLinkedListDestroy(&(listController->lists[listController->currentList]));
   listController->lists[listController->currentList] = res;

EXIT:
   if (!SUCCESS(status))
   {
      MyDoubleLinkedListDestroy(&res);
   }
   return status;
}

STATUS ListAdd(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser)
{
   STATUS status;
   BOOLEAN ans;
   int value;

   status = ZERO_EXIT_STATUS;
   ans = TRUE;
   value = 0;

   if (listController->currentList == LIST_NOT_SET)
   {
      status = CURRENT_STRUCTURE_UNDEFINED;
      goto EXIT;
   }

   if (MyDoubleLinkedListLength(listController->lists[listController->currentList]) + 1 >= MAX_LIST_CAPACITY)
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

   status = MyDoubleLinkedListInsertAtTail(listController->lists[listController->currentList], value);

EXIT:
   return status;
}