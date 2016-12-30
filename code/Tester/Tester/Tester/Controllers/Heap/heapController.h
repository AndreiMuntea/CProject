#ifndef HEAPCONTROLLER_H
#define HEAPCONTROLLER_H

#define MAX_HEAP_CAPACITY      10000000
#define MAX_HEAP_STRUCTS       10
#define HEAP_NOT_SET           -1

#include <myheap.h>

#include "../../Parser/parser.h"

typedef struct _HEAP_CONTROLLER
{
   PMY_HEAP heap[MAX_HEAP_STRUCTS];
   int currentHeap;
   int size;

}HEAP_CONTROLLER, *PHEAP_CONTROLLER;

STATUS HeapControllerCreate(PHEAP_CONTROLLER* heapController);

void HeapControllerDestroy(PHEAP_CONTROLLER* heapController);

STATUS HeapInsert(PHEAP_CONTROLLER heapController, PPARSER parser);

STATUS HeapRead(PHEAP_CONTROLLER heapController, PPARSER parser);

STATUS HeapRemove(PHEAP_CONTROLLER heapController, FILE* outputFile);

#endif //HEAPCONTROLLER_H