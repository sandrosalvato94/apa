#include "item.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct oggetto
{
    char *parola;
};

Item ITEMscan()
{
    Item item=NULL;
    char *tmp = NULL;

    printf("\nInserisci il dato: ");
    scanf("%s", tmp);

    item->parola = strdup(tmp);

    return (item);
}

