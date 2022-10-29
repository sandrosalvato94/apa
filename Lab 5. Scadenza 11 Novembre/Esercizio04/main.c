#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA 10
#include <ctype.h>
#include <string.h>

typedef struct persona
{
    char codice[LUNGHEZZA+1];
    struct persona *succ;
}tipo_persona;

typedef enum {FALSE, TRUE} boolean;

void StampaMenu();
void Inserisci_in_lista(tipo_persona **puttesta, tipo_persona **putcorr);
void Elimina_da_lista(tipo_persona **puttesta);
void StampaLista(tipo_persona *puttesta);
void DeallocazioneLista(tipo_persona *puttesta);
char* RendiMaiuscolo(char *parola, int lunghezza_parola);
boolean verifica_presenza_in_lista(tipo_persona *puttesta, char codice_prenotazione[LUNGHEZZA+1]);

int main()
{
    tipo_persona *head, *coda;
    int decisione = 1;

    printf("\nBenevnuto del programma che gestisce i turni.\n");

    head = (tipo_persona *)malloc(sizeof(tipo_persona));
    coda = (tipo_persona *)malloc(sizeof(tipo_persona));
    head = NULL;
    coda = NULL;
    while (decisione != 0)
    {
        StampaMenu();
        scanf("%d", &decisione);

        switch (decisione)
        {
        case 1:
            {
                Inserisci_in_lista(&head, &coda);
                system("PAUSE");
                system("cls");
                break;
            }
        case 2:
            {
                Elimina_da_lista(&head);
                system("PAUSE");
                system("cls");
                break;
            }
        case 3:
            {
                StampaLista(head);
                printf("\n\n");
                system("PAUSE");
                system("cls");
                break;
            }
        case 0:
            {
                printf("\nGrazie per aver usato il programma\n");
                DeallocazioneLista(head);
                break;
            }
        default:
            {
                printf("\nERRORE: Comando non valido.\n");
                system("PAUSE");
                system("cls");
            }
        }
    }
    return EXIT_SUCCESS;
}

void StampaMenu()
{
    printf("\n***SELEZIONARE UNA DELLE SEGUENTI OPERAZIONI***\n\n");
    printf("\n1 - Aggiungi prenotazione.");
    printf("\n2 - Cancella prenotazione in cima.");
    printf("\n3 - Stampa ordine di prenotazione.");
    printf("\n0 - Chiudi il programma.\n\n");
    printf("\nSeleziona operazione: ");
}
void Inserisci_in_lista(tipo_persona **puttesta, tipo_persona **putcorr)
 {
    tipo_persona *nuovo;
    char codice_prenotazione[LUNGHEZZA+1];
    boolean presente;

    printf("\nInserisci codice di prenotazione: \n");
    scanf("%s", codice_prenotazione);

    presente = verifica_presenza_in_lista(*puttesta, RendiMaiuscolo(codice_prenotazione, strlen(codice_prenotazione)));
    if(presente == TRUE)
    {
        printf("\nIl codice %s e' già presente in lista\n", codice_prenotazione);
        return;
    }
    else
    {
        nuovo = (tipo_persona *)malloc(sizeof(tipo_persona));
        strcpy(nuovo->codice,  codice_prenotazione);
        nuovo->succ = NULL;

        if (*puttesta == NULL) /*Se la lista è vuota*/
        {
            *puttesta = *putcorr = nuovo;
            /* *puttesta->succ = NULL; */
        }
        else
        {
            (*putcorr)->succ = nuovo;
            *putcorr = nuovo;
        }
    }

 }

 char* RendiMaiuscolo(char *parola, int lunghezza_parola)
{
    int i;

    for (i=0; i<lunghezza_parola; i++)
    {
        parola[i] = toupper(parola[i]);
    }
    return(parola);
}

void Elimina_da_lista(tipo_persona **puttesta)
{
    tipo_persona *putcorr;
    boolean Presente;


    if (*puttesta == NULL)
    {
        printf("\nNon si puo' eliminare nulla: la lista e' vuota.\n");
    }
    else
    {
        if(((*puttesta)->succ) == NULL)
        {
            free(*puttesta);
            *puttesta = NULL;
        }
        else
        {
            putcorr = (*puttesta)->succ;
            free(*puttesta);
            *puttesta = putcorr;
        }
    }
}

void StampaLista(tipo_persona *puttesta)
{
    tipo_persona *putcorr;

    if (puttesta!= NULL)
    {
        for (putcorr = puttesta; putcorr!= NULL; putcorr = putcorr->succ)
        {
            printf("\n%s\n", putcorr->codice);
        }
    }
    else
    {
        printf("\nNon c'e' nessuno in attesa: la lista e' vuota.\n");
    }
}

void DeallocazioneLista(tipo_persona *puttesta)
{
    tipo_persona *putcorr;

    for (putcorr = puttesta; putcorr!= NULL; putcorr = putcorr->succ)
    {
        free(putcorr);
    }
}

boolean verifica_presenza_in_lista(tipo_persona *puttesta, char codice_prenotazione[LUNGHEZZA+1])
{
    tipo_persona *putcorr;

    for (putcorr = puttesta; putcorr!=NULL; putcorr = putcorr->succ)
    {
        if ((strcmp(putcorr->codice, codice_prenotazione)) == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}
