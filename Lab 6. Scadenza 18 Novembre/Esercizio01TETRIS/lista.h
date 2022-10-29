#ifndef LISTA_H_DEFINED
#define LISTA_H_DEFINED
#include "item.h"

void StampaMenuLista();
void MainLista(int decisione, int *num_studenti, ITEM **studente_testa, ITEM **studente_coda);
void ListaPUSH (ITEM **puttesta, ITEM **putcoda, ITEM **nuovo);
void Push_coda(ITEM **puttesta, ITEM **putcoda, ITEM **nuovo);
void Ricerca_Stampa(char *chiave, ITEM *puttesta);
void Ricerca_Elimina(char *chiave, ITEM **puttesta, ITEM **putcoda, int *Num_studenti);
void Elimina_da_lista(ITEM **putcorr, ITEM **putprec, ITEM **puttesta, ITEM **putcoda);
void StampaLista(ITEM *puttesta);
void DeallocaLista(ITEM *puttesta);

#endif


