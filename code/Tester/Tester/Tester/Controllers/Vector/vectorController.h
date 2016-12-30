#ifndef VECTORCONTROLLER_H
#define VECTORCONTROLLER_H

#define MAX_VECTOR_CAPACITY    10000000
#define MAX_VECTOR_STRUCTS     10
#define VECTOR_NOT_SET         -1

#include <myvector.h>

#include "../../Parser/parser.h"

typedef struct _VECTOR_CONTROLLER
{
   PMY_VECTOR vectors[MAX_VECTOR_STRUCTS];
   int currentVector;
   int size;

}VECTOR_CONTROLLER, *PVECTOR_CONTROLLER;

STATUS VectorControllerCreate(PVECTOR_CONTROLLER* vectorController);

void VectorControllerDestroy(PVECTOR_CONTROLLER* vectorController);

STATUS VectorRead(PVECTOR_CONTROLLER vectorController, PPARSER parser);

STATUS VectorPrint(PVECTOR_CONTROLLER vectorController, FILE* outputFile);

STATUS VectorGoTo(PVECTOR_CONTROLLER vectorController, PPARSER parser);

STATUS VectorLength(PVECTOR_CONTROLLER vectorController, FILE* outputFile);

STATUS VectorSearch(PVECTOR_CONTROLLER vectorController, PPARSER parser, FILE* outputFile);

STATUS VectorRemovePosition(PVECTOR_CONTROLLER vectorController, PPARSER parser);

STATUS VectorRemoveValue(PVECTOR_CONTROLLER vectorController, PPARSER parser);

STATUS VectorAdd(PVECTOR_CONTROLLER vectorController, PPARSER parser);

#endif // VECTORCONTROLLER_H