/*Libreria per FIFO: estrazione ed inserzione dalla testa*/
#ifndef STACK_H_DEFINED
#define STACK_H_DEFINED
#include "Item.h"

void StampaMenuStack();
void MainStack(int decisione, int *num_studenti,  ITEM **studente_testa);
void PUSH(ITEM **puttesta, ITEM *nuovo);
void POP(ITEM **puttesta, int *numero_studenti);
void STACKshow(ITEM *puttesta);
void DeallocaSTACK(ITEM *puttesta);

#endif

