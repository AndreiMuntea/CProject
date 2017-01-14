#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#define HASH_SLOTS            262144      // 2 ^ 18

#include "mydoublelinkedlist.h"

typedef struct _MY_HASHTABLE
{
   PMY_DOUBLE_LINKED_LIST table[HASH_SLOTS];
   int size;

}MY_HASHTABLE, *PMY_HASHTABLE;

/**
* @Brief:   Creates a MY_HASHTABLE
* @Params:  hash    - a PMY_HASHTABLE*
* @Returns: STATUS: - ZERO_EXIT_STATUS if the structure was successfully created
*                   - NULL_POINTER if hash is NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS MyHashTableCreate(PMY_HASHTABLE* hash);

/**
* @Brief:   Destroys a MY_HASHTABLE
* @Params:  hash - a PMY_HASHTABLE*
* @Returns: void
*/
void MyHashTableDestroy(PMY_HASHTABLE* hash);


/**
* @Brief:   Inserts an element
* @Params:  hash    - a PMY_HASHTABLE
*           element - an int, the element to be inserted
* @Returns: STATUS: - ZERO_EXIT_STATUS if the element was successfully inserted
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS MyHashTableInsert(PMY_HASHTABLE hash, int element);

/**
* @Brief:   Search an element in hash
* @Params:  hash    - a PMY_HASHTABLE
*           element - an int, the element to be searched
* @Returns: BOOLEAN - TRUE,  if the element was found
*                   - FALSE, otherwise
*/
BOOLEAN MyHashTableSearch(PMY_HASHTABLE hash, int element);

/**
* @Brief:   Returns the number of elements currently in a PMY_HASHTABLE
* @Params:  hash  - a PMY_HASHTABLE
* @Returns: int   - the number of elements in the given hash
*/
int MyHashTableLength(PMY_HASHTABLE hash);

#endif //MYHASHTABLE_H