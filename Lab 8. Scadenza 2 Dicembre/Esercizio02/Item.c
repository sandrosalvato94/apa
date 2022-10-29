#include "Item.h"
#define LUNGHEZZA 10
#define MAX_CARAT 30
#include <stdio.h>
#include <stdlib.h>

typedef struct data
{
    int giorno;
    int mese;
    int anno;
}tipo_data;

struct inf
{
    char chiave[LUNGHEZZA+1];
    char nome[MAX_CARAT+1];
    char cognome[MAX_CARAT+1];
    tipo_data data;
};

Item ITEMscan()
{
    Item tmp=malloc(sizeof(Item));

    printf("\nCODICE: ");
    scanf("%s", tmp->chiave);
    printf("\nNOME: ");
    scanf("%s", tmp->nome);
    printf("\nCOGNOME: ");
    scanf("%s", tmp->cognome);
    printf("\nGIORNO DI NASCITA: ");
    scanf("%d", &tmp->data.giorno);
    printf("\nMESE DI NASCITA: ");
    scanf("%d", &tmp->data.mese);
    printf("\nANNO DI NASCITA: ");
    scanf("%d", &tmp->data.anno);

    return tmp;
}

void ITEMshow(Item dato)
{
    printf("\nCODICE: %s", dato->chiave);
    printf("\nNOME: %s", dato->nome);
    printf("\nCOGNOME: %s", dato->cognome);
    printf("\nGIORNO DI NASCITA: %2d", dato->data.giorno);
    printf("\nMESE DI NASCITA: %2d",dato->data.mese);
    printf("\nANNO DI NASCITA: %4d",dato->data.anno);
}

key Acquisisci_Chiave(Item item)
{
    return item->chiave;
}

Item Acquisisci_ITEM_File(FILE *Puntatore_File)
{
    Item dato = malloc(sizeof(Item));

    fscanf(Puntatore_File, "%s%s%s%d%*c%d%*c%d", dato->chiave, dato->nome, dato->cognome, &dato->data.giorno, &dato->data.mese, &dato->data.anno);

    return dato;
}
