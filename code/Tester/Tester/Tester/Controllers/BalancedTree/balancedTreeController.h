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

STATUS BalancedSearchTreeControllerCreate(PBALANCED_SEARCH_TREE_CONTROLLER* treeController);

void BalancedSearchTreeControllerDestroy(PBALANCED_SEARCH_TREE_CONTROLLER* treeController);

STATUS BalancedTreeInsert(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser);

STATUS BalancedTreeRead(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser);

STATUS BalancedTreeRemove(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser);

STATUS BalancedTreeSearch(PBALANCED_SEARCH_TREE_CONTROLLER treeController, PPARSER parser, FILE* outputFile);



#endif //BALANCEDTREECONTROLLER_H