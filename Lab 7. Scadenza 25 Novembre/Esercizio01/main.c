#include <stdio.h>
#include <stdlib.h>
#include "itemADT.h"
#include "item_quasiADT.h"
#include "inverseSTACK_ADT.h"
#include "inverseSTACK_quasiADT.h"

void StampaMenu();
int AcquisisciDecisione();

int main()
{
    int decisione = 1;

    while (decisione!=0)
    {
        StampaMenu();
        decisione = AcquisisciDecisione();

        switch (decisione)
        {
        case 1:
            {
                break;
            }
        case 2:
            {
                break;
            }
        case 3:
            {
                break;
            }
        case 4:
            {
                break;
            }
        case 5:
            {
                break;
            }
        case 6:
            {
                break;
            }
        case 7:
            {
                break;
            }
        case 0:
            {
                break;
            }
        default:
            {
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}

void StampaMenu()
{
    printf("***SELEZIONA UNA DELLE SEGUENTI OPERAZIONI***\n\n");
    printf("\n1 - Crea nuova struttura dati.");
    printf("\n2 - Visualizza numero di dati salvati.");
    printf("\n3 - Inserisci nuovo dato in coda.");
    printf("\n4 - Estrai dato dalla coda.");
    printf("\n5 - Stampa tutti i dati.");
    printf("\n6 - Salva dati su un file.");
    printf("\n7 - Carica dati da file.");
    printf("\n0 - Termina.\n");
}

int AcquisisciDecisione()
{
    int a;
    printf("\nInserisci operazione: ");
    scanf("%d", &a);
    return a;
}
