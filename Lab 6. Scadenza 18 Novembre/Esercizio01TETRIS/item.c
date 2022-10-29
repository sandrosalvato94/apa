#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LUNGHEZZA 35

void StructITEMscan(ITEM **stud)
{
    ITEM *stud_corrente=NULL;

    stud_corrente = (ITEM*)malloc(sizeof(ITEM));

    printf("\nNOME: ");
    scanf("%s", stud_corrente->nome);
    printf("\nCOGNOME: ");
    scanf("%s", stud_corrente->cognome);
    printf("\nMATRICOLA: ");
    scanf("%s", stud_corrente->matricola);
    printf("\nNUMERO CREDITI: ");
    scanf("%d", &stud_corrente->carriera.crediti);
    printf("\nMEDIA: ");
    scanf("%f", &stud_corrente->carriera.media);
    stud_corrente->succ = NULL;

    *stud = stud_corrente;
}

void StructITEMshow(ITEM* stud_corrente)
{
    printf("\nNOME = %s", stud_corrente->nome);
    printf("\nCOGNOME = %s", stud_corrente->cognome);
    printf("\nMATRICOLA = %s", stud_corrente->matricola);
    printf("\nNUMERO CREDITI = %d", stud_corrente->carriera.crediti);
    printf("\nMEDIA = %.1f", stud_corrente->carriera.media);
}

char* RendiMinuscolo (char *chiave, int dim_chiave)
{
    int i=0;

    while(i<dim_chiave)
    {
        chiave[i] = tolower(chiave[i]);
        i++;
    }
    return(chiave);
}


