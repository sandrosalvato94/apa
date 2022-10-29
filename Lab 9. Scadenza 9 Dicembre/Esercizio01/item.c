#include "item.h"
#define LUNGHEZZA 20
#include <stdio.h>
#include <stdlib.h>

struct ele
{
    char oggetto[LUNGHEZZA+1];
    float peso;
    int importanza;
};

Item* InizializzaItem(int capienza)
{
    Item *v;

    v = (Item*)malloc(capienza*sizeof(Item));
    if(v == NULL)
    {
        printf("\nERRORE: Non c'e' abbastanza memoria disponibile.\n");
        return NULL;
    }
    return v;
}

/*Item* SalvaItem_File(FILE *Puntatore_file, int capienza)
{
    Item *v=InizializzaItem(capienza);
    int i=0;
    if (v!=NULL)
    {
        while (i<capienza)
        {
            fscanf(Puntatore_file, "%s%f%d", v[i]->oggetto, &v[i]->peso, &v[i]->importanza);
            i++;
        }
        return v;
    }
    return NULL;
}*/
