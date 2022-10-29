#ifndef HEAP_H_DEFINED
#define HEAP_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#define LEFT(i) ((i*2) + 1)
#define RIGHT(i) ((i*2) + 2)
#define PARENT(i) ((i-1) / 2)

typedef struct heap *HEAP;
typedef int key;

HEAP HeapInit(int max);
int EmptyHeap(HEAP PQ);
void HeapInsert(HEAP PQ);
void HeapExMax(HEAP PQ);
void HeapInsertFile(FILE *Puntatore_File, HEAP PQ);
void HeapSHOW(HEAP PQ);
int HeapSIZE(HEAP PQ);
void Heapify(HEAP PQ, int i);
void DeallocaHeap(HEAP PQ);

#endif
