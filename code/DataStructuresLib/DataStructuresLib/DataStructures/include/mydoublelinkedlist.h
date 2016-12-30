#ifndef MYDOUBLELINKEDLIST_H
#define MYDOUBLELINKEDLIST_H

#include <stdio.h>

#include "definitions.h"

typedef struct _NODE
{
   struct _NODE* next;
   struct _NODE* previous;
   int data;
}NODE, *PNODE;

typedef struct _MY_DOUBLE_LINKED_LIST
{
   int size;
   PNODE head;
   PNODE tail;

}MY_DOUBLE_LINKED_LIST, *PMY_DOUBLE_LINKED_LIST;


STATUS MyDoubleLinkedListCreate(PMY_DOUBLE_LINKED_LIST* list);

void MyDoubleLinkedListDestroy(PMY_DOUBLE_LINKED_LIST* list);

STATUS MyDoubleLinkedListInsertAtHead(PMY_DOUBLE_LINKED_LIST list, int element);

STATUS MyDoubleLinkedListInsertAtTail(PMY_DOUBLE_LINKED_LIST list, int element);

STATUS MyDoubleLinkedListMerge(PMY_DOUBLE_LINKED_LIST firstList, PMY_DOUBLE_LINKED_LIST secondList, PMY_DOUBLE_LINKED_LIST* result);

STATUS MyDoubleLinkedListSort(PMY_DOUBLE_LINKED_LIST list, PMY_DOUBLE_LINKED_LIST* result);

BOOLEAN MyDoubleLinkedListSearchElement(PMY_DOUBLE_LINKED_LIST list, int element);

STATUS MyDoubleLinkedListPrint(PMY_DOUBLE_LINKED_LIST list, FILE* outputFile);

int MyDoubleLinkedListLength(PMY_DOUBLE_LINKED_LIST list);

#endif //MYDOUBLELINKEDLIST_H