#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#define LUNGHEZZA 10
#include "tabella_di_simboli.h"

void StampaMenu();
int AcquisisciDecisione();

int main(int argc, char *argv[])
{
    FILE *fp;
    int num_dati, i=0;
    int decisione = 0;
    char k[LUNGHEZZA+1];
    TABELLA t=NULL;

    if (argc!=2)
    {
        printf("\nERRORE: numero di parametri errati da linea di comando.\n");
        return EXIT_FAILURE;
    }

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura.\n", argv[2]);
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &num_dati);

    t = InizilizzaTabella(num_dati);

    while (i<num_dati)
    {
        Aggiungi_Dato_Tabella(fp, i, t);
        i++;
    }
    fclose(fp);

    quicksort(t, 0, num_dati-1);

    while (decisione!=0)
    {
        StampaMenu();
        AcquisisciDecisione();

        switch(decisione)
        {
        case 1:
            {
                printf("\nInserisci chiave di ricerca: ");
                scanf("%s", k);
                RicercaBinaria(t, 0, num_dati-1, k);
                system("PAUSE");
                system("cls");
                break;
            }
        case 0:
            {
                DeallocaTabella(t);
            }
        }
    }

    return EXIT_SUCCESS;
}

void StampaMenu()
{
    printf("\n***SELEZIONA UNA DELLE SEGUENTI OPERAZIONE***\n\n");
    printf("\n1 - Effettua ricerca inserendo il codice.\n");
    printf("0 - Termina.");
    printf("\n\n");
}

int AcquisisciDecisione()
{
    int decisione;

    printf("\nSeleziona: ");
    scanf("%d", &decisione);

    return decisione;
}
