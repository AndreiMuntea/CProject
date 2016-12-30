#ifndef MYVECTOR_H_
#define MYVECTOR_H_

#include <stdio.h>

#include "definitions.h"

typedef struct _MY_VECTOR
{
   int size;
   int capacity;
   int* items;
}MY_VECTOR, *PMY_VECTOR;

STATUS MyVectorCreate(PMY_VECTOR* vector);

void MyVectorDestroy(PMY_VECTOR* vector);

STATUS MyVectorInsert(PMY_VECTOR vector, int element);

int MyVectorLength(PMY_VECTOR vector);

STATUS MyVectorRemovePosition(PMY_VECTOR vector, int position);

STATUS MyVectorRemoveValue(PMY_VECTOR vector, int value);

STATUS MyVectorGetElement(PMY_VECTOR vector, int position, int* element);

STATUS MyVectorSetElement(PMY_VECTOR vector, int position, int element);

STATUS MyVectorGetFirstEntry(PMY_VECTOR vector, int element, int* position);

STATUS MyVectorPrint(PMY_VECTOR vector, FILE* file);


#endif //MYVECTOR_H_