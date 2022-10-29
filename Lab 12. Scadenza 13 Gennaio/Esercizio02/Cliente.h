#ifndef CLIENTE_H_DEFINED
#define CLIENTE_H_DEFINED
#define less(A, B) (A<B)
#define greater(A, B) (A>B)
#include <stdio.h>
#include <stdlib.h>


typedef struct client *CLIENTE;
typedef int key;

CLIENTE ClienteSCAN();
void ClienteSHOW(CLIENTE dato);
void DeallocaCliente(CLIENTE dato);
int GetKey(CLIENTE dato);
CLIENTE ClienteFSCAN(FILE *Puntatore_File);



#endif
