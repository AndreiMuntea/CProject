#include <stdlib.h>

#include "../include/myheap.h"


_inline int LeftChild(int node)
{
   return node * 2 + 1;
}

_inline int RightChild(int node)
{
   return node * 2 + 2;
}

_inline int Parent(int node)
{
   return (node - 1) / 2;
}

void HeapUp(PMY_HEAP heap, int position)
{
   int parent;
   int k;
   int parentElement;
   int element;
   
   k = position;
   parent = Parent(k);
   
   MyVectorGetElement(heap->items, k, &element);
   MyVectorGetElement(heap->items, parent, &parentElement);

   while (k > 0 && parentElement > element)
   {
      MyVectorSetElement(heap->items, k, parentElement);
      
      k = parent;
      parent = Parent(k);
      MyVectorGetElement(heap->items, parent, &parentElement);
   }

   MyVectorSetElement(heap->items, k, element);

}

void HeapDown(PMY_HEAP heap, int position)
{
   int k;
   int element;
   int size;
   
   int leftChildPosition;
   int rightChildPosition;
   int minChildPosition;
   
   int leftChildElement;
   int rightChildElement;
   int minChildElement;

   size = MyVectorLength(heap->items);
   k = position;
   MyVectorGetElement(heap->items, k, &element);

   leftChildPosition = LeftChild(k);
   rightChildPosition = RightChild(k);
   minChildPosition = LeftChild(k);

   while (minChildPosition <= size)
   {
      MyVectorGetElement(heap->items, leftChildPosition, &leftChildElement);
      if (leftChildPosition < size)
      {
         MyVectorGetElement(heap->items, rightChildPosition, &rightChildElement);
         if (leftChildElement > rightChildElement)
         {
            minChildPosition++;
         }
      }
      
      MyVectorGetElement(heap->items, minChildPosition, &minChildElement);
      if (minChildElement > element)
      {
         minChildPosition = size + 1;
      }
      else
      {
         MyVectorSetElement(heap->items, k, minChildElement);
         k = minChildPosition;
         leftChildPosition = LeftChild(k);
         rightChildPosition = RightChild(k);
         minChildPosition = LeftChild(k);
      }
   }

   MyVectorSetElement(heap->items, k, element);
}

STATUS MyHeapCreate(PMY_HEAP* heap)
{
   STATUS status;
   PMY_HEAP tempHeap;

   status = ZERO_EXIT_STATUS;
   tempHeap = NULL;

   if (NULL == heap)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempHeap = (PMY_HEAP)malloc(sizeof(MY_HEAP));
   if (NULL == tempHeap)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   status = MyVectorCreate(&(tempHeap->items));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   tempHeap->size = 0;
   *heap = tempHeap;

EXIT:
   if (!SUCCESS(status))
   {
      MyHeapDestroy(&tempHeap);
   }
   return status;
}

void MyHeapDestroy(PMY_HEAP* heap)
{
   PMY_HEAP tempHeap;

   tempHeap = NULL;

   if (NULL == heap)
   {
      goto EXIT;
   }

   if (NULL == *heap)
   {
      goto EXIT;
   }

   tempHeap = *heap;

   MyVectorDestroy(&(tempHeap->items));
   
   free(*heap);
   *heap = NULL;
EXIT:
   return;
}

STATUS MyHeapInsert(PMY_HEAP heap, int element)
{
   STATUS status;
   int size;

   status = ZERO_EXIT_STATUS;
   size = 0;

   status = MyVectorInsert(heap->items, element);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   size = MyVectorLength(heap->items);
   HeapUp(heap, size - 1);
   heap->size++;

EXIT:
   return status;
}

STATUS MyHeapRemove(PMY_HEAP heap)
{
   STATUS status;
   int size;
   int element;

   size = 0;
   status = ZERO_EXIT_STATUS;
   
   size = MyVectorLength(heap->items);
   
   status = MyVectorGetElement(heap->items, size - 1, &element);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   MyVectorSetElement(heap->items, 0, element);
   MyVectorRemovePosition(heap->items, size - 1);
   
   if (size - 1 == 0)
   {
      goto EXIT;
   }

   HeapDown(heap, 0);
   heap->size--;

EXIT:
   return status;
}

int MyHeapLength(PMY_HEAP heap)
{
   return heap->size;
}

STATUS MyHeapGetMin(PMY_HEAP heap, int* element)
{
   STATUS status;
   
   status = ZERO_EXIT_STATUS;
   
   if (NULL == element)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   status = MyVectorGetElement(heap->items, 0, element);


EXIT:
   return status;
}