#ifndef INTERFACE_H
#define INTERFACE_H

#include "../Controllers/Vector/vectorController.h"
#include "../Controllers/DoubleLinkedList/doubleLinkedListController.h"
#include "../Controllers/HashTable/hashTableController.h"
#include "../Controllers/Heap/heapController.h"
#include "../Controllers/BalancedTree/balancedTreeController.h"

#include "../Controllers/controllerStatuses.h"

typedef struct _MY_INTERFACE
{
   PVECTOR_CONTROLLER vectorController;
   PDOUBLE_LINKED_LIST_CONTROLLER listController;
   PMY_HASHTABLE_CONTROLLER hashController;
   PHEAP_CONTROLLER heapController;
   PBALANCED_SEARCH_TREE_CONTROLLER treeController;

   PPARSER parser;
   FILE* outputFile;

}MY_INTERFACE, *PMY_INTERFACE;

STATUS InterfaceCreate(PMY_INTERFACE* myInterface, const char* file);

void InterfaceDestroy(PMY_INTERFACE* myInterface);

STATUS AnalyzeCommand(PMY_INTERFACE myInterface, const char* command);

STATUS RunSingleTest(const char* fileName);

#endif //INTERFACE_H