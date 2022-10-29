#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "Tabella.h"
#define LUNGHEZZA 10

int ContaArchi_File(FILE *Puntatore_File, ST Tabella);
void Leggi_Dati_File(FILE *Puntatore_File, GRAPH Grafo, ST Tabella);
void StampaMenu();
int AcquisisciDecisione();
void PAUSE();
int InserisciVertice(ST Tabella);
void CamminoMinimo(ST Tabella, int vertice_partenza, int vertice_arrivo);

int main(int argc, char *argv[])
{
    FILE *fp;
    int num_vertici, num_archi=0;
    GRAPH Grafo = NULL;
    ST Tabella = NULL;
    int decisione = 1;
    int nv1, nv2;

    if (argc!=2)
    {
        printf("\nERRORE: numero di parametri errati da linea di comando.\n");
        return EXIT_FAILURE;
    }

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura.\n", argv[1]);
        return EXIT_SUCCESS;
    }

    fscanf(fp, "%d", &num_vertici);
    Tabella = ST_Init(num_vertici);
    num_archi = ContaArchi_File(fp, Tabella);
    rewind(fp);
    fscanf(fp, "%*d");
    Grafo = GraphInit(num_vertici, num_archi);
    Leggi_Dati_File(fp, Grafo, Tabella);
    //GraphShow(Grafo);

    while(decisione!=0)
    {
        StampaMenu();
        decisione = AcquisisciDecisione();
        switch(decisione)
        {
            case 1:
            {
                nv1 = InserisciVertice(Tabella);
                if(nv1 == -1)
                {
                    printf("\nERRORE: Vertice non trovato.\n");
                    PAUSE();
                    break;
                }
                nv2 = InserisciVertice(Tabella);
                if(nv2 == -1)
                {
                    printf("\nERRORE: Vertice non trovato.\n");
                    PAUSE();
                    break;
                }
                GRAPHbfs(Grafo, nv1, nv2);
                CamminoMinimo(Tabella, nv1, nv2);
                PAUSE();
                break;
            }
            case 2:
            {
                nv1 = InserisciVertice(Tabella);
                if(nv1 == -1)
                {
                    printf("\nERRORE: Vertice non trovato.\n");
                    PAUSE();
                    break;
                }
                nv2 = InserisciVertice(Tabella);
                if(nv2 == -1)
                {
                    printf("\nERRORE: Vertice non trovato.\n");
                    PAUSE();
                    break;
                }
                DAGrts(Grafo);
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
            case 0:
            {
               break;
            }
            default:
            {
                printf("\nERRORE: Comando non valido.");
                PAUSE();
            }
        }
    }

    return EXIT_SUCCESS;
}

int ContaArchi_File(FILE *Puntatore_File, ST Tabella)
{
    char v1[LUNGHEZZA+1], v2[LUNGHEZZA+1];
    int n=0;
    while(fscanf(Puntatore_File, "%s%s", v1, v2) != EOF)
    {
        ST_SCAN(Tabella, v1); /*Mentre conto il numero degli archi, mi salvo i nomi dei vertici, che poi convertirò tramite...*/
        ST_SCAN(Tabella, v2); /*...la tabella di simboli*/
        n++;
    }

    ST_Sort(Tabella);
    //ST_Show(Tabella);
    return n;
}

void Leggi_Dati_File(FILE *Puntatore_File, GRAPH Grafo, ST Tabella)
{
    EDGE edge;
    char v_a[LUNGHEZZA+1], v_p[LUNGHEZZA+1];
    int p, a, i=0;

    while(fscanf(Puntatore_File, "%s%s", v_p, v_a) != EOF)
    {
        a = Conversion_Word2Numb(Tabella, v_a);
        p = Conversion_Word2Numb(Tabella, v_p);
        edge = GetEdge(p, a);
        EdgeGraphInsert(Grafo, edge, i);
        i++;
    }
}

void StampaMenu()
{
    printf("\n******SELEZIONA UN'OPERAZIONE******\n\n\n");
    printf("\n1 - Calcola il cammino semplice minimo fra due vertici.\n");
    printf("2 - Calcola il cammino semplice massimo fra due vertici.\n");
    printf("3 - Calcola il numero di cammini semplici possibili fra due vertici.\n");
    printf("4 - Calcolare le componenti fortemente connesse del grafo.\n");
    printf("5 - Individuare il numero minimo possibile di archi, tale che il grafo sia ancora fortemente connesso.\n\n");
    printf("0 - Termina.\n\n");
}

int AcquisisciDecisione()
{
    int a;
    printf("\nQuale operazione: ");
    scanf("%d", &a);
    return a;
}

void PAUSE()
{
    printf("\n");
    system("PAUSE");
    system("cls");
}

int InserisciVertice(ST Tabella)
{
    char v1[LUNGHEZZA+1];
    int nv1;

    printf("\nInserisci nome del vertice: ");
    scanf("%s", v1);
    nv1=Conversion_Word2Numb(Tabella, v1);

    return nv1;
}

void CamminoMinimo(ST Tabella, int vertice_partenza, int vertice_arrivo)
{
    printf("\n Il cammino minimo semplice che collega il vertice %s e %s e':\n",
           ConversionNumber2Word(Tabella, vertice_partenza), ConversionNumber2Word(Tabella, vertice_arrivo));
    GetCammino(vertice_partenza, vertice_arrivo);
}
