#ifndef HASHTABLECONTROLLER_H
#define HASHTABLECONTROLLER_H

#define MAX_HASH_CAPACITY      10000000
#define MAX_HASH_STRUCTS       10
#define HASH_NOT_SET           -1

#include <myhashtable.h>

#include "../../Parser/parser.h"

typedef struct _MY_HASHTABLE_CONTROLLER
{
   PMY_HASHTABLE hash[MAX_HASH_STRUCTS];
   int currentHash;
   int size;
}MY_HASHTABLE_CONTROLLER, *PMY_HASHTABLE_CONTROLLER;

STATUS HashTableControllerCreate(PMY_HASHTABLE_CONTROLLER* hashController);

void HashTableControllerDestroy(PMY_HASHTABLE_CONTROLLER* hashController);

STATUS HashTableRead(PMY_HASHTABLE_CONTROLLER hashController, PPARSER parser);

STATUS HashTableSearch(PMY_HASHTABLE_CONTROLLER hashController, PPARSER parser, FILE* outputFile);

#endif // HASHTABLECONTROLLER_H