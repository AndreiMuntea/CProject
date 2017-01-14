#ifndef MYBALANCEDSEARCHTREE_H
#define MYBALANCEDSEARCHTREE_H

#include "definitions.h"

typedef struct _TREE_NODE
{
   struct _TREE_NODE* leftChild;
   struct _TREE_NODE* rightChild;
   int height;
   int data;
}TREE_NODE, *PTREE_NODE;


typedef struct _MY_BALANCED_SEARCH_TREE
{
   PTREE_NODE root;
   int size;
}MY_BALANCED_SEARCH_TREE, *PMY_BALANCED_SEARCH_TREE;

/**
 * @Brief:   Creates a MY_BALACED_SEARCH_TREE
 * @Params:  tree    - a PMY_BALANCED_SEARCH_TREE*
 * @Returns: STATUS: - ZERO_EXIT_STATUS if the structure was successfully created
 *                   - NULL_POINTER if tree is NULL
 *                   - BAD_ALLOCATION if there wasn't enough memory 
 */
STATUS MyBalancedSearchTreeCreate(PMY_BALANCED_SEARCH_TREE* tree);

/**
 * @Brief:   Destroys a MY_BALACED_SEARCH_TREE
 * @Params:  tree - a PMY_BALANCED_SEARCH_TREE*
 * @Returns: void
 */
void MyBalancedSearchTreeDestroy(PMY_BALANCED_SEARCH_TREE* tree);

/**
 * @Brief:   Inserts an element in a MY_BALANCED_SEARCH_TREE
 * @Params:  tree    - a PMY_BALANCED_SEARCH_TREE
 *           element - an int, element to be inserted
 * @Returns: STATUS: - ZERO_EXIT_STATUS if the element was successfully inserted
 *                   - BAD_ALLOCATION if there wasn't enough memory
 * @Warning: If the element already exists, it is ignored.
 */
STATUS MyBalancedSearchTreeInsert(PMY_BALANCED_SEARCH_TREE tree, int element);

/**
 * @Brief:   Removes an element in a MY_BALANCED_SEARCH_TREE
 * @Params:  tree    - a PMY_BALANCED_SEARCH_TREE
 *           element - an int, element to be removed
 * @Returns: STATUS: - ZERO_EXIT_STATUS if the element was successfully removed
 *                   - NOT_FOUND if the element doesn't exists
 */
STATUS MyBalancedSearchTreeRemove(PMY_BALANCED_SEARCH_TREE tree, int element);

/**
 * @Brief:   Search an element in a MY_BALANCED_SEARCH_TREE
 * @Params:  tree    - a PMY_BALANCED_SEARCH_TREE
 *           element - an int, element to be searched
 * @Returns: BOOLEAN - TRUE   if the element was found
 *                   - FALSE  otherwise           
 */
BOOLEAN MyBalancedSearchTreeSearchElement(PMY_BALANCED_SEARCH_TREE tree, int element);

/**
 * @Brief:   Returns the number of elements currently in a MY_BALANCED_SEARCH_TREE
 * @Params:  tree  - a PMY_BALANCED_SEARCH_TREE
 * @Returns: int   - the number of elements in the given tree
 */
int MyBalancedSearchTreeSize(PMY_BALANCED_SEARCH_TREE tree);

#endif //MYBALANCEDSEARCHTREE_H