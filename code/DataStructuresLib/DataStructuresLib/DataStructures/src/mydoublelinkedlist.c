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

void Append(PMY_DOUBLE_LINKED_LIST result, PNODE node)
{
   if(result->head == NULL)
   {
      result->head = node;
      result->tail = node;
      node->next = NULL;
      node->previous = NULL;
   }
   else
   {
      result->tail->next = node;
      node->previous = result->tail;
      node->next = NULL;
      result->tail = node;
   }
}

void ResetList(PMY_DOUBLE_LINKED_LIST list)
{
   list->head = NULL;
   list->tail = NULL;
}

PNODE PartitionList(PMY_DOUBLE_LINKED_LIST list, int len, PNODE start)
{
   PNODE nodeBegin;
   PNODE nodeEnd;

   nodeBegin = start;
   nodeEnd = start;

   while(start != NULL && len > 0)
   {
      nodeEnd = start;
      start = start->next;
      len--;
   }

   if(NULL != nodeEnd)
   {
      nodeEnd->next = NULL;
   }

   list->head = nodeBegin;
   list->tail = nodeEnd;

   return start;
}

void JoinLists(PMY_DOUBLE_LINKED_LIST firstList, PMY_DOUBLE_LINKED_LIST secondList)
{
   if (NULL == firstList->head)
   {
      firstList->head = secondList->head;
      firstList->tail = secondList->tail;
   }
   else
   {
      firstList->tail->next = secondList->head;
      secondList->head->previous = firstList->tail;
      firstList->tail = secondList->tail;
   }
}

void MergeListsInPlace(PMY_DOUBLE_LINKED_LIST list1, PMY_DOUBLE_LINKED_LIST list2, PMY_DOUBLE_LINKED_LIST result)
{
   PNODE currentFirst;
   PNODE currentSecond;
   PNODE tmp;

   currentFirst = list1->head;
   currentSecond = list2->head;
   tmp = NULL;

   while (currentFirst != NULL && currentSecond != NULL)
   {
      if(currentFirst->data < currentSecond->data)
      {
         tmp = currentFirst->next;
         Append(result, currentFirst);
         currentFirst = tmp;
      }
      else
      {
         tmp = currentSecond->next;
         Append(result, currentSecond);
         currentSecond = tmp;
      }
   }

   while(currentFirst != NULL)
   {
      tmp = currentFirst->next;
      Append(result, currentFirst);
      currentFirst = tmp;
   }

   while(currentSecond != NULL)
   {
      tmp = currentSecond->next;
      Append(result, currentSecond);
      currentSecond = tmp;
   }

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
   PMY_DOUBLE_LINKED_LIST tempList;
   MY_DOUBLE_LINKED_LIST firstHalf;
   MY_DOUBLE_LINKED_LIST secondHalf;
   MY_DOUBLE_LINKED_LIST merged;
   MY_DOUBLE_LINKED_LIST splitedList;
   PNODE current;

   int len;
   int listLength;

   len = 0;
   listLength = 0;
   status = ZERO_EXIT_STATUS;
   current = NULL;

   status = MyDoubleLinkedListCopy(list, &tempList);
   if(!SUCCESS(status))
   {
      goto EXIT;
   }

   listLength = MyDoubleLinkedListLength(tempList);
   len = 1;

   while(len < listLength)
   {
      current = tempList->head;
      ResetList(&splitedList);
      while(current != NULL)
      {
         ResetList(&firstHalf);
         ResetList(&secondHalf);
         ResetList(&merged);

         current = PartitionList(&firstHalf, len, current);
         current = PartitionList(&secondHalf, len, current);
         MergeListsInPlace(&firstHalf, &secondHalf, &merged);
         JoinLists(&splitedList, &merged);
      }
      tempList->head = splitedList.head;
      tempList->tail = splitedList.tail;
      len *= 2;
   }

   *result = tempList;

EXIT:
   if(!SUCCESS(status))
   {
      MyDoubleLinkedListDestroy(&tempList);
   }
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

STATUS MyDoubleLinkedListCopy(PMY_DOUBLE_LINKED_LIST list, PMY_DOUBLE_LINKED_LIST* result)
{
   STATUS status;
   PMY_DOUBLE_LINKED_LIST tempList;
   PNODE current;

   tempList = NULL;
   status = ZERO_EXIT_STATUS;
   current = NULL;

   if (NULL == result)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   status = MyDoubleLinkedListCreate(&tempList);
   if(!SUCCESS(status))
   {
      goto EXIT;
   }

   current = list->head;
   while(current!= NULL)
   {
      status = MyDoubleLinkedListInsertAtTail(tempList, current->data);
      if(!SUCCESS(status))
      {
         goto EXIT;
      }
      current = current->next;
   }

   *result = tempList;

EXIT:
   if(!SUCCESS(status))
   {
      MyDoubleLinkedListDestroy(&tempList);
   }
   return status;
}

int MyDoubleLinkedListLength(PMY_DOUBLE_LINKED_LIST list)
{
   return list->size;
}