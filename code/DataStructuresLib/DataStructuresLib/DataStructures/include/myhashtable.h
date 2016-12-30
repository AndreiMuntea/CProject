#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#define HASH_SLOTS            262144      // 2 ^ 18

#include "mydoublelinkedlist.h"

typedef struct _MY_HASHTABLE
{
   PMY_DOUBLE_LINKED_LIST table[HASH_SLOTS];
   int size;

}MY_HASHTABLE, *PMY_HASHTABLE;


STATUS MyHashTableCreate(PMY_HASHTABLE* hash);

void MyHashTableDestroy(PMY_HASHTABLE* hash);

STATUS MyHashTableInsert(PMY_HASHTABLE hash, int element);

BOOLEAN MyHashTableSearch(PMY_HASHTABLE hash, int element);

int MyHashTableLength(PMY_HASHTABLE hash);

#endif //MYHASHTABLE_H