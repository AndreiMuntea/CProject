#include <stdlib.h>

#include "../include/mydoublelinkedlist.h"

STATUS CreateNode(PNODE* node, int element)
{
   STATUS status;
   PNODE tempNode;

   status = ZERO_EXIT_STATUS;
   tempNode = NULL;

   if (NULL == node)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempNode = (PNODE)malloc(sizeof(NODE));
   if (NULL == tempNode)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   tempNode->next = NULL;
   tempNode->previous = NULL;
   tempNode->data = element;

   *node = tempNode;

EXIT:
   return status;
}

STATUS SplitList(PMY_DOUBLE_LINKED_LIST list, PMY_DOUBLE_LINKED_LIST* firstHalf, PMY_DOUBLE_LINKED_LIST* secondHalf)
{
   STATUS status;
   PNODE fast;
   PNODE lazy;
   PMY_DOUBLE_LINKED_LIST first;
   PMY_DOUBLE_LINKED_LIST second;

   status = ZERO_EXIT_STATUS;
   first = NULL;
   second = NULL;
   fast = NULL;
   lazy = NULL;

   if (NULL == firstHalf)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   if (NULL == secondHalf)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   status = MyDoubleLinkedListCreate(&first);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = MyDoubleLinkedListCreate(&second);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   fast = list->head;
   lazy = list->head;

   while (fast != NULL && fast->next != NULL)
   {
      status = MyDoubleLinkedListInsertAtTail(first, lazy->data);
      lazy = lazy->next;
      fast = fast->next->next;

      if (!SUCCESS(status))
      {
         goto EXIT;
      }
   }

   while (lazy != NULL)
   {
      status = MyDoubleLinkedListInsertAtTail(second, lazy->data);
      lazy = lazy->next;

      if (!SUCCESS(status))
      {
         goto EXIT;
      }
   }

   *firstHalf = first;
   *secondHalf = second;

EXIT:
   if (!SUCCESS(status))
   {
      MyDoubleLinkedListDestroy(&first);
      MyDoubleLinkedListDestroy(&second);
   }
   return status;
}


STATUS MyDoubleLinkedListCreate(PMY_DOUBLE_LINKED_LIST* list)
{
   STATUS status;
   PMY_DOUBLE_LINKED_LIST tempList;

   status = ZERO_EXIT_STATUS;
   tempList = NULL;

   if (NULL == list)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempList = (PMY_DOUBLE_LINKED_LIST)malloc(sizeof(MY_DOUBLE_LINKED_LIST));
   if (NULL == tempList)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   tempList->size = 0;
   tempList->head = NULL;
   tempList->tail = NULL;

   *list = tempList;

EXIT:
   return status;
}

void MyDoubleLinkedListDestroy(PMY_DOUBLE_LINKED_LIST* list)
{
   PNODE currentNode;
   PNODE auxNode;

   currentNode = NULL;
   auxNode = NULL;

   if (NULL == list)
   {
      goto EXIT;
   }

   if (NULL == *list)
   {
      goto EXIT;
   }

   currentNode = (*list)->head;
   
   while (currentNode != NULL)
   {
      auxNode = currentNode->next;
      free(currentNode);
      currentNode = auxNode;
   }

   free(*list);
   *list = NULL;

EXIT:
   return;
}

STATUS MyDoubleLinkedListInsertAtHead(PMY_DOUBLE_LINKED_LIST list, int element)
{
   STATUS status;
   PNODE node;

   status = ZERO_EXIT_STATUS;
   node = NULL;

   status = CreateNode(&node, element);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   if (list->head == NULL)
   {
      list->head = node;
      list->tail = node;
      ++list->size;
      goto EXIT;
   }

   node->next = list->head;
   list->head->previous = node;
   list->head = node;
   ++list->size;

EXIT:
   return status;
}

STATUS MyDoubleLinkedListInsertAtTail(PMY_DOUBLE_LINKED_LIST list, int element)
{
   STATUS status;
   PNODE node;

   status = ZERO_EXIT_STATUS;
   node = NULL;

   status = CreateNode(&node, element);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   if (list->head == NULL)
   {
      list->head = node;
      list->tail = node;
      ++list->size;
      goto EXIT;
   }

   node->previous = list->tail;
   list->tail->next = node;
   list->tail = node;
   ++list->size;

EXIT:
   return status;
}

