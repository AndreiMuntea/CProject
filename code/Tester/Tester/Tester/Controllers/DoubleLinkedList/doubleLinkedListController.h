#ifndef DOUBLELINKEDLISTCONTROLLER_H
#define DOUBLELINKEDLISTCONTROLLER_H

#define MAX_LIST_CAPACITY      10000000
#define MAX_LIST_STRUCTS       10
#define LIST_NOT_SET           -1

#include <mydoublelinkedlist.h>

#include "../../Parser/parser.h"

typedef struct _DOUBLE_LINKED_LIST_CONTROLLER
{
   PMY_DOUBLE_LINKED_LIST lists[MAX_LIST_STRUCTS];
   int currentList;
   int size;

}DOUBLE_LINKED_LIST_CONTROLLER, *PDOUBLE_LINKED_LIST_CONTROLLER;

STATUS DoubleLinkedListControllerCreate(PDOUBLE_LINKED_LIST_CONTROLLER* listController);

void DoubleLinkedListControllerDestroy(PDOUBLE_LINKED_LIST_CONTROLLER* listController);

STATUS ListRead(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser);

STATUS ListGoTo(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser);

STATUS ListPrint(PDOUBLE_LINKED_LIST_CONTROLLER listController, FILE* outputFile);

STATUS ListMerge(PDOUBLE_LINKED_LIST_CONTROLLER listController);

STATUS ListSort(PDOUBLE_LINKED_LIST_CONTROLLER listController);

STATUS ListAdd(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser);

#endif //DOUBLELINKEDLISTCONTROLLER_H