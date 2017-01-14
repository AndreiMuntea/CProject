#ifndef MYHEAP_H
#define MYHEAP_H

#include "myvector.h"

typedef struct _MY_HEAP
{
   PMY_VECTOR items;
   int size;

}MY_HEAP,*PMY_HEAP;

/**
* @Brief:   Creates a MY_HEAP
* @Params:  heap    - a PMY_HEAP*
* @Returns: STATUS: - ZERO_EXIT_STATUS if the structure was successfully created
*                   - NULL_POINTER if hash is NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
* @Warning: The structure created is a MinHeap, meaning the root will be the element with the smallest value
*/
STATUS MyHeapCreate(PMY_HEAP* heap);

/**
* @Brief:   Destroys a MY_HEAP
* @Params:  heap - a PMY_HEAP*
* @Returns: void
*/
void MyHeapDestroy(PMY_HEAP* heap);

/**
* @Brief:   Inserts an element in heap
* @Params:  heap    - a PMY_HEAP
*           element - an int, the element to be inserted
* @Returns: STATUS: - ZERO_EXIT_STATUS if the element was successfully inserted
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS MyHeapInsert(PMY_HEAP heap, int element);

/**
* @Brief:   Removes an element in a PMY_HEAP
* @Params:  heap    - a PMY_HEAP
*           element - an int, element to be removed
* @Returns: STATUS: - ZERO_EXIT_STATUS if the element was successfully removed
*                   - NOT_FOUND if the element doesn't exists
*/
STATUS MyHeapRemove(PMY_HEAP heap);

/**
* @Brief:   Returns the number of elements currently in a PMY_HEAP
* @Params:  heap  - a PMY_HEAP
* @Returns: int   - the number of elements in the given heap
*/
int MyHeapLength(PMY_HEAP heap);


/**
* @Brief:   Get the element with the smallest value
* @Params:  heap    - a PMY_HEAP
*           element - an int*, the result
* @Returns: STATUS: - ZERO_EXIT_STATUS if the heap is not empty
*                   - NULL_POINTER if element is NULL
*                   - NOT_FOUND if the heap is empty
*/
STATUS MyHeapGetMin(PMY_HEAP heap, int* element);

#endif //MYHEAP_H