#include "Heap.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LUNGHEZZA 5


struct heap
{
    CLIENTE *a;
    int dimensione;
};

HEAP HeapInit(int max)
{
    HEAP PQ=malloc(sizeof(*PQ));
    PQ->a = malloc(max*sizeof(PQ->a));
    PQ->dimensione = 0;
    return PQ;
}

int EmptyHeap(HEAP PQ)
{
    return (PQ->dimensione == 0);
}

void HeapInsert(HEAP PQ)
{
    CLIENTE cliente = ClienteSCAN();
    if (EmptyHeap(PQ))
    {
        PQ->a[0] = cliente;
        PQ->dimensione = 1;
    }
    else
    {
        int i = PQ->dimensione++;
        key z = GetKey(cliente);

        while (i>=1 && less(PARENT(i), z))
        {
            PQ->a[i] = PQ->a[PARENT(i)];
            i = (i-1)/2;
        }
        PQ->a[i] = cliente;
    }
}

void Swap(HEAP PQ, int n1, int n2)
{
    CLIENTE tmp;

    tmp = PQ->a[n1];
    PQ->a[n1] = PQ->a[n2];
    PQ->a[n2] = tmp;
}

void Heapify(HEAP PQ, int i)
{
    int l,r,largest;

    l = LEFT(i);
    r = RIGHT(i);
    if (l<PQ->dimensione && less(GetKey(PQ->a[l]), GetKey(PQ->a[i])))
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if(r>PQ->dimensione && less(GetKey(PQ->a[r]), GetKey(PQ->a[largest])))
    {
        largest = r;
    }

    if(largest!=i)
    {
        Swap(PQ, i, largest);
        Heapify(PQ, largest);
    }
}

void HeapExMax(HEAP PQ)
{
    Swap(PQ, 0, PQ->dimensione-1);
    printf("Stiamo servendo il cliente:\n");
    ClienteSHOW(PQ->a[PQ->dimensione-1]);
    PQ->dimensione--;
    Heapify(PQ, 0);
}

void HeapInsertFile(FILE *Puntatore_File, HEAP PQ)
{
    CLIENTE cliente = ClienteFSCAN(Puntatore_File);
    if (EmptyHeap(PQ))
    {
        PQ->a[0] = cliente;
        PQ->dimensione = 1;
    }
    else
    {
        int i = PQ->dimensione++;
        key z = GetKey(cliente);

        while (i>=1 && less(PARENT(i), z))
        {
            PQ->a[i] = PQ->a[PARENT(i)];
            i = (i-1)/2;
        }
        PQ->a[i] = cliente;
    }
}

void HeapSHOW(HEAP PQ)
{
    int i;
    if(PQ->dimensione == 0)
    {
        printf("\nNon ci sono clienti in coda.\n");
        return;
    }
    for (i=0; i<PQ->dimensione; i++)
    {
        ClienteSHOW(PQ->a[i]);
        printf("\n");
    }
}

int HeapSIZE(HEAP PQ)
{
    return PQ->dimensione;
}

void DeallocaHeap(HEAP PQ)
{
    free(PQ->a);
    free(PQ);
}
