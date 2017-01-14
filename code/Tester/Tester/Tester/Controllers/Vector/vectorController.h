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

/*
* @Brief:   Creates a VECTOR_CONTROLLER
* @Params:  vectorController a PVECTOR_CONTROLLER*
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS VectorControllerCreate(PVECTOR_CONTROLLER* vectorController);

/*
* @Brief:   Destroys a VECTOR_CONTROLLER
* @Params:  vectorController a PVECTOR_CONTROLLER*
* @Returns: void
*/
void VectorControllerDestroy(PVECTOR_CONTROLLER* vectorController);

/*
* @Brief:   Handle the vector read command
* @Params:  vectorController a PVECTOR_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*                   - STRUCTS_LIMIT_REACHED if there is no more space for another structure
*                   - INVALID_INPUT if there wasn't at least one valid integer
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS VectorRead(PVECTOR_CONTROLLER vectorController, PPARSER parser);

/*
* @Brief:   Handle the vector print command
* @Params:  vectorController a PVECTOR_CONTROLLER*
*           outputFile a FILE*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_VECTOR defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
* @Output: the current vector
*/
STATUS VectorPrint(PVECTOR_CONTROLLER vectorController, FILE* outputFile);

/*
* @Brief:   Handle the vector goto command
* @Params:  vectorController a PVECTOR_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - INVALID_INDEX if the index was out of bounds
*/
STATUS VectorGoTo(PVECTOR_CONTROLLER vectorController, PPARSER parser);

/*
* @Brief:   Handle the vector length command
* @Params:  vectorController a PVECTOR_CONTROLLER*
*           parser a PPARSER
*           outputFile a FILE*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_VECTOR defined
*                    - FILE_IO_ERROR if there was a read/write error
* @Output: current vector's length
*/
STATUS VectorLength(PVECTOR_CONTROLLER vectorController, FILE* outputFile);

/*
* @Brief:   Handle the vector search command
* @Params:  vectorController a PVECTOR_CONTROLLER*
*           parser a PPARSER
*           outputFile a FILE*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_VECTOR defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
* @Output: element's first entry in vector, if the element exists
*          NOT_FOUND if the element doesn't exists
*/
STATUS VectorSearch(PVECTOR_CONTROLLER vectorController, PPARSER parser, FILE* outputFile);

/*
* @Brief:   Handle the vector remove command
* @Params:  vectorController a PVECTOR_CONTROLLER*
*           parser a PPARSER
*           outputFile a FILE*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_VECTOR defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
*                    - INVALID_INDEX if the index was out of bounds
*/
STATUS VectorRemovePosition(PVECTOR_CONTROLLER vectorController, PPARSER parser);

/*
* @Brief:   Handle the vector remove command
* @Params:  vectorController a PVECTOR_CONTROLLER*
*           parser a PPARSER
*           outputFile a FILE*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_VECTOR defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
*                    - NOT_FOUND if the given value wasn't found in current vector
*/
STATUS VectorRemoveValue(PVECTOR_CONTROLLER vectorController, PPARSER parser);

/*
* @Brief:   Handle the vector add command
* @Params:  vectorController a PVECTOR_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_VECTOR defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
*                    - CAPACITY_LIMIT_REACHED if the current structure is full
*/
STATUS VectorAdd(PVECTOR_CONTROLLER vectorController, PPARSER parser);

#endif // VECTORCONTROLLER_H