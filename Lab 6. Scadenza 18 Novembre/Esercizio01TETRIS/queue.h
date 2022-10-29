/*Libreria per lista in cui l'inserzione è in coda e l'estrazione è in testa*/
#ifndef QUEUE_H_DEFINED
#define QUEUE_H_DEFINED
#include "item.h"

void StampaMenuQueue();
void MainQueue(int decisione, int *numero_studenti, ITEM **studente_testa, ITEM **studente_coda);
void InsertQueue(ITEM **puttesta, ITEM **putcoda, ITEM *nuovo);
void DeleteQueue(ITEM **puttesta, ITEM **putcoda, int *numero_studenti);
void QUEUEshow (ITEM *puttesta);
void DeallocaQueue (ITEM *puttesta);

#endif

