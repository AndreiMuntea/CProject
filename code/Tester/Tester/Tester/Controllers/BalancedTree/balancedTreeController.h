#ifndef BALANCEDTREECONTROLLER_H
#define BALANCEDTREECONTROLLER_H


#define MAX_BALANCED_TREE_CAPACITY      10000000
#define MAX_BALANCED_TREE_STRUCTS       10
#define BALANCED_TREE_NOT_SET          -1

#include <mybalancedsearchtree.h>

#include "../../Parser/parser.h"

typedef struct _BALANCED_SEARCH_TREE_CONTROLLER
{
   PMY_BALANCED_SEARCH_TREE tree[MAX_BALANCED_TREE_STRUCTS];
   int currentBalancedSearchTree;
   int size;

}BALANCED_SEARCH_TREE_CONTROLLER, *PBALANCED_SEARCH_TREE_CONTROLLER;

/*
 * @Brief:   Creates a BALANCED_SEARCH_TREE_CONTROLLER
 * @Params:  treeController a PBALANCED_SEARCH_TREE_CONTROLLER*
 * @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
 *                   - NULL_POINTER if the treeController was NULL
 *                   - BAD_ALLOCATION if there wasn't enough memory
 */
STATUS BalancedSearchTreeControllerCreate(PBALANCED_SEARCH_TREE_CONTROLLER* treeController);

/*
* @Brief:   Destroys a BALANCED_SEARCH_TREE_CONTROLLER
* @Params:  treeController a PBALANCED_SEARCH_TREE_CONTROLLER*
* @Returns: void
*/
void BalancedSearchTreeControllerDestroy(PBALANCED_SEARCH_TREE_CONTROLLER* treeController);

/*
* @Brief:   Handle the tree insert command 
* @Params:  treeController a PBALANCED_SEARCH_TREE_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*                   - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_BALANCED_SEARCH_TREE defined
*                   - CAPACITY_LIMIT_REACHED if the current tree is full
*                   - INVALID_INPUT if there wasn't exactly one valid integer
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS BalancedTreeInsert(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser);

/*
* @Brief:   Handle the tree read command
* @Params:  treeController a PBALANCED_SEARCH_TREE_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*                   - STRUCTS_LIMIT_REACHED if there is no more space for another structure
*                   - INVALID_INPUT if there wasn't at least one valid integer
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS BalancedTreeRead(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser);

/*
* @Brief:   Handle the tree remove command
* @Params:  treeController a PBALANCED_SEARCH_TREE_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS: - ZERO_EXIT_STATUS if the operation was successful
*                   - NULL_POINTER if the treeController was NULL
*                   - BAD_ALLOCATION if there wasn't enough memory
*                   - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_BALANCED_SEARCH_TREE defined
*                   - INVALID_INPUT if there wasn't at least one valid integer
*                   - NOT_FOUND if the element doesn't exist
*                   - FILE_IO_ERROR if there was a read error
*/
STATUS BalancedTreeRemove(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser);

/*
* @Brief:   Handle the tree search command
* @Params:  treeController a PBALANCED_SEARCH_TREE_CONTROLLER*
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
STATUS BalancedTreeSearch(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser, FILE* outputFile);

/*
* @Brief:   Handle the tree goto command
* @Params:  treeController a PBALANCED_SEARCH_TREE_CONTROLLER*
*           parser a PPARSER
* @Returns: STATUS:  - ZERO_EXIT_STATUS if the operation was successful
*                    - NULL_POINTER if the treeController was NULL
*                    - BAD_ALLOCATION if there wasn't enough memory
*                    - CURRENT_STRUCTURE_UNDEFINED, if there is no MY_BALANCED_SEARCH_TREE defined
*                    - INVALID_INPUT if there wasn't at least one valid integer
*                    - INVALID_INDEX if the index was out of bounds
*                    - FILE_IO_ERROR if there was a read error
*/
STATUS BalancedTreeGoTo(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser);


#endif //BALANCEDTREECONTROLLER_H