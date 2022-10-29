#include "TabellaSimboli.h"
#define LUNGHEZZA 10
#define MAX_CARAT 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#define less(a, b) (strcmp(a, b) < 0)
#define greater(a, b) (strcmp(a, b) > 0)
#define eq(a, b) (strcmp(a, b) == 0)

struct NODO_TABELLA
{
    Item informazione;
    link succ;
};

struct symbletable
{
    link testa;
    link z;
    int num_dati;
};

TABELLA InizializzaTabella()
{
    TABELLA t = NULL;

    t = malloc(sizeof(*t));
    t->num_dati = 0;
    t->testa = t->z = NULL;
    return t;
}

int TabellaVuota(TABELLA t)
{
    return (t->num_dati == 0);
}

void InserimentoTabella(TABELLA t, Item item)
{
    t->testa = NEW(item, t->testa);
    t->num_dati++;
}

link NEW(Item item, link succ)
{
    link tmp = NULL;

    tmp = malloc(sizeof(*tmp));

    tmp->informazione = item;
    tmp->succ = succ;

    return tmp;
}

void Ricerca_Tabella(TABELLA t, key k)
{
    Ricerca(t->testa, k);
}

void Ricerca(link nodo_corrente, key k)
{
    if(nodo_corrente == NULL)
    {
        printf("\nNon ci sono dati.\n");
        return;
    }

    if(eq(Acquisisci_Chiave(nodo_corrente->informazione), k))
    {
        ITEMshow(nodo_corrente->informazione);
        return;
    }
    else
    {
        Ricerca(nodo_corrente->succ, k);
    }
}

link Cancella(link nodo_corrente, key k)
{
    if (nodo_corrente == NULL)
    {
        printf("\nNon e' possibile cancellare niente. La lista e' vuota.\n");
        return NULL;
    }
    if(eq(Acquisisci_Chiave(nodo_corrente->informazione), k))
    {
        link x = nodo_corrente->succ;
        free (nodo_corrente);
        return x;
    }
    nodo_corrente->succ = Cancella(nodo_corrente->succ, k);
    return (nodo_corrente);
}

void Cancella_in_Tabella(TABELLA t, key k)
{
    t->testa = Cancella(t->testa, k);
    if(t->testa != NULL)
    {
        t->num_dati--;
    }
}

void StampaTabella(TABELLA t)
{
    link nodo_corrente;

    nodo_corrente = t->testa;
    while (nodo_corrente!=NULL)
    {
        ITEMshow(nodo_corrente->informazione);
        nodo_corrente = nodo_corrente->succ;
    }
}

void DeallocaTabella(TABELLA t)
{
    Dealloca(t->testa);
}

void Dealloca(link nodo_corrente)
{
    if(nodo_corrente->succ == NULL)
    {
        free(nodo_corrente);
        return;
    }
    else
    Dealloca(nodo_corrente->succ);
}
