#include <stdio.h>
#include "lista.h"
#include "item.h"
#include <stdlib.h>
#define LUNGHEZZA 35
#include <string.h>

void StampaMenuLista()
{
    printf("\n***SELEZIONE L'OPERAZIONE DA COMPIERE***\n\n");
    printf("\n1 - Visualizza il numero di studenti.");
    printf("\n2 - Inserisci in testa."); /*PUSH*/
    printf("\n3 - Inserisci in coda.");
    printf("\n4 - Ricerca tramite l'utilizzo di una parola chiave.");
    printf("\n5 - Cancellazione tramite l'utilizzo di una parola chiave.");
    printf("\n6 - Stampa la lista.");
    printf("\n0 - Termina.");
}

void MainLista(int decisione, int *num_studenti,  ITEM **studente_testa, ITEM **studente_coda)
{
    //ITEM  *studente_nuovo = NULL;
    //studente_nuovo = (ITEM *)malloc(sizeof(ITEM));

    char chiave_ricerca[LUNGHEZZA+1];

    switch (decisione)
    {
    case 1:
        {
            printf("\nIl numero di studenti attuali e': %d\n", *num_studenti);
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
           ListaPUSH(studente_testa, studente_coda, &studente_nuovo);
           *num_studenti = *num_studenti +1;
           break;
        }
    case 3:
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
            Push_coda(studente_testa, studente_coda, &studente_nuovo);
            *num_studenti = *num_studenti +1;
            break;
        }
    case 4:
        {
            if (*studente_testa == NULL)
            {
                printf("\nLa lista e' vuota, non si puo' effettuare alcuna ricerca.\n");
                break;
            }
            printf("\nInserisci chiave di ricerca: ");
            scanf("%s", chiave_ricerca);
            Ricerca_Stampa(chiave_ricerca, *studente_testa);
            break;
        }
    case 5:
        {

             if (*studente_testa == NULL)
            {
                printf("\nLa lista e' vuota, non si puo' effettuare alcuna cancellazione.\n");
                break;
            }
            printf("\nInserisci chiave di ricerca: ");
            scanf("%s", chiave_ricerca);
            Ricerca_Elimina(chiave_ricerca, studente_testa, studente_coda, num_studenti);
            break;
        }
    case 6:
        {
            StampaLista(*studente_testa);
            break;
        }
    case 0:
        {
            DeallocaLista(*studente_testa);
            *num_studenti = 0;
            break;
        }
    }
}

void ListaPUSH(ITEM **puttesta, ITEM **putcoda, ITEM **nuovo)
{

    if (*puttesta == NULL)
    {
        *puttesta = *putcoda = *nuovo;
    }
    else
    {
        (*nuovo)->succ = *puttesta;
        *puttesta = *nuovo;
    }
}

void Push_coda(ITEM **puttesta, ITEM **putcoda, ITEM **nuovo)
{
    (*nuovo)->succ = NULL;

    if(*puttesta == NULL) /*La lista e' vuota, puttesta=putcoda*/
    {
        *puttesta = *putcoda = *nuovo;
    }
    else
    {
        (*putcoda)->succ = *nuovo;
        *putcoda = *nuovo;
    }
}

void Ricerca_Stampa(char *chiave, ITEM *puttesta)
{
    ITEM *putcorr;
    char w1[LUNGHEZZA+1], w2[LUNGHEZZA+1], w3[LUNGHEZZA+1];
    int flag = 0;

    strcpy(chiave, RendiMinuscolo(chiave, strlen(chiave)));

    for (putcorr = puttesta; putcorr!= NULL; putcorr = putcorr->succ)
    {
        strcpy(w1, putcorr->nome);
        strcpy(w2, putcorr->cognome);
        strcpy(w3, putcorr->matricola);

        if (((strcmp(chiave, RendiMinuscolo(w1, strlen(w1)))) == 0) || ((strcmp(chiave, RendiMinuscolo(w2, strlen(w2)))) == 0) || ((strcmp(chiave, RendiMinuscolo(w3, strlen(w3)))) == 0))
        {
            StructITEMshow(putcorr);
            printf("\n\n");
            flag = 1;
        }
    }

    if (flag == 0)
    {
        printf("\nNessun risultato trovato.\n");
    }
}

void Ricerca_Elimina(char *chiave, ITEM **puttesta, ITEM **putcoda, int *Num_studenti)
{
    ITEM *putcorr=NULL, *putprec=NULL;
    char w1[LUNGHEZZA+1], w2[LUNGHEZZA+1], w3[LUNGHEZZA+1];
    int flag = 0;

    chiave = RendiMinuscolo(chiave, strlen(chiave));

    putprec = *puttesta;

    for (putcorr = *puttesta; putcorr!=NULL; putcorr = putcorr->succ)
    {
        strcpy(w1, putcorr->nome);
        strcpy(w2, putcorr->cognome);
        strcpy(w3, putcorr->matricola);

        if (((strcmp(chiave, RendiMinuscolo(w1, strlen(w1)))) == 0) || ((strcmp(chiave, RendiMinuscolo(w2, strlen(w2)))) == 0) || ((strcmp(chiave, RendiMinuscolo(w3, strlen(w3)))) == 0))
        {
            Elimina_da_lista(&putcorr, &putprec, puttesta, putcoda);
            *Num_studenti = *Num_studenti - 1;
            flag = 1;
        }
        putprec = putcorr;
    }

    if (flag == 0)
    {
        printf("\nNessun elemento cancellato.\n");
    }
}

void Elimina_da_lista(ITEM **putcorr, ITEM **putprec, ITEM **puttesta, ITEM **putcoda)
{
    if (*putcorr == *puttesta)
    {
        if (((*putcorr)->succ) == NULL)
        {
            free(*puttesta);
            free(*putcoda);
            *puttesta = NULL;
            *putcoda = NULL;
        }
        else
        {
            *puttesta = (*puttesta)->succ;
            free(*putcorr);
        }
    }
    else
    {
        if ((*putcorr)->succ != NULL)
        {
            (*putprec)->succ = (*putcorr)->succ;
            free(*putcorr);
        }
        else
        {
            *putcoda = *putprec;
            free(*putcorr);
            (*putcoda)->succ = NULL;
        }
    }
}

void StampaLista (ITEM *puttesta)
{
    ITEM *putcorr = NULL;

    putcorr = (ITEM*)malloc(sizeof(ITEM));

    if(puttesta == NULL)
    {
        printf("\nLa lista e' vuota.\n");
        free(putcorr);
        return;
    }

    for (putcorr = puttesta; putcorr!= NULL; putcorr = putcorr->succ)
    {
        StructITEMshow(putcorr);
        printf("\n\n");
    }
    free(putcorr);
}

void DeallocaLista(ITEM *puttesta)
{
    if(puttesta == NULL)
    {
        return;
    }
    DeallocaLista(puttesta->succ);
    free(puttesta);
}
