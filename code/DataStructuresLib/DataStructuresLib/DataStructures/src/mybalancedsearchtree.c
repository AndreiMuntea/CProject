#include <stdlib.h>

#include "../include/mybalancedsearchtree.h"


void DestroyRoot(PTREE_NODE root)
{
   if (NULL == root)
   {
      goto EXIT;
   }

   DestroyRoot(root->leftChild);
   DestroyRoot(root->rightChild);

   free(root);
   root = NULL;

EXIT:
   return;
}

STATUS CreateTreeNode(PTREE_NODE* node, int element)
{
   STATUS status;
   PTREE_NODE tempNode;

   tempNode = NULL;
   status = ZERO_EXIT_STATUS;

   if (NULL == node)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempNode = (PTREE_NODE)malloc(sizeof(TREE_NODE));
   if (NULL == tempNode)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   tempNode->height = 1;
   tempNode->data = element;
   tempNode->leftChild = NULL;
   tempNode->rightChild = NULL;

   *node = tempNode;

EXIT:
   return status;
}

_inline int Height(PTREE_NODE node)
{
   return (NULL == node) ? 0 : node->height;
}

_inline int BalanceFactor(PTREE_NODE node)
{
   return Height(node->rightChild) - Height(node->leftChild);
}

_inline void FixHeight(PTREE_NODE node)
{
   int leftHeight;
   int rightHeight;

   leftHeight = Height(node->leftChild);
   rightHeight = Height(node->rightChild);
   node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

PTREE_NODE RotateRight(PTREE_NODE node)
{
   PTREE_NODE newRoot;

   newRoot = node->leftChild;
   node->leftChild = newRoot->rightChild;
   newRoot->rightChild = node;
   
   FixHeight(node);
   FixHeight(newRoot);

   return newRoot;
}

PTREE_NODE RotateLeft(PTREE_NODE node)
{
   PTREE_NODE newRoot;

   newRoot = node->rightChild;
   node->rightChild = newRoot->leftChild;
   newRoot->leftChild = node;

   FixHeight(node);
   FixHeight(newRoot);

   return newRoot;
}

PTREE_NODE Balance(PTREE_NODE node)
{
   FixHeight(node);

   if (BalanceFactor(node) == 2)
   {
      if (BalanceFactor(node->rightChild) < 0)
      {
         node->rightChild = RotateRight(node->rightChild);
       }
      return RotateLeft(node);
   }
   
   if (BalanceFactor(node) == -2)
   {
      if (BalanceFactor(node->leftChild) > 0)
      {
         node->leftChild = RotateLeft(node->leftChild);
      }
      return RotateRight(node);
   }

   return node;
}

PTREE_NODE FindMin(PTREE_NODE node)
{
   return (NULL == node->leftChild ? node : FindMin(node->leftChild));
}

PTREE_NODE Insert(PTREE_NODE root, PTREE_NODE node)
{
   if (root == NULL)
   {
      return node;
   }

   if (root->data > node->data)
   {
      root->leftChild = Insert(root->leftChild, node);
   }
   else
   {
      root->rightChild = Insert(root->rightChild, node);
   }

   return Balance(root);
}

BOOLEAN Exists(PTREE_NODE root, int key)
{
   if (NULL == root)
   {
      return FALSE;
   }
   if (root->data == key)
   {
      return TRUE;
   }

   if (root->data > key)
   {
      return Exists(root->leftChild, key);
   }
   
   return Exists(root->rightChild, key);
}

PTREE_NODE Remove(PTREE_NODE node, int key)
{
   PTREE_NODE min;
   PTREE_NODE temp;

   temp = NULL;
   min = NULL;

   if (NULL == node)
   {
      return node;
   }

   if (node->data > key)
   {
      node->leftChild = Remove(node->leftChild, key);
   }
   else if (node->data < key)
   {
      node->rightChild = Remove(node->rightChild, key);
   }
   else if (node->leftChild != NULL && node->rightChild != NULL)
   {
      min = FindMin(node->rightChild);
      node->data = min->data;
      node->rightChild = Remove(node->rightChild, min->data);
   }
   else
   {
      temp = node;
      if (NULL == node->leftChild && node->rightChild != NULL)
      {
         node = node->rightChild;
      }
      else if (NULL == node->rightChild && node->leftChild != NULL)
      {
         node = node->leftChild;
      }
      else
      {
         node = NULL;
      }
      free(temp);
   }

   if (NULL == node)
   {
      return NULL;
   }
   return Balance(node);
}


STATUS MyBalancedSearchTreeCreate(PMY_BALANCED_SEARCH_TREE* tree)
{
   STATUS status;
   PMY_BALANCED_SEARCH_TREE tempTree;

   tempTree = NULL;
   status = ZERO_EXIT_STATUS;

   if (NULL == tree)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempTree = (PMY_BALANCED_SEARCH_TREE)malloc(sizeof(MY_BALANCED_SEARCH_TREE));
   if (NULL == tempTree)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   tempTree->root = NULL;
   tempTree->size = 0;
   *tree = tempTree;

EXIT:
   return status;
}

void MyBalancedSearchTreeDestroy(PMY_BALANCED_SEARCH_TREE* tree)
{
   if (NULL == tree)
   {
      goto EXIT;
   }

   if (NULL == *tree)
   {
      goto EXIT;
   }

   DestroyRoot((*tree)->root);

   free(*tree);
   *tree = NULL;

EXIT:
   return;
}

STATUS MyBalancedSearchTreeInsert(PMY_BALANCED_SEARCH_TREE tree, int element)
{
   STATUS status;
   PTREE_NODE node;

   status = ZERO_EXIT_STATUS;
   node = NULL;

   status = CreateTreeNode(&node, element);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   tree->root = Insert(tree->root, node);
   tree->size++;

EXIT:
   return status;
}

BOOLEAN MyBalancedSearchTreeSearchElement(PMY_BALANCED_SEARCH_TREE tree, int element)
{
   return Exists(tree->root, element);
}

STATUS MyBalancedSearchTreeRemove(PMY_BALANCED_SEARCH_TREE tree, int element)
{
   STATUS status;

   status = ZERO_EXIT_STATUS;

   if (Exists(tree->root, element) == FALSE)
   {
      status = ITEM_NOT_FOUND;
      goto EXIT;
   }

   tree->root = Remove(tree->root, element);
   tree->size--;

EXIT:
   return status;
}

int MyBalancedSearchTreeSize(PMY_BALANCED_SEARCH_TREE tree)
{
   return tree->size;
}