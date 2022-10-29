#include "PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#define LEFT(i) ((i*2) + 1)
#define RIGHT(i) ((i*2) + 2)
#define PARENT(i) ((i-1) / 2)
#define greater(a, b) (a>b)
#define less(a,b) (a<b)


struct coda
{
    int *coda_priorita;
    int dimensione;
    int dim_attuale;
};

PQ QueueInit(int n)
{
    int i;
    PQ Q = malloc(sizeof(*Q));
    Q->coda_priorita = malloc(n*sizeof(int)); //La mia coda a priorità è un vettore della lunghezza del numero dei vertici
    for(i=0; i<n; i++)
    {
        Q->coda_priorita[i] = -1;
    }
    Q->dimensione = n;
    Q->dim_attuale = 0;
    return Q;
}

void QueuePut(PQ Q, int n)
{
    int i;

    for(i=0; i<Q->dimensione; i++)
    {
        if(Q->coda_priorita[i] == -1)
        {
            Q->coda_priorita[i] = n;
            Q->dim_attuale++;
            break;
        }
    }
}

int QueueEmpty(PQ Q)
{
    return Q->dim_attuale;
}

int QueueExtr(PQ Q)
{
    int i;
    int tmp = Q->coda_priorita[0];

    for(i=0; i<=Q->dimensione; i++)
    {
        Q->coda_priorita[i] = Q->coda_priorita[i+1];
    }
    Q->coda_priorita[Q->dimensione-1] = -1;
    Q->dim_attuale--;

    return tmp;
}

void SwapPQ(PQ h, int n1, int n2)
{
    int tmp;
    tmp = h->coda_priorita[n1];
    h->coda_priorita[n1] =h->coda_priorita[n2];
    h->coda_priorita[n2] = tmp;
}

void Heapify(PQ h, int i)
{
    int l, r, largest;
    l = LEFT(i);
    r = RIGHT(i);
    if (l < h->dimensione && greater(h->coda_priorita[l], h->coda_priorita[i]))
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if (r<h->dimensione && greater(h->coda_priorita[r], h->coda_priorita[largest]))
    {
        largest = r;
    }
    if (largest != i)
    {
        SwapPQ(h, i, largest);
        Heapify(h, largest);
    }
    return;
}

void PQUEUEinsert (PQ Q, int item)
{
    int i;
    i  = Q->dim_attuale++;
	while (i>=1 && less(Q->coda_priorita[PARENT(i)], item))
    {
        Q->coda_priorita[i] = Q->coda_priorita[PARENT(i)];
		i = (i-1)/2;
    }
	Q->coda_priorita[i] = item;
	return;
}

int PQUEUEextractMax(PQ Q)
{
    int item;
    SwapPQ (Q, 0,Q->dim_attuale-1);
    item = Q->coda_priorita[Q->dim_attuale-1];
    Q->dim_attuale--;
    Heapify(Q, 0);
	return item;
}

void PQUEUEchange (PQ Q, int pos, int item)
{
	while (pos>=1 && less(Q->coda_priorita[PARENT(pos)], item))
    {
        Q->coda_priorita[pos] = Q->coda_priorita[PARENT(pos)];
		pos = (pos-1)/2;
    }
	Q->coda_priorita[pos] = item;
	Heapify(Q, pos);
	return;
}


int QueueExtrMin(PQ Q)
{
    int j;
    QueueExtr(Q);
    return j;
}
