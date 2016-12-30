#ifndef MYHEAP_H
#define MYHEAP_H

#include "myvector.h"

typedef struct _MY_HEAP
{
   PMY_VECTOR items;
   int size;

}MY_HEAP,*PMY_HEAP;

STATUS MyHeapCreate(PMY_HEAP* heap);

void MyHeapDestroy(PMY_HEAP* heap);

STATUS MyHeapInsert(PMY_HEAP heap, int element);

STATUS MyHeapRemove(PMY_HEAP heap);

int MyHeapLength(PMY_HEAP heap);

STATUS MyHeapGetMin(PMY_HEAP heap, int* element);

#endif //MYHEAP_H