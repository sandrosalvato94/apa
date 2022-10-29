#include "Cliente.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA 5





struct client
{
    char codice[LUNGHEZZA+1];
    int priorita;
};

CLIENTE ClienteSCAN()
{
    CLIENTE dato=malloc(sizeof(*dato));

    do
    {
        printf("\nInserisci il codice cliente: ");
        scanf("%s", dato->codice);
        if (strlen(dato->codice) != LUNGHEZZA)
        {
            printf("\nERRORE: Il codice alfanumerico deve essere di 5 caratteri.\n");
        }
    }
    while(strlen(dato->codice) != LUNGHEZZA);

    printf("\nInserisci il grado di priorita: ");
    scanf("%d", &dato->priorita);

    return dato;
}

void ClienteSHOW(CLIENTE dato)
{
    printf("\nCodice = %s", dato->codice);
    printf("\nPriorita = %d", dato->priorita);
}

void DeallocaCliente(CLIENTE dato)
{
    free(dato);
}

int GetKey(CLIENTE dato)
{
    return dato->priorita;
}

CLIENTE ClienteFSCAN(FILE *Puntatore_File)
{
    CLIENTE dato=malloc(sizeof(*dato));

    fscanf(Puntatore_File, "%s%d", dato->codice, &dato->priorita);
    return dato;
}
