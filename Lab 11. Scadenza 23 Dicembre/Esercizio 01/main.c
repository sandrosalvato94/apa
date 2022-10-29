#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "BST.h"

void Stampamenu();
int GetDecision();

int main()
{
    int decisione = 1;

    while (decisione!=0)
    {
        Stampamenu();
        decisione = GetDecision();
        switch(decisione)
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
        case 8:
            {
                break;
            }
        case 9:
            {
                break;
            }
        case 10:
            {
                break;
            }
        case 11:
            {
                break;
            }
        case 12:
            {
                break;
            }
        case 13:
            {
                break;
            }
        case 0:
            {
                break;
            }
        default:
            {
                printf("\nERRORE: Comando non valido.\n\n");
                system("PAUSE");
                system("cls");
                break;
            }
        }
    }
    return 0;
}

void Stampamenu()
{
    printf("\n******MENU******\n\n\n");
    printf("1 - Crea un nuovo BST.\n");
    printf("2 - Inserisci in foglia un nuovo elemento.\n");
    printf("3 - Inserisci in radice un nuovo elemento.\n");
    printf("4 - Ricerca tramite codice numerico.\n");
    printf("5 - Stampa dell'elemento minimo e massimo.\n");
    printf("6 - Visualizzazione tramite visita IN-ORDER.\n");
    printf("7 - Visualizzazione tramite visita PRE-ORDER.\n");
    printf("8 - Visualizzazione tramite visita POST-ORDER.\n");
    printf("9 - Calcola altezza dell'albero.\n");
    printf("10 - Stampa numero totale degli elementi nella struttura dati.\n"); /*Calcolo dei numeri di nodi*/
    printf("11 - Stampa il numero totali di foglie.\n");
    printf("12 - Salva la struttura dati in file.\n");
    printf("13 - Carica struttura dati da file.\n");
    printf("0 - Termina.\n");
}

int GetDecision()
{
    int a;
    printf("\n\n Seleziona un'operazione: ");
    scanf("%d", &a);
    return a;
}
