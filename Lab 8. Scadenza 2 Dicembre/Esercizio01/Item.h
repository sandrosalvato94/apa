#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED
#include <stdio.h>
#include <stdlib.h>


typedef struct item* Item;
typedef char* key;

void ITEMshow(Item dato);
key Acquisisci_Chiave(Item item);
Item Acquisisci_ITEM_File(FILE *Puntatore_File);

#endif
