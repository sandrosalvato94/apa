#ifndef PRIORITY_QUEUE_H_DEFINED
#define PRIORITY_QUEUE_H_DEFINED

typedef struct coda *PQ;

PQ QueueInit(int n);
void QueuePut(PQ Q, int n);
int QueueEmpty(PQ Q);
int QueueExtr(PQ Q);
void Heapify(PQ h, int i);
int QueueExtrMin(PQ Q);
void PQUEUEchange (PQ Q, int pos, int item);
int PQUEUEextractMax(PQ Q);
void PQUEUEinsert (PQ Q, int item);
void Heapify(PQ h, int i);

#endif
