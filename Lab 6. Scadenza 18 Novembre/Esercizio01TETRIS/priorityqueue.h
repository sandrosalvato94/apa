/*Liste che garantiscono l'estrazione dalla testa del valore massimo (key) possibile*/
#ifndef PRIORITYQUEUE_H_DEFINED
#define PRIORITYQUEUE_H_DEFINED
#include "item.h"

void StampaMenuPriorityQueue();
void MainPriorityQueue(int decisione, int *numero_studenti, ITEM **studente_testa, ITEM **studente_coda);
void Insert_PriorityQueue(ITEM **puttesta, ITEM **putcoda, ITEM *nuovo);
void Delete_PriorityQueue(ITEM **puttesta, ITEM **putcoda, int *numero_studenti);
void PriorityQueue_SHOW(ITEM *puttesta);
void Dealloca_PriorityQueue (ITEM *puttesta);

#endif

