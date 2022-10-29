#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA 25

struct dato
{
    int numero;
    char parola[LUNGHEZZA+1];
};

Item ITEMscan()
{
    Item data=malloc(sizeof(*data));
    printf("\nInserisci valore numerico: ");
    scanf("%d", &data->numero);
    printf("\nInserisci codice lungo al piu' 25 caratteri: ");
    scanf("%s", data->parola);
    return data;
}

void ITEMshow(Item d)
{
    printf("\nDato numerico: %d", d->numero);
    printf("\nDato alfanumerico: %s", d->parola);
}
