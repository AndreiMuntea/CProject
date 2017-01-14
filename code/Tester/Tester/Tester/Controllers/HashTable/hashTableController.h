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

/*
* @Brief:   Creates a MY_HASHTABLE_CONTROLLER
* @Params:  hashController a PMY_HASHTABLE_CONTROLLER*
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS HashTableControllerCreate(PMY_HASHTABLE_CONTROLLER* hashController);

/*
* @Brief:   Destroys a MY_HASHTABLE_CONTROLLER
* @Params:  hashController a PMY_HASHTABLE_CONTROLLER*
* @Returns: void
*/
void HashTableControllerDestroy(PMY_HASHTABLE_CONTROLLER* hashController);

/*
* @Brief:   Handle the hash read command
* @Params:  hashController a PMY_HASHTABLE_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*                   - STRUCTS_LIMIT_REACHED if there is no more space for another structure
*                   - INVALID_INPUT if there wasn't at least one valid integer
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS HashTableRead(PMY_HASHTABLE_CONTROLLER hashController, PPARSER parser);

/*
* @Brief:   Handle the hash search command
* @Params:  hashController a PMY_HASHTABLE_CONTROLLER*
*           parser a PPARSER
*           outputFile a FILE*
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_BALANCED_SEARCH_TREE defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - FILE_IO_ERROR if there was a read/write error
* @Output: FOUND     - if the element was found
*          NOT_FOUND - otherwise
*/
STATUS HashTableSearch(PMY_HASHTABLE_CONTROLLER hashController, PPARSER parser, FILE* outputFile);

/*
* @Brief:   Handle the hash goto command
* @Params:  hashController a PMY_HASHTABLE_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - INVALID_INDEX if the index was out of bounds
*/
STATUS HashTableGoTo(PMY_HASHTABLE_CONTROLLER hashController, PPARSER parser);

#endif // HASHTABLECONTROLLER_H