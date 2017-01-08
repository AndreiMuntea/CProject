#include <stdlib.h>

#include "balancedTreeController.h"
#include "../controllerStatuses.h"


STATUS BalancedSearchTreeControllerCreate(PBALANCED_SEARCH_TREE_CONTROLLER* treeController)
{
   STATUS status;
   PBALANCED_SEARCH_TREE_CONTROLLER tempController;
   int i;

   i = 0;
   tempController = NULL;
   status = ZERO_EXIT_STATUS;

   if (NULL == treeController)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempController = (PBALANCED_SEARCH_TREE_CONTROLLER)malloc(sizeof(BALANCED_SEARCH_TREE_CONTROLLER));
   if (NULL == tempController)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   for (i = 0; i < MAX_BALANCED_TREE_STRUCTS; ++i)
   {
      tempController->tree[i] = NULL;
   }

   tempController->currentBalancedSearchTree = BALANCED_TREE_NOT_SET;
   tempController->size = 0;
   *treeController = tempController;

EXIT:
   if (!SUCCESS(status))
   {
      BalancedSearchTreeControllerDestroy(&tempController);
   }
   return status;
}

void BalancedSearchTreeControllerDestroy(PBALANCED_SEARCH_TREE_CONTROLLER* treeController)
{
   PBALANCED_SEARCH_TREE_CONTROLLER temp;
   int i;

   i = 0;
   temp = NULL;

   if (NULL == treeController)
   {
      goto EXIT;
   }

   temp = *treeController;
   if (NULL == temp)
   {
      goto EXIT;
   }

   for (i = 0; i < MAX_BALANCED_TREE_STRUCTS; ++i)
   {
      MyBalancedSearchTreeDestroy(&(temp->tree[i]));
   }

   free(*treeController);
   *treeController = NULL;

EXIT:
   return;
}

STATUS BalancedTreeInsert(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser)
{

   STATUS status;
   int value;
   BOOLEAN ans;

   value = 0;
   status = ZERO_EXIT_STATUS;


   if (treeController->currentBalancedSearchTree == BALANCED_TREE_NOT_SET)
   {
      status = INVALID_INDEX;
      goto EXIT;
   }

   if (MyBalancedSearchTreeSize(treeController->tree[treeController->currentBalancedSearchTree]) + 1 >= MAX_BALANCED_TREE_CAPACITY)
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

   status = MyBalancedSearchTreeInsert(treeController->tree[treeController->currentBalancedSearchTree], value);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


EXIT:
   return status;
}

STATUS BalancedTreeRead(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser)
{
   STATUS status;
   int itemsFound;
   int element;

   status = ZERO_EXIT_STATUS;
   itemsFound = 0;


   ++treeController->size;
   treeController->currentBalancedSearchTree = treeController->size - 1;

   if (treeController->size > MAX_BALANCED_TREE_STRUCTS)
   {
      status = STRUCTS_LIMIT_REACHED;
      goto EXIT;
   }


   status = MyBalancedSearchTreeCreate(&(treeController->tree[treeController->currentBalancedSearchTree]));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = ParserNextInt(parser, &element);
   while (SUCCESS(status))
   {
      itemsFound++;
      status = MyBalancedSearchTreeInsert(treeController->tree[treeController->currentBalancedSearchTree], element);
      if (!SUCCESS(status))
      {
         goto EXIT;
      }
      status = ParserNextInt(parser, &element);
   }

   if (EndOfLine(parser) == TRUE)
   {
      if (itemsFound == 0 || itemsFound >= MAX_BALANCED_TREE_CAPACITY)
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
      if (treeController->size <= MAX_BALANCED_TREE_STRUCTS) {
         MyBalancedSearchTreeDestroy(&(treeController->tree[treeController->currentBalancedSearchTree--]));
      };
      treeController->size--;
   }
   return status;
}

STATUS BalancedTreeRemove(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser)
{
   STATUS status;
   int value;
   BOOLEAN ans;

   value = 0;
   status = ZERO_EXIT_STATUS;


   if (treeController->currentBalancedSearchTree == BALANCED_TREE_NOT_SET)
   {
      status = INVALID_INDEX;
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

   status = MyBalancedSearchTreeRemove(treeController->tree[treeController->currentBalancedSearchTree], value);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


EXIT:
   return status;
}

STATUS BalancedTreeSearch(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser, FILE* outputFile)
{
   STATUS status;
   int element;
   int err;
   BOOLEAN ans;

   status = ZERO_EXIT_STATUS;
   err = 0;
   element = 0;


   if (treeController->currentBalancedSearchTree == BALANCED_TREE_NOT_SET)
   {
      status = INVALID_INDEX;
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
      status = INVALID_COMMAND;
      goto EXIT;
   }

   ans = MyBalancedSearchTreeSearchElement(treeController->tree[treeController->currentBalancedSearchTree], element);


   if (ans == TRUE)
   {
      err = fprintf_s(outputFile, "%s\n", "FOUND");
   }
   else
   {
      err = fprintf_s(outputFile, "%s\n", "NOT_FOUND");
   }
   if (err < 0)
   {
      status = FILE_IO_ERROR;
      goto EXIT;
   }


EXIT:
   return status;
}

STATUS BalancedTreeGoTo(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser)
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

   if (pos < 0 || pos >= treeController->size)
   {
      status = INVALID_INDEX;
      goto EXIT;
   }

   treeController->currentBalancedSearchTree = pos;

EXIT:
   return status;
}