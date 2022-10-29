#ifndef TABELLA_DI_SIMBOLI_H_DEFINED
#define TABELLA_DI_SIMBOLI_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

typedef struct tab* TABELLA;

void Aggiungi_Dato_Tabella(FILE *Puntatore_File, int cardinalita, TABELLA t);
TABELLA InizilizzaTabella(int capienza);
void DeallocaTabella(TABELLA t);
void quicksort(TABELLA, int, int);
void Swap(TABELLA, int, int);
int Partizione(TABELLA, int, int);
void RicercaBinaria(TABELLA, int indice_inizio, int indice_fine, char key[]);

#endif

