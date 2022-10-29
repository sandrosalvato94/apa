#ifndef TABELLASIMBOLI_H_DEFINED
#define TABELLASIMBOLI_H_DEFINED
#include "Item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NODO_TABELLA* link;
typedef struct symbletable* TABELLA;
typedef char* key;

TABELLA InizializzaTabella();
int TabellaVuota(TABELLA t);
void InserimentoTabella(TABELLA t, Item item);
link NEW(Item item, link succ);
void Ricerca_Tabella(TABELLA t, key k);
void Ricerca(link nodo_corrente, key k);
void Cancella_in_Tabella(TABELLA t, key k);
link Cancella(link nodo_corrente, key k);
void StampaTabella(TABELLA t);
void DeallocaTabella(TABELLA t);
void Dealloca(link nodo_corrente);

#endif
