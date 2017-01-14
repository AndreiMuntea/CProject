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

/*
* @Brief:   Creates a HEAP_CONTROLLER
* @Params:  heapController a PHEAP_CONTROLLER*
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS HeapControllerCreate(PHEAP_CONTROLLER* heapController);

/*
* @Brief:   Destroys a HEAP_CONTROLLER
* @Params:  heapController a PHEAP_CONTROLLER*
* @Returns: void
*/
void HeapControllerDestroy(PHEAP_CONTROLLER* heapController);

/*
* @Brief:   Handle the heap add command
* @Params:  heapController a PHEAP_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_HEAP defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
*                    - CAPACITY_LIMIT_REACHED if the current structure is full
*/
STATUS HeapInsert(PHEAP_CONTROLLER heapController, PPARSER parser);

/*
* @Brief:   Handle the heap read command
* @Params:  heapController a PHEAP_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*                   - STRUCTS_LIMIT_REACHED if there is no more space for another structure
*                   - INVALID_INPUT if there wasn't at least one valid integer
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS HeapRead(PHEAP_CONTROLLER heapController, PPARSER parser);

/*
* @Brief:   Handle the heap remove command
* @Params:  heapController a PHEAP_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*                   - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_HEAP defined
*                   - INVALID_INPUT if there wasn't at least one valid integer
*                   - NOT_FOUND if the element doesn't exist
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS HeapRemove(PHEAP_CONTROLLER heapController, FILE* outputFile);

/*
* @Brief:   Handle the heap goto command
* @Params:  heapController a PHEAP_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - INVALID_INDEX if the index was out of bounds
*/
STATUS HeapGoTo(PHEAP_CONTROLLER heapController, PPARSER parser);

#endif //HEAPCONTROLLER_H