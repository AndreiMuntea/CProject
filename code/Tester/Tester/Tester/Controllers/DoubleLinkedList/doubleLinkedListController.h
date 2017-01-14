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

/*
* @Brief:   Creates a DOUBLE_LINKED_LIST_CONTROLLER
* @Params:  listController a PDOUBLE_LINKED_LIST_CONTROLLER*
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS DoubleLinkedListControllerCreate(PDOUBLE_LINKED_LIST_CONTROLLER* listController);

/*
* @Brief:   Destroys a DOUBLE_LINKED_LIST_CONTROLLER
* @Params:  listController a PDOUBLE_LINKED_LIST_CONTROLLER*
* @Returns: void
*/
void DoubleLinkedListControllerDestroy(PDOUBLE_LINKED_LIST_CONTROLLER* listController);

/*
* @Brief:   Handle the list read command
* @Params:  listController a PDOUBLE_LINKED_LIST_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*                   - STRUCTS_LIMIT_REACHED if there is no more space for another structure
*                   - INVALID_INPUT if there wasn't at least one valid integer
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS ListRead(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser);

/*
* @Brief:   Handle the list goto command
* @Params:  listController a PDOUBLE_LINKED_LIST_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - INVALID_INDEX if the index was out of bounds
*/
STATUS ListGoTo(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser);

/*
* @Brief:   Handle the list print command
* @Params:  listController a listController*
*           outputFile a FILE*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_DOUBLE_LINKED_LIST defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
* @Output: the current list
*/
STATUS ListPrint(PDOUBLE_LINKED_LIST_CONTROLLER listController, FILE* outputFile);

/*
* @Brief:   Handle the list merge command
* @Params:  listController a listController*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_DOUBLE_LINKED_LIST defined
*                    - PREVIOUS_STRUCTURE_UNDEFINED, if the current structure is the first one
*                    - STRUCTS_LIMIT_REACHED if there is no more space for another structure
*/
STATUS ListMerge(PDOUBLE_LINKED_LIST_CONTROLLER listController);

/*
* @Brief:   Handle the list SORT command
* @Params:  listController a listController*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_DOUBLE_LINKED_LIST defined
*/
STATUS ListSort(PDOUBLE_LINKED_LIST_CONTROLLER listController);

/*
* @Brief:   Handle the list add command
* @Params:  listController a listController*
*           parser a PPARSER
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_DOUBLE_LINKED_LIST defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
*                    - CAPACITY_LIMIT_REACHED if the current structure is full
*/
STATUS ListAdd(PDOUBLE_LINKED_LIST_CONTROLLER listController, PPARSER parser);

#endif //DOUBLELINKEDLISTCONTROLLER_H