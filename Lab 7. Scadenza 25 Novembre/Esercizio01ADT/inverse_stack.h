#ifndef INVERSE_STACK_H_DEFINED
#define INVERSE_STACK_H_DEFINED

typedef struct inverse_stack *STACK;

void Acquisisci_capienza(int *massimo);
STACK Inizializza_coda(int capienza);
void StampaCardinalita(int cardinalita);
void InversePUSH(STACK fifo,int *cardinalita);

#endif
