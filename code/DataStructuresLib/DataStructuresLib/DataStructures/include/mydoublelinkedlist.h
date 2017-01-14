#ifndef MYDOUBLELINKEDLIST_H
#define MYDOUBLELINKEDLIST_H

#include <stdio.h>

#include "definitions.h"

typedef struct _NODE
{
   struct _NODE* next;
   struct _NODE* previous;
   int data;
}NODE, *PNODE;

typedef struct _MY_DOUBLE_LINKED_LIST
{
   int size;
   PNODE head;
   PNODE tail;

}MY_DOUBLE_LINKED_LIST, *PMY_DOUBLE_LINKED_LIST;

/**
* @Brief:   Creates a MY_DOUBLE_LINKED_LIST
* @Params:  list    - a PMY_DOUBLE_LINKED_LIST*
* @Returns: STATUS: - ZERO_EXIT_STATUS if the structure was successfully created
*                   - NULL_POINTER if list is NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS MyDoubleLinkedListCreate(PMY_DOUBLE_LINKED_LIST* list);

/**
* @Brief:   Destroys a MY_DOUBLE_LINKED_LIST
* @Params:  list - a PMY_DOUBLE_LINKED_LIST*
* @Returns: void
*/
void MyDoubleLinkedListDestroy(PMY_DOUBLE_LINKED_LIST* list);

/**
 * @Brief:   Inserts an element in front of a list
 * @Params:  list    - a PMY_DOUBLE_LINKED_LIST
 *           element - an int, the element to be inserted
 * @Returns: STATUS: - ZERO_EXIT_STATUS if the element was successfully inserted
 *                   - BAD_ALLOCATION if there wasn't enough memory
 */
STATUS MyDoubleLinkedListInsertAtHead(PMY_DOUBLE_LINKED_LIST list, int element);

/**
* @Brief:   Inserts an element at the tail of a list
* @Params:  list    - a PMY_DOUBLE_LINKED_LIST
*           element - an int, the element to be inserted
* @Returns: STATUS: - ZERO_EXIT_STATUS if the element was successfully inserted
*                   - BAD_ALLOCATION if there wasn't enough memory
*/
STATUS MyDoubleLinkedListInsertAtTail(PMY_DOUBLE_LINKED_LIST list, int element);

/**
 * @Brief:   Merges two lists
 * @Params:  firstList  - a PMY_DOUBLE_LINKED_LIST, first given list
 *           secondList - a PMY_DOUBLE_LINKED_LIST, second given list
 *           result     - a PMY_DOUBLE_LINKED_LIST* , the result of merge
 * @Returns: STATUS:    - ZERO_EXIT_STATUS if the merge was successful
 *                      - NULL_POINTER if result is NULL
 *                      - BAD_ALLOCATION if there wasn't enough memory
 * @Warning: The two given lists should be sorted. If not, the behaviour is not defined
 */
STATUS MyDoubleLinkedListMerge(PMY_DOUBLE_LINKED_LIST firstList, PMY_DOUBLE_LINKED_LIST secondList, PMY_DOUBLE_LINKED_LIST* result);

/**
 * @Brief:   Sorts a given list
 * @Params:  list       - a PMY_DOUBLE_LINKED_LIST, the list to be sorted
 *           result     - a PMY_DOUBLE_LINKED_LIST*, the result of sorting
 * @Returns: STATUS:    - ZERO_EXIT_STATUS if the sort operation was successful
 *                      - NULL_POINTER if result is NULL
 *                      - BAD_ALLOCATION if there wasn't enough memory
 * @Warning: It isn't an in-place sorting. The list will be copied and the copy will be sorted.
 */
STATUS MyDoubleLinkedListSort(PMY_DOUBLE_LINKED_LIST list, PMY_DOUBLE_LINKED_LIST* result);

/**
 * @Brief:   Search an element in list
 * @Params:  list    - a PMY_DOUBLE_LINKED_LIST
 *           element - an int, the element to be searched
 * @Returns: BOOLEAN - TRUE,  if the element was found
 *                   - FALSE, otherwise
 */
BOOLEAN MyDoubleLinkedListSearchElement(PMY_DOUBLE_LINKED_LIST list, int element);

/**
 * @Brief:   Prints a list
 * @Params:  list       - a PMY_DOUBLE_LINKED_LIST, the list to be printed
 *           outputFile - a FILE*
 * @Returns: STATUS:    - ZERO_EXIT_STATUS if the printing operation was successful
 *                      - FILE_IO_ERROR if there was an error at printing     
 */
STATUS MyDoubleLinkedListPrint(PMY_DOUBLE_LINKED_LIST list, FILE* outputFile);

/**
 * @Brief:   Makes a copy of a given list
 * @Params:  list    - a PMY_DOUBLE_LINKED_LIST, the list to be copied
 *           result  - a PMY_DOUBLE_LINKED_LIST*, a copy of a given list
 * @Returns: STATUS: - ZERO_EXIT_STATUS if the copy operation was successful
 *                   - NULL_POINTER if the result was NULL
 *                   - BAD_ALLOCATION if there wasn't enough memory
 */
STATUS MyDoubleLinkedListCopy(PMY_DOUBLE_LINKED_LIST list, PMY_DOUBLE_LINKED_LIST* result);

/**
* @Brief:   Returns the number of elements currently in a PMY_DOUBLE_LINKED_LIST
* @Params:  list  - a PMY_DOUBLE_LINKED_LIST
* @Returns: int   - the number of elements in the given list
*/
int MyDoubleLinkedListLength(PMY_DOUBLE_LINKED_LIST list);

#endif //MYDOUBLELINKEDLIST_H