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


STATUS MyBalancedSearchTreeCreate(PMY_BALANCED_SEARCH_TREE* tree);

void MyBalancedSearchTreeDestroy(PMY_BALANCED_SEARCH_TREE* tree);

STATUS MyBalancedSearchTreeInsert(PMY_BALANCED_SEARCH_TREE tree, int element);

STATUS MyBalancedSearchTreeRemove(PMY_BALANCED_SEARCH_TREE tree, int element);

BOOLEAN MyBalancedSearchTreeSearchElement(PMY_BALANCED_SEARCH_TREE tree, int element);

int MyBalancedSearchTreeSize(PMY_BALANCED_SEARCH_TREE tree);

#endif //MYBALANCEDSEARCHTREE_H