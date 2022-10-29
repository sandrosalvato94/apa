#include "queue.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

void StampaMenuQueue()
{
    printf("\n***SELEZIONA L'OPERAZIONE DA ESEGUIRE***\n\n");
    printf("\n1 - Stampa il numero di studenti.");
    printf("\n2 - Inserisci dati del nuovo studente.");
    printf("\n3 - Elimina dati studente.");
    printf("\n4 - Stampa QUEUE.");
    printf("\n0 - Termina\n\n");
}

void MainQueue(int decisione, int *numero_studenti, ITEM **studente_testa, ITEM **studente_coda)
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
            InsertQueue(studente_testa, studente_coda, studente_nuovo);
            *numero_studenti = *numero_studenti + 1;
            break;
        }
    case 3:
        {
            DeleteQueue(studente_testa, studente_coda, numero_studenti);
            break;
        }
    case 4:
        {
            QUEUEshow(*studente_testa);
            break;
        }
    case 0:
        {
            DeallocaQueue(*studente_testa);
            break;
        }
    default:
        {
            printf("\nOperazione non valida.\n");
            break;
        }
    }

}

void InsertQueue(ITEM **puttesta, ITEM **putcoda, ITEM *nuovo)
{
    if (*puttesta == NULL)
    {
        *puttesta = *putcoda = nuovo;
    }
    else
    {
        (*putcoda)->succ = nuovo;
        *putcoda = nuovo;
    }
}


void DeleteQueue(ITEM **puttesta, ITEM **putcoda, int *numero_studenti)
{

    if (*puttesta == NULL)
    {
        printf("\nNon ci sono elementi in coda.\n");
    }
    else
    {
        if(((*puttesta)->succ) == NULL) // *puttesta = *putcoda
        {
            free(*puttesta);
            free(*putcoda);
            *puttesta = NULL;
            *putcoda = NULL;
            *numero_studenti = 0;
            printf("\nDati studente in testa eliminati.\n");
        }
        else
        {
            ITEM *putprec = NULL;
            putprec = *puttesta;
            *puttesta = (*puttesta)->succ;
            free(putprec);
            *numero_studenti = *numero_studenti - 1;
            printf("\nDati studente in testa eliminati.\n");
        }
    }
}

void QUEUEshow (ITEM *puttesta)
{
    ITEM *putcorr = NULL;

    if (puttesta == NULL)
    {
        printf("\nIl Queue e' vuoto.\n");
        return;
    }

    for (putcorr = puttesta; putcorr!=NULL; putcorr = putcorr->succ)
    {
        StructITEMshow(putcorr);
        printf("\n\n");
    }
}

void DeallocaQueue (ITEM *puttesta)
{
   if (puttesta==NULL)
   {
       return;
   }
   DeallocaQueue(puttesta->succ);
   free(puttesta);
}

