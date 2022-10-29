#include "stack.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

void StampaMenuStack()
{
    printf("\n***SELEZIONE L'OPERAZIONE DA ESEGUIRE***\n\n");
    printf("\n1 - Stampa il numero di studenti.");
    printf("\n2 - Inserisci dati nuovo studente.");
    printf("\n3 - Elimina dati studente.");
    printf("\n4 - Stampa STACK.");
    printf("\n0 - Termina\n");
}

void MainStack(int decisione, int *numero_studenti,  ITEM **studente_testa)
{
    switch (decisione)
    {
    case 1:
        {
            printf("\nIl numero di studenti e' %d\n", *numero_studenti);
            break;
        }
    case 2:
        {
            ITEM  *studente_nuovo = NULL;
            studente_nuovo = (ITEM *)malloc(sizeof(ITEM));
            if (studente_nuovo == NULL)
            {
                printf("\nERRORE: Non c'e' abbastanza memoria disponibilie.\n");
                system("PAUSE");
                system("cls");
                return;
            }
            StructITEMscan(&studente_nuovo);
            PUSH(studente_testa, studente_nuovo);
            *numero_studenti = *numero_studenti + 1;
            break;
        }
    case 3:
        {
            POP(studente_testa, numero_studenti);
            break;
        }
    case 4:
        {
            STACKshow(*studente_testa);
            break;
        }
    case 0:
        {
            DeallocaSTACK(*studente_testa);
            *numero_studenti = 0;
            break;
        }
    default:
        {
            printf("\nComando non valido.\n");
            break;
        }
    }
}

void PUSH(ITEM **puttesta, ITEM *nuovo)
{
    if (*puttesta == NULL)
    {
        *puttesta = nuovo;
    }
    else
    {
        nuovo->succ = *puttesta;
        *puttesta = nuovo;
    }
}

void POP(ITEM **puttesta, int *numero_studenti)
{
    ITEM *putcorr;

    if(*puttesta == NULL)
    {
        printf("\nNon puoi eliminare niente. Lo STACK e' vuoto.\n");
    }
    else
    {
        if (((*puttesta)->succ) == NULL)
        {
            free(*puttesta);
            *puttesta = NULL;
            *numero_studenti = 0;
        }
        else
        {
            putcorr = *puttesta;
            *puttesta = (*puttesta)->succ;
            free(putcorr);
            *numero_studenti = *numero_studenti - 1;
        }
        printf("\nDati studente testa eliminati.\n");
    }
}

void STACKshow(ITEM *puttesta)
{
    ITEM *putcorr = NULL;

    if (puttesta == NULL)
    {
        printf("\nLo STACK e' vuoto.\n");
        return;
    }

    for (putcorr = puttesta; putcorr!=NULL; putcorr=putcorr->succ)
    {
        StructITEMshow(putcorr);
        printf("\n\n");
    }

}

void DeallocaSTACK(ITEM *puttesta)
{
    if (puttesta == NULL)
    {
        return;
    }

    DeallocaSTACK(puttesta->succ);
    free(puttesta);
}

