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

/*
* @Brief:   Creates a MY_INTERFACE to "communicate" with the file
* @Params:  myInterface  - a PMY_INTERFACE*
*           file         - a const char*, the name of the file
* @Returns: Status:      - ZERO_EXIT_STATUS, if the operation was successful
*                        - NULL_POINTER if parser or fileName were NULL
*                        - BAD_ALLOCATION if the wasn't enough memory
*                        - OPEN_FILE_ERROR if the file couldn't be opened in read mode
*/
STATUS InterfaceCreate(PMY_INTERFACE* myInterface, const char* file);

/*
 * @Brief:   Destroys a MY_INTERFACE
 * @Params:  myInterface - a PMY_INTERFACE*
 * @Returns: void
 */
void InterfaceDestroy(PMY_INTERFACE* myInterface);

/*
* @Brief:   Analyze the command read from file
* @Params:  myInterface  - a PMY_INTERFACE*
*           file         - a const char*, the command
* @Returns: Status:      - ZERO_EXIT_STATUS, if the operation was successful
*                        - BAD_ALLOCATION if the wasn't enough memory
*                        - OPEN_FILE_ERROR if the file couldn't be opened in read mode
*/
STATUS AnalyzeCommand(PMY_INTERFACE myInterface, const char* command);

/*
* @Brief:   Runs a single test
* @Params:  file    - a const char*, the name of the file
* @Returns: Status: - ZERO_EXIT_STATUS, if the operation was successful
*                   - BAD_ALLOCATION if the wasn't enough memory
*                   - OPEN_FILE_ERROR if the file couldn't be opened in read mode
*/
STATUS RunSingleTest(const char* fileName);

/*
* @Brief:   Runs a range of tests
* @Params:  startTest    - a const char*, the name of the first file
*           endTest      - a const char*, the name of the last file 
* @Returns: Status:      - ZERO_EXIT_STATUS, if the operation was successful
*                        - BAD_ALLOCATION if the wasn't enough memory
*                        - OPEN_FILE_ERROR if the file couldn't be opened in read mode
* @Warning: There should be all tests between startTest and endTest. If one is missing, the execution will stop.
*/
STATUS RunMultipleTests(const char* startTest, const char* endTest);

/*
* @Brief:   Runs all tests
* @Params:  -
* @Returns: Status:      - ZERO_EXIT_STATUS, if the operation was successful
*                        - BAD_ALLOCATION if the wasn't enough memory
*                        - OPEN_FILE_ERROR if the file couldn't be opened in read mode
* @Warning: There should be all tests. If one is missing, the execution will stop.
*/
STATUS RunAllTests();

#endif //INTERFACE_H