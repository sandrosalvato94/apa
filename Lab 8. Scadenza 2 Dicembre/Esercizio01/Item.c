#define LUNGHEZZA 10
#define MAX_CARAT 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define less(a, b) (strcmp(a, b) < 0)
#define greater(a, b) (strcmp(a, b) > 0)
#include "Item.h"

typedef struct data
{
    int giorno;
    int mese;
    int anno;
}tipo_data;

struct item
{
    char chiave[LUNGHEZZA+1];
    char nome[MAX_CARAT+1];
    char cognome[MAX_CARAT+1];
    tipo_data data;
};

void ITEMshow(Item dato)
{
    printf("\nCODICE: %s", dato->chiave);
    printf("\nNOME: %s", dato->nome);
    printf("\nCOGNOME: %s", dato->cognome);
    printf("\nDATA DI NASCITA: %2d/%2d/%4d\n", dato->data.giorno, dato->data.mese, dato->data.anno);
}

key Acquisisci_Chiave(Item item)
{
    return item->chiave;
}

Item Acquisisci_ITEM_File(FILE *Puntatore_File)
{
    Item dato=malloc(sizeof(Item));

    fscanf(Puntatore_File, "%s%s%s%d%*c%d%*c%d", dato->chiave, dato->nome, dato->cognome, &dato->data.giorno, &dato->data.mese, &dato->data.anno);

    return dato;
}

