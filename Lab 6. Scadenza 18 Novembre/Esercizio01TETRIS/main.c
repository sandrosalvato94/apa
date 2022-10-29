#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "stack.h"
#include "queue.h"
#include "priorityqueue.h"
#include "item.h"
#define LUNGHEZZA 35

void StampaMenuGenerale();
int Seleziona_operazione();

int main()
{
    int decisione, numero_studenti = 0;
    ITEM *studente_testa = NULL, *studente_coda = NULL;

    StampaMenuGenerale();
    decisione = Seleziona_operazione();
    studente_testa = (ITEM*)malloc(sizeof(ITEM));
    studente_coda = (ITEM *)malloc(sizeof(ITEM));


    if ((studente_testa == NULL) || (studente_coda == NULL))
    {
        printf("\nERRORE: Non c'e' abbastanza memoria disponibile.\n");
        return EXIT_FAILURE;
    }
    studente_testa = studente_coda = NULL;

    system("cls");

    switch (decisione)
    {
    case 1:
        {
            while(decisione!=0)
            {
                StampaMenuLista();
                decisione = Seleziona_operazione();
                MainLista(decisione, &numero_studenti, &studente_testa, &studente_coda);
                system("PAUSE");
                system("cls");
            }
            break;
        }
    case 2:
        {
            while(decisione!=0)
            {
                StampaMenuStack();
                decisione = Seleziona_operazione();
                MainStack(decisione, &numero_studenti, &studente_testa);
                system("PAUSE");
                system("cls");
            }
            break;
        }
    case 3:
        {
            while (decisione!=0)
            {
                StampaMenuQueue();
                decisione = Seleziona_operazione();
                MainQueue(decisione, &numero_studenti, &studente_testa, &studente_coda);
                system("PAUSE");
                system("cls");
            }
            break;
        }
    case 4:
        {
            while (decisione!=0)
            {
                StampaMenuPriorityQueue();
                decisione = Seleziona_operazione();
                MainPriorityQueue(decisione, &numero_studenti, &studente_testa, &studente_coda);
                system("PAUSE");
                system("cls");
            }
            break;
        }
    case 0:
        {
            printf("\nProgramma terminato.\n");
            system("PAUSE");
            free(studente_testa);
            free(studente_coda);
            break;
        }
    default:
        {
            printf("\nERRORE: Comando non valido.\n\n");
            system("PAUSE");
            break;
        }
    }
    return 0;
}

void StampaMenuGenerale()
{
    printf("\n***SELEZIONA UNA DELLE SEGUENTI OPERAZIONI***\n");
    printf("\n1 - Liste Semplici");
    printf("\n2 - FIFO");
    printf("\n3 - LIFO");
    printf("\n4 - Priority Queue");
    printf("\n0 - Nessuna. Termina.");
}

int Seleziona_operazione()
{
    int a;

    printf("\nSelezione il comando da eseguire: ");
    scanf("%d", &a);

    return (a);
}
