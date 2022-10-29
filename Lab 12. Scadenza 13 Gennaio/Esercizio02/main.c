#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Heap.h"
#define MAX 100
#define LUNGHEZZA 5

void StampaMenu();
int AcquisisciDecisione();
void PAUSE();
void AggiungiCliente(HEAP heap);
void EstraiCliente(HEAP heap);
void Leggi_dati_File(FILE* Puntatore_File, HEAP heap);
void Dealloca(HEAP Heap);

int main()
{
    int decisione=1;
    HEAP Heap=NULL;
    FILE *fp;
    char *nome_file;
    char r[LUNGHEZZA+1];

    Heap = HeapInit(MAX);

    while(decisione!=0)
    {
        StampaMenu();
        decisione = AcquisisciDecisione();

        switch (decisione)
        {
            case 1:
            {
                AggiungiCliente(Heap);
                PAUSE();
                break;
            }
            case 2:
            {
                EstraiCliente(Heap);
                PAUSE();
                break;
            }
            case 3:
            {
                printf("\nInserisci il nome del file da cui caricare i dati: ");
                scanf("%s", r);
                nome_file = strdup(r);
                if((fp = fopen(nome_file, "r")) == NULL)
                {
                    printf("\nERRORE nell'apertura del file %s in lettura.\nIl file potrebbe non esistere.\n", nome_file);
                    break;
                }
                Leggi_dati_File(fp, Heap);
                fclose(fp);
                free(nome_file);
                PAUSE();
                break;
            }
            case 4:
            {
                HeapSHOW(Heap);
                PAUSE();
                break;
            }
            case 0:
            {
                DeallocaHeap(Heap);
                break;
            }
            default:
            {
                printf("\nERRORE: Comando non valido.\n");
                PAUSE();
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}

void StampaMenu()
{
    printf("\n******SELEZIONA UNA DELLE SEGUENTI OPERAZIONI******\n\n");
    printf("1 - Aggiungi cliente.\n");
    printf("2 - Estrazione cliente.\n");
    printf("3 - Aggiungi i clienti dal database.\n");
    printf("4 - Stampa coda.\n");
    printf("0 - Termina.\n\n");
}

int AcquisisciDecisione()
{
    int a;
    printf("\nOperazione numero: ");
    scanf("%d", &a);
    return a;
}

void PAUSE()
{
    printf("\n");
    system("PAUSE");
    system("cls");
}

void AggiungiCliente(HEAP heap)
{
    HeapInsert(heap);
}

void EstraiCliente(HEAP heap)
{
    HeapExMax(heap);
}

void Leggi_dati_File(FILE* Puntatore_File, HEAP heap)
{
    HeapInsertFile(Puntatore_File, heap);
}

void Dealloca(HEAP Heap)
{
    DeallocaHeap(Heap);
}
