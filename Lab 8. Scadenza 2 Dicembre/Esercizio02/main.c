#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "TabellaSimboli.h"
#define LUNGHEZZA 10
#define MAX_CARAT 30

void StampaMenu();
int AcquisisciDecisione();

int main(int argc, char *argv[])
{
   FILE *fp;
   int num_dati, decisione = 1, i=0;
   char k[LUNGHEZZA+1];
   TABELLA t = InizializzaTabella();

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

    while(i<num_dati)
    {
        Acquisisci_ITEM_File(fp);
        i++;
    }

    while (decisione!=0)
    {
        StampaMenu();
        AcquisisciDecisione();

        switch(decisione)
        {
        case 1:
            {
                Item nuovo = NULL;
                nuovo = malloc(sizeof(Item));
                nuovo = ITEMscan();
                InserimentoTabella(t, nuovo);
                system("PAUSE");
                system("cls");
                break;
            }
        case 2:
            {
                printf("\nInserisci chiave: ");
                scanf("%s", k);
                Cancella_in_Tabella(t, k);
                system("cls");
                break;
            }
        case 3:
            {
                printf("\nInserisci chiave: ");
                scanf("%s", k);
                Ricerca_Tabella(t, k);
                system("cls");
                break;
            }
        case 4:
            {
                StampaTabella(t);
                printf("\n");
                system("PAUSE");
                system("cls");
                break;
            }
        case 0:
            {
                DeallocaTabella(t);
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}

void StampaMenu()
{
    printf("\n***SELEZIONA UNA DELLE SEGUENTI OPERAZIONE***\n\n");
    printf("\n1 - Inserisci nuovi dati.\n");
    printf("2 - Cancella dati.\n");
    printf("3 - Modifica dati.\n");
    printf("4 - Stampa dati.\n");
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
