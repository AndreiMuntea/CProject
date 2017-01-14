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

/**
* @Brief:   Creates a MY_VECTOR
* @Params:  vector   - a PMY_VECTOR*
* @Returns: STATUS: - ZERO_EXIT_STATUS if the structure was successfully created
*                   - NULL_POINTER if hash is NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS MyVectorCreate(PMY_VECTOR* vector);

/**
* @Brief:   Destroys a MY_VECTOR
* @Params:  vector - a PMY_VECTOR*
* @Returns: void
*/
void MyVectorDestroy(PMY_VECTOR* vector);

/**
* @Brief:   Inserts an element in a PMY_VECTOR
* @Params:  vector   - a PMY_VECTOR
*           element - an int, element to be inserted
* @Returns: STATUS: - ZERO_EXIT_STATUS if the element was successfully inserted
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS MyVectorInsert(PMY_VECTOR vector, int element);

/**
* @Brief:   Returns the number of elements currently in a PMY_VECTOR
* @Params:  vector - a PMY_VECTOR
* @Returns: int   - the number of elements in the given vector
*/
int MyVectorLength(PMY_VECTOR vector);

/**
* @Brief:   Removes an element in a PMY_VECTOR
* @Params:  vector   - a PMY_VECTOR
*           position - an int, position of the element to be removed
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the element was successfully removed
*                    - INVALID_INDEX if the position is not between array bounds
*/
STATUS MyVectorRemovePosition(PMY_VECTOR vector, int position);

/**
* @Brief:   Removes elements in a PMY_VECTOR
* @Params:  vector   - a PMY_VECTOR
*           value    - an int, value  to be removed
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the element was successfully removed
*                    - INVALID_INDEX if there was no element with the given value in vector
*/
STATUS MyVectorRemoveValue(PMY_VECTOR vector, int value);

/**
* @Brief:   Get the element from a given position
* @Params:  vector   - a PMY_VECTOR
*           position - an int, the position of the element
*           element  - an int*, the result
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the heap is not empty
*                    - NULL_POINTER if element is NULL
*                    - INVALID_INDEX if the position is not between array bounds
*/
STATUS MyVectorGetElement(PMY_VECTOR vector, int position, int* element);

/**
* @Brief:   Set the value of an element from a given position
* @Params:  vector   - a PMY_VECTOR
*           position - an int, the position of the element
*           element  - an int, the new value result
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the heap is not empty
*                    - NULL_POINTER if element is NULL
*                    - INVALID_INDEX if the position is not between array bounds
*/
STATUS MyVectorSetElement(PMY_VECTOR vector, int position, int element);

/**
* @Brief:   Get the first entry of an element
* @Params:  vector   - a PMY_VECTOR
*           position - an int*, the position of the element
*           element  - an int, the given element
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the heap is not empty
*                    - NULL_POINTER if position is NULL
*                    - NOT_FOUND if the element doesn't exists
*/
STATUS MyVectorGetFirstEntry(PMY_VECTOR vector, int element, int* position);

/**
* @Brief:   Prints a vector
* @Params:  vector     - a PMY_VECTOR, the vector to be printed
*           outputFile - a FILE*
* @Returns: STATUS:    - ZERO_EXIT_STATUS if the printing operation was successful
*                      - FILE_IO_ERROR if there was an error at printing
*/
STATUS MyVectorPrint(PMY_VECTOR vector, FILE* file);


#endif //MYVECTOR_H_