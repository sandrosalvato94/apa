#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct inf* Item;
typedef char* key;

Item ITEMscan();
void ITEMshow(Item dato);
key Acquisisci_Chiave(Item item);
Item Acquisisci_ITEM_File(FILE *Puntatore_File);

#endif
