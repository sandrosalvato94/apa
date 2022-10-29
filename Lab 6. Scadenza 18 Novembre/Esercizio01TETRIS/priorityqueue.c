#include "priorityqueue.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

void StampaMenuPriorityQueue()
{
    printf("\n***SELEZIONA L'OPERAZIONE DA ESEGUIRE***\n\n");
    printf("\n1 - Stampa il numero di studenti presenti.");
    printf("\n2 - Inserisci dati nuovo studente.");
    printf("\n3 - Elimina dati di uno studente.");
    printf("\n4 - Stampa PRIORITY QUEUE.");
    printf("\n0 - Termina");
}

void MainPriorityQueue(int decisione, int *numero_studenti, ITEM **studente_testa, ITEM **studente_coda)
{
    switch(decisione)
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
            Insert_PriorityQueue(studente_testa, studente_coda, studente_nuovo);
            *numero_studenti = *numero_studenti + 1;
            break;
        }
    case 3:
        {
            Delete_PriorityQueue(studente_testa, studente_coda, numero_studenti);
            break;
        }
    case 4:
        {
            PriorityQueue_SHOW(*studente_testa);
            break;
        }
    case 0:
        {
            Dealloca_PriorityQueue(*studente_testa);
            break;
        }
    default:
        {
            printf("\nComando non valido.\n");
            break;
        }

    }
}

void Insert_PriorityQueue(ITEM **puttesta, ITEM **putcoda, ITEM *nuovo)
{
    int trovato = 0;

    if (*puttesta == NULL)
    {
        *puttesta = *putcoda = nuovo;
    }
    else
    {
        ITEM *putprec = NULL, *putcorr = NULL;

        putprec = *puttesta;
        for (putcorr = *puttesta; putcorr!=NULL; putcorr = putcorr->succ)
        {
            if (nuovo->carriera.media > putcorr->carriera.media)
            {
                trovato = 1;
                if (putcorr == *puttesta)
                {
                    nuovo->succ = *puttesta;
                    *puttesta = nuovo;
                    break;
                }
                else
                {
                    nuovo->succ = putcorr;
                    putprec->succ = nuovo;
                    break;
                }
            }
            putprec = putcorr;
        }
        if (trovato == 0)
        {
            (*putcoda)->succ = nuovo;
            *putcoda = nuovo;
        }
    }
}

void Delete_PriorityQueue(ITEM **puttesta, ITEM **putcoda, int *numero_studenti)
{
    ITEM *tmp = NULL;

    if (*puttesta == NULL)
    {
        printf("\nLa coda a priorita' e' vuota. Non si puo' cancellare niente.\n");
        return;
    }
    else
    {
        if (*puttesta == *putcoda)
        {
            free(*puttesta);
            free(*putcoda);
            *numero_studenti = 0;
        }
        else
        {
            tmp = *puttesta;
            *puttesta = (*puttesta)->succ;
            free(tmp);
            *numero_studenti = *numero_studenti-1;
            printf("\nDati studente a massima priorita' eliminati.\n");
        }
    }
}

void PriorityQueue_SHOW(ITEM *puttesta)
{
    ITEM  *putcorr = NULL;

    if (puttesta == NULL)
    {
        printf("\nLa coda a priorita e' vuota.\n");
        return;
    }
    else
    {
        for (putcorr = puttesta; putcorr!=NULL; putcorr= putcorr->succ)
        {
            StructITEMshow(putcorr);
            printf("\n\n");
        }
    }
}

void Dealloca_PriorityQueue(ITEM *puttesta)
{
   if (puttesta == NULL)
   {
       return;
   }
   Dealloca_PriorityQueue(puttesta->succ);
   free(puttesta);
}

