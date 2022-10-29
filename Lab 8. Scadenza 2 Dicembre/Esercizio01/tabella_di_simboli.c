#include "tabella_di_simboli.h"
#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LUNGHEZZA 10
#define MAX_CARAT 30
#define less(a, b) (strcmp(a, b) < 0)
#define greater(a, b) (strcmp(a, b) > 0)
#define eq(a, b) (strcmp(a, b) == 0)

struct tab
{
    Item *vett;
};

void Aggiungi_Dato_Tabella(FILE *Puntatore_File, int cardinalita, TABELLA t)
{
    Item dato = malloc(sizeof(Item));
    dato = Acquisisci_ITEM_File(Puntatore_File);
    t->vett[cardinalita] = dato;
    ITEMshow(dato);
    printf("\n");
}

TABELLA InizilizzaTabella(int capienza)
{
    TABELLA t;

    t = malloc(sizeof(TABELLA));
    t->vett = malloc(capienza*sizeof(Item));

    if((t==NULL) || (t->vett==NULL))
    {
        printf("\nERRORE nell'allocazione della memoria.\n");
        return NULL;
    }

    return t;
}

void DeallocaTabella(TABELLA t)
{
    free(t->vett);
    free(t);
}


void quicksort(TABELLA t, int indice_sinistro, int indice_destro)
{
    int q;

    if (indice_destro<= indice_sinistro)
    {
        return;
    }

    q = Partizione(t, indice_sinistro, indice_destro);
    quicksort(t, indice_sinistro, q-1);
    quicksort(t, q+1, indice_destro);
    return;
}

void Swap(TABELLA t, int n1, int n2)
{
    Item temp;
    temp = t->vett[n1];
    t->vett[n1] = t->vett[n2];
    t->vett[n2] = temp;
    return;
}

int Partizione(TABELLA t, int indice_sinistro, int indice_destro)
{
    int i = indice_sinistro-1;
    int j = indice_destro;
    Item x = t->vett[indice_destro];
    for ( ; ; )
    {
        while(less(Acquisisci_Chiave(t->vett[++i]), Acquisisci_Chiave(x)));
        while(greater(Acquisisci_Chiave(t->vett[--j]), Acquisisci_Chiave(x)));
        if (j == indice_sinistro)
        {
            break;
        }
        if (i >= j)
        {
            break;
        }
        Swap(t, i, j);
    }
    Swap(t, i, indice_destro);
    return i;
}

void RicercaBinaria(TABELLA t, int indice_inizio, int indice_fine, char key[])
{
    int indice_medio = (indice_fine+indice_inizio)/2;

    while (indice_inizio!=indice_fine)
    {
         if (eq(Acquisisci_Chiave(t->vett[indice_medio]), key))
        {
            ITEMshow(t->vett[indice_medio]);
            break;
        }
        else
        {
            if(greater(Acquisisci_Chiave(t->vett[indice_medio]), key))
            {
                indice_inizio = indice_medio;
                indice_medio = (indice_inizio+indice_fine)/2;
            }
            else
            {
                if(less(Acquisisci_Chiave(t->vett[indice_medio]), key))
                {
                    indice_fine = indice_medio;
                    indice_medio = (indice_inizio+indice_fine)/2;
                }
            }
        }
    }
}

