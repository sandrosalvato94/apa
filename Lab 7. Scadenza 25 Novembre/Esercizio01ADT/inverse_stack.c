#include "inverse_stack.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

struct inverse_stack
{
    Item dato;
    int posizione;
    int testa;
    int coda;
};

void Acquisisci_capienza(int *massimo)
{
    printf("\nInserisci il numero massimo di elementi previsti: ");
    scanf("%d", massimo);
}

STACK Inizializza_coda(int capienza)
{
    STACK fifo;

    fifo = malloc(capienza*sizeof(STACK));

    return(fifo);
}

void StampaCardinalita(int cardinalita)
{
    printf("\nIl numero di elementi nello STACK e': %d", cardinalita);
}

void InversePUSH(STACK fifo,int *cardinalita)
{
    Item nuovo;


    nuovo = ITEMscan();
    fifo->dato = nuovo;
    fifo->posizione = *cardinalita+1;
    fifo->testa = 0;
    fifo->coda = *cardinalita+1;
    *cardinalita++;
}