STATUS MyDoubleLinkedListMerge(PMY_DOUBLE_LINKED_LIST firstList, PMY_DOUBLE_LINKED_LIST secondList, PMY_DOUBLE_LINKED_LIST* result)
{
   STATUS status;
   PMY_DOUBLE_LINKED_LIST tempList;
   PNODE firstListElement;
   PNODE secondListElement;

   tempList = NULL;
   status = ZERO_EXIT_STATUS;
   firstListElement = NULL;
   secondListElement = NULL;

   if (NULL == result)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   status = MyDoubleLinkedListCreate(&tempList);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   firstListElement = firstList->head;
   secondListElement = secondList->head;

   while (firstListElement != NULL && secondListElement != NULL)
   {
      if (firstListElement->data < secondListElement->data)
      {
         status = MyDoubleLinkedListInsertAtTail(tempList, firstListElement->data);
         firstListElement = firstListElement->next;
      }
      else
      {
         status = MyDoubleLinkedListInsertAtTail(tempList, secondListElement->data);
         secondListElement = secondListElement->next;
      }
      if (!SUCCESS(status))
      {
         goto EXIT;
      }
   }

   while (firstListElement != NULL)
   {
      status = MyDoubleLinkedListInsertAtTail(tempList, firstListElement->data);
      firstListElement = firstListElement->next;
      if (!SUCCESS(status))
      {
         goto EXIT;
      }
   }

   while (secondListElement != NULL)
   {
      status = MyDoubleLinkedListInsertAtTail(tempList, secondListElement->data);
      secondListElement = secondListElement->next;
      if (!SUCCESS(status))
      {
         goto EXIT;
      }
   }

   *result = tempList;

EXIT:
   if (!SUCCESS(status))
   {
      MyDoubleLinkedListDestroy(&tempList);
   }
   return status;
}

STATUS MyDoubleLinkedListSort(PMY_DOUBLE_LINKED_LIST list, PMY_DOUBLE_LINKED_LIST* result)
{
   STATUS status;
   PMY_DOUBLE_LINKED_LIST res;
   PMY_DOUBLE_LINKED_LIST firstHalf;
   PMY_DOUBLE_LINKED_LIST secondHalf;
   PMY_DOUBLE_LINKED_LIST sortedFirstHalf;
   PMY_DOUBLE_LINKED_LIST sortedSecondHalf;

   status = ZERO_EXIT_STATUS;
   res = NULL;
   firstHalf = NULL;
   secondHalf = NULL;
   sortedFirstHalf = NULL;
   sortedSecondHalf = NULL;

   if (NULL == result)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   if(NULL == list->head)
   {
      status = MyDoubleLinkedListCreate(result);
      goto EXIT;
   }

   if (NULL == list->head->next)
   {
      status = MyDoubleLinkedListCreate(result);
      if (!SUCCESS(status))
      {
         goto EXIT;
      }

      status = MyDoubleLinkedListInsertAtTail(*result, list->head->data);
      goto EXIT;
   }

   status = SplitList(list, &firstHalf, &secondHalf);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = MyDoubleLinkedListSort(firstHalf, &sortedFirstHalf);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = MyDoubleLinkedListSort(secondHalf, &sortedSecondHalf);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = MyDoubleLinkedListMerge(sortedFirstHalf, sortedSecondHalf, &res);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   *result = res;

EXIT:
   if (!SUCCESS(status))
   {
      MyDoubleLinkedListDestroy(&res);
   }
   MyDoubleLinkedListDestroy(&firstHalf);
   MyDoubleLinkedListDestroy(&secondHalf);
   MyDoubleLinkedListDestroy(&sortedFirstHalf);
   MyDoubleLinkedListDestroy(&sortedSecondHalf);
   return status;
}

BOOLEAN MyDoubleLinkedListSearchElement(PMY_DOUBLE_LINKED_LIST list, int element)
{
   BOOLEAN found;
   PNODE currentNode;

   currentNode = list->head;
   found = FALSE;

   while (currentNode != NULL && found == FALSE)
   {
      if (currentNode->data == element)
      {
         found = TRUE;
      }
      else
      {
         currentNode = currentNode->next;
      }
   }

   return found;
}

STATUS MyDoubleLinkedListPrint(PMY_DOUBLE_LINKED_LIST list, FILE* outputFile)
{
   STATUS status;
   PNODE current;
   int i;
   int err;

   
   err = 0;
   i = 0;
   status = ZERO_EXIT_STATUS;
   current = list->head;

   while (current != NULL)
   {
      err = fprintf_s(outputFile, "%d ", current->data);
      if (err < 0)
      {
         status = FILE_IO_ERROR;
         goto EXIT;
      }
      current = current->next;
   }

   err = fprintf_s(outputFile, "\n");
   if (err < 0)
   {
      status = FILE_IO_ERROR;
      goto EXIT;
   }

EXIT:
   return status;
}

int MyDoubleLinkedListLength(PMY_DOUBLE_LINKED_LIST list)
{
   return list->size;
}